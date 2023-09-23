#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "wifi_name"
#define WIFI_PASSWORD "wifi_pass"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDzU0Ndmefis6IOULmc43RPubieEAdgQ9U"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://nodemcu-9a843-default-rtdb.europe-west1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int nivosvjetlosti;
bool signupOK = false;
int senzor = 0;
bool automatski = true;
int granica = 0;

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
  if (Firebase.RTDB.getBool(&fbdo, "/rasvjeta/automatski")) {   
      if (fbdo.dataType() == "boolean") {
        automatski = fbdo.boolData();
        Serial.println("automatski:");
        Serial.println(automatski);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  if (automatski == true) {
    senzor = analogRead(A0);
    if (Firebase.RTDB.setInt(&fbdo, "rasvjeta/senzor", senzor)){
      Serial.println("PASSED");
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/rasvjeta/granica")) {
      if (fbdo.dataType() == "int") {
        granica = fbdo.intData();
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    if (senzor < granica) {
      analogWrite(D1, 255);
    }
    else {
      analogWrite(D1, 0);
    }
  }
  else {
     if (Firebase.RTDB.getInt(&fbdo, "/rasvjeta/nivosvjetlosti")) {
      if (fbdo.dataType() == "int") {
        nivosvjetlosti = fbdo.intData();
        analogWrite(D1, nivosvjetlosti);
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}
}
}
