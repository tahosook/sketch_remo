//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseRoom_ESP8266 is a sample that demo using multiple sensors
// and actuactor with the FirebaseArduino library.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "tahosook-smarthome.firebaseio.com"
#define FIREBASE_AUTH "AAAA0xo5Q5M:APA91bFo-1dws_FNvxdDM1WdXqKZgvsvwPTm_e6Xw0mL5XHc7RB4MzXSE226JmAuFgrlZPqkZgxRohx1xvc_fVOFHSuRfmEGAanxouFrzLpCdaScRJRn_f5mdbBaVPCrGkUJW6VsR176"
#define WIFI_SSID "30F772BBF363-2G"
#define WIFI_PASSWORD "2215092608712"

void initWifi() {
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}
void initFirebase() {
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.begin(FIREBASE_HOST);
}

String readFirebase(){
    String word = Firebase.getString("googlehome/word");
    if (Firebase.failed()) {
        Serial.print("getting /googlehome/word failed:");
        Serial.println(Firebase.error());
        return "error";
    }

    Serial.print("Firebase string = ");
    Serial.println(word);

    return word;
}

void resetFirebase(){
    Firebase.setString("googlehome/word","");
    if (Firebase.failed()) {
        Serial.print("getting /googlehome/word failed:");
        Serial.println(Firebase.error());
    }
}
