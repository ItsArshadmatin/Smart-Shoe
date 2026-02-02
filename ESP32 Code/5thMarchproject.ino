#define FIREBASE_PROJECT_ID "esp32-firebase-8e6ac"
#define FIREBASE_API_KEY "AIzaSyAYb7Q6Sl9pzFXuueVAXaANM8ZlE_7GxAE"
#define FIREBASE_COLLECTION "sensorData"
#define FIREBASE_DOCUMENT "latest"

#include <WiFi.h>
#include <WiFiClient.h>
#include <TinyGPSPlus.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

char ssid[] = "ARSHAD";
char pass[] = "PASSWORD";

#define RXD2 16
#define TXD2 173
#define GPS_BAUD 9600
#define PIEZO_PIN 33
#define STEPS_PER_METER 1.25
#define DEBOUNCE_DELAY 300
#define CALORIES_PER_STEP 0.04

#define Y_PIN 35
#define X_PIN 34  
#define Z_PIN 32  
#define ZERO_G 1.65
#define SENSITIVITY 0.3
#define ADC_MAX 4095
#define V_REF 3.3
#define G_TO_MS2 9.81
#define ACCEL_OFFSET 5.0
#define NOISE_THRESHOLD 0.5

#define DEFAULT_LAT 20.781528
#define DEFAULT_LON 76.678167

const char* botToken = "8034404540:AAHFCZuapVtXv_imMimxPzDaA6k9eyblCWk";
const char* chatID = "1950427601";
const char* chatID2 = "1392743150";


TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
volatile bool stepDetected = false;
volatile int stepCount = 0;
float distance = 0.0;
float calories = 0.0;
String lastLocation = "Fetching...";
float latitude = 0.0;
float longitude = 0.0;
float prevAccelY = 0.0;
unsigned long lastStepTime = 0;
int fallCount = 0;
bool messageSent = false;

void IRAM_ATTR detectStep() {
    unsigned long currentTime = millis();
    if (currentTime - lastStepTime > DEBOUNCE_DELAY) {
        stepDetected = true;
        lastStepTime = currentTime;
    }
}

void sendDataToFirestore(int steps, float distance, float calories, float latitude, float longitude, float accelY) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "https://firestore.googleapis.com/v1/projects/" + String(FIREBASE_PROJECT_ID) +
                     "/databases/(default)/documents/" + String(FIREBASE_COLLECTION) + "/" + String(FIREBASE_DOCUMENT) + "?key=" + String(FIREBASE_API_KEY);

        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        if (latitude == 0.000000 && longitude == 0.000000) {
            latitude = DEFAULT_LAT;
            longitude = DEFAULT_LON;
        }

        String locationUrl = "https://ItsArshadmatin.github.io/map-project/map.html?lat=" + String(latitude, 6) + "&lng=" + String(longitude, 6);
        String googleMapsLink = "https://www.google.com/maps/search/?api=1&query=" + String(latitude, 6) + "," + String(longitude, 6);
        

        StaticJsonDocument<256> json;
        json["fields"]["stepCount"]["integerValue"] = steps;
        json["fields"]["distance"]["doubleValue"] = distance;
        json["fields"]["calories"]["doubleValue"] = calories;
        json["fields"]["latitude"]["doubleValue"] = latitude;
        json["fields"]["longitude"]["doubleValue"] = longitude;
        json["fields"]["accelerationY"]["doubleValue"] = String(accelY, 2).toFloat();
        json["fields"]["location"]["stringValue"] = locationUrl;
        json["fields"]["googleMapsLink"]["stringValue"] = googleMapsLink;

        String requestBody;
        serializeJson(json, requestBody);

        int httpResponseCode = http.PATCH(requestBody);
        if (httpResponseCode > 0) {
            Serial.println("✅ Data successfully stored in Firestore!");
        } else {
            Serial.print("❌ Error sending data: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }
}

void sendTelegramMessage(String googleMapsLink) {
    if (WiFi.status() == WL_CONNECTED) {
        String message = "❌ EMERGENCY POSSIBLE FALL DETECTED! Location: " + googleMapsLink;
        HTTPClient http;

        // Send to first user
        String url1 = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatID) + "&text=" + message;
        http.begin(url1);
        int httpResponseCode1 = http.GET();
        if (httpResponseCode1 > 0) {
            Serial.println("Message sent to Telegram user 1");
        } else {
            Serial.println("Failed to send message to user 1");
        }
        http.end();

        // Send to second user
        String url2 = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatID2) + "&text=" + message;
        http.begin(url2);
        int httpResponseCode2 = http.GET();
        if (httpResponseCode2 > 0) {
            Serial.println("Message sent to Telegram user 2");
        } else {
            Serial.println("Failed to send message to user 2");
        }
        http.end();
    } else {
        Serial.println("WiFi not connected");
    }
}


void setup() {
    Serial.begin(115200);
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
    WiFi.begin(ssid, pass);
    pinMode(PIEZO_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIEZO_PIN), detectStep, RISING);
}

void loop() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }
    if (stepDetected) {
        stepDetected = false;
        stepCount++;
        distance = stepCount / STEPS_PER_METER;
        calories = stepCount * CALORIES_PER_STEP;
        Serial.print("Steps: ");
        Serial.print(stepCount);
        Serial.print(" | Distance: ");
        Serial.print(distance);
        Serial.print(" m | Calories: ");
        Serial.println(calories);
        sendDataToFirestore(stepCount, distance, calories, latitude, longitude, prevAccelY);
    }
    if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        lastLocation = "Lat: " + String(latitude, 6) + "° , Long: " + String(longitude, 6) + "°";
    }
    float voltageY = (analogRead(Y_PIN) * V_REF) / ADC_MAX;
    float accelY_g = (voltageY - ZERO_G) / SENSITIVITY;
    float accelY = fabs(accelY_g * G_TO_MS2) - ACCEL_OFFSET;
    if (accelY < NOISE_THRESHOLD) {
        accelY = 0;
    }
    if (fabs(accelY - prevAccelY) > NOISE_THRESHOLD) {
        prevAccelY = accelY;
        Serial.print("Y-Axis Acceleration: ");
        Serial.print(accelY);
        Serial.println(" m/s²");
        sendDataToFirestore(stepCount, distance, calories, latitude, longitude, accelY);
    }
    int xRaw = analogRead(X_PIN);
    int yRaw = analogRead(Y_PIN);
    int zRaw = analogRead(Z_PIN);
    float xG = (xRaw - 1650) / 330.0;
    float yG = (yRaw - 1650) / 330.0;
    float zG = (zRaw - 1650) / 330.0;
    float roll = atan2(yG, zG) * 57.2958 - 30.0;
    float pitch = atan2(-xG, sqrt(yG * yG + zG * zG)) * 57.2958 + 57.0;

    Serial.print("Roll: "); Serial.print(roll);
    Serial.print(" | Pitch: "); Serial.println(pitch);

    if (abs(roll) > 60 || abs(pitch) > 60) {
        fallCount++;
        if (fallCount >= 5 && !messageSent) {
            sendTelegramMessage("https://www.google.com/maps/search/?api=1&query=" + String(latitude, 6) + "," + String(longitude, 6));
            messageSent = true;
        }
    } else {
        fallCount = 0;
        messageSent = false;
    }
    delay(1000);
}

