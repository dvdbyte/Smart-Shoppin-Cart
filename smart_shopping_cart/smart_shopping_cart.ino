#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;     

MFRC522 rfid(SS_PIN, RST_PIN); // 
MFRC522::MIFARE_Key key;

int a;
int p1=0,p2=0,p3=0,p4=0; 
int c1=0,c2=0,c3=0,c4=0;

double total = 0;
int count_prod = 0;
String tag;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  // pinMode(D8, OUTPUT);
//  Pin direction
   
  pinMode(8, INPUT_PULLUP);   //Push Switch
  // pinMode(4, OUTPUT);         //RED LED
  pinMode(A0, OUTPUT);         //BUZZER
  // pinMode(6, OUTPUT);         //GREEN LED

// Initialization
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  delay (2000);
  lcd.print("SMART ");
  lcd.setCursor(0, 1);      
  lcd.print("SHOPPING CART");
  delay (2000);
  // lcd.clear();



}
void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "2122468242") {
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Added");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):35.00");
        p1++;
        // digitalWrite(D4,HIGH);
        delay(2000);
        total = total + 35.00;
        count_prod++;
        // digitalWrite(D4,LOW);
        lcd.clear();
    } else if (tag == "212969642") {
         lcd.setCursor(0, 0);
        lcd.print("Soap Added          ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):38.00         ");
        total = total + 38.00;
        digitalWrite(D8, HIGH);
        delay(2000);
        p2++;
        count_prod++;
        digitalWrite(A0,LOW);
        lcd.clear();
    } else if (tag == "16215738") {
         lcd.setCursor(0, 0);
        lcd.print("Rice(1KG) Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):55.00      ");
        total = total + 55.00;
        digitalWrite(D8, HIGH);
        delay(2000);
        count_prod++;
        p3++;
        lcd.clear();
        digitalWrite(A0,LOW);
    } else {
      Serial.println("Access Denied!");
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(A0, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}