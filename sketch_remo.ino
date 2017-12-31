#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(14);

void setup() {
  Serial.begin(9600);

  initWifi();
  initFirebase();

  irsend.begin();
  //dumpChipInformation();
}

void loop() {
  String word = readFirebase();
  if(word == "REGZA POWER"){
    irsend.sendNEC(0x2FD48B7);
  }else if(word == "DENON POWER") {
    irsend.sendDenon(0x2024);
  }else if(word == "DENON VOLUP") {
    irsend.sendDenon(0x22C4);
  }else if(word == "DENON VOLDOWN") {
    irsend.sendDenon(0x20C4);
  }else if(word == "ROOMBA CLEAN"){
    uint16_t rawData[47] = {3006, 934,  1056, 2852,  1024, 2852,  1024, 2850,  2954, 912,  1030, 2876,  1004, 2876,  1000, 20440,  3008, 934,  1030, 2876,  978, 2904,  998, 2878,  2954, 912,  1030, 2882,  1000, 2876,  1000, 20446,  2994, 1602,  1582, 3870,  1024, 2850,  1026, 2856,  3146, 1610,  1536, 4078,  1024, 2852,  1004};  // UNKNOWN EE79A1E
    irsend.sendRaw(rawData,sizeof(rawData),38);
  }else if(word == "ROOMBA DOCK"){
    uint16_t rawData[31] = {3448, 1608,  1540, 3830,  1026, 2850,  1024, 2852,  1024, 2852,  3542, 1624,  1538, 4018,  3608, 20104,  3546, 1618,  1542, 4032,  1026, 2852,  1028, 2852,  1026, 2856,  3626, 1628,  1542, 4180,  3668};  // UNKNOWN 9F444744
    irsend.sendRaw(rawData,sizeof(rawData),38);
  }else if(word == "LIGHT POWER"){
    irsend.sendPanasonic(0x344A,0x344A90401041);
  }else if(word == ""){
    Serial.println("COMMAND EMPTY");
  }else {
    Serial.print("UNKNOWN COMMAND = ");
    Serial.println(word);
  }

  resetFirebase();

  //ESP.deepSleep(10*1000*1000,WAKE_RF_DEFAULT);
  delay(1000);
}
