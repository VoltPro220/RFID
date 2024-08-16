#include "SPI.h"
#include "MFRC522.h"

#define RST_PIN 9 // RES pin
#define SS_PIN  10 // SDA (SS) pin
#define CST_COUNT 4

byte readCard[CST_COUNT];
//String cardID = "A0B1C2D3"; // ID
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(7, OUTPUT);
}

void loop() {
  while (getID()) {
    //if (tagID == cardID) {
    //  Serial.println("Access Granted!");
    //  CODE:
    //}
    //else {
    //  Serial.println("Access Denied!");
    //  CODE:
    //}
    Serial.print("ID: ");
    Serial.println(tagID);
    delay(2000);
  }
}

boolean getID() {
  if (!mfrc522.PICC_IsNewCardPresent()) 
    return false;
    
  if (!mfrc522.PICC_ReadCardSerial()) 
    return false;

  tagID = "";

  for (uint8_t i = 0; i < CST_COUNT; i++) 
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  
  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}