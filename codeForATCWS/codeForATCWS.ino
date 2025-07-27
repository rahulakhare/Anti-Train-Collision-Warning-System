#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

RF24 radio(9, 10); // CE = 9, CSN = 10
const byte address[6] = "00001"; 


LiquidCrystal_I2C lcd(0x27, 16, 2);


const int buzzerPin = 7;

unsigned long lastSendTime = 0;
bool trainDetected = false;
unsigned long lastReceiveTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Booting...");
  delay(1000);
  lcd.clear();

 
  lcd.setCursor(0, 0);
  lcd.print("Testing NRF24...");
  radio.begin();
  bool nrfStatus = radio.isChipConnected();
  if (nrfStatus) {
    lcd.setCursor(0, 1);
    lcd.print("NRF24 OK");
    Serial.println("NRF24L01 is connected.");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("NRF24 FAIL");
    Serial.println("NRF24L01 not detected!");
  }
  delay(1500);
  lcd.clear();

 
  lcd.setCursor(0, 0);
  lcd.print("Testing Buzzer...");
  Serial.println("Testing Buzzer...");
  tone(buzzerPin, 1000); 
  delay(300);
  noTone(buzzerPin);
  lcd.setCursor(0, 1);
  lcd.print("Buzzer OK");
  delay(1500);
  lcd.clear();


  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS); 
  radio.startListening();

  lcd.setCursor(0, 0);
  lcd.print("Waiting Signal");
}

void loop() {
  
  if (radio.available()) {
    char receivedMsg[32] = "";
    radio.read(&receivedMsg, sizeof(receivedMsg));

    Serial.println("Message received:");
    Serial.println(receivedMsg);

    trainDetected = true;
    lastReceiveTime = millis();
    showWarning();
  }


  if (millis() - lastSendTime > 500) {
    radio.stopListening();
    const char text[] = "ping";
    radio.openWritingPipe(address);
    radio.write(&text, sizeof(text));
    radio.startListening();
    lastSendTime = millis();
  }

  
  if (trainDetected && millis() - lastReceiveTime > 3000) {
    trainDetected = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Train Nearby");
    noTone(buzzerPin);
  }
}

void showWarning() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!!! WARNING !!!");
  lcd.setCursor(0, 1);
  lcd.print("Train Detected");

  tone(buzzerPin, 1000);
  delay(200);
  noTone(buzzerPin);
}
