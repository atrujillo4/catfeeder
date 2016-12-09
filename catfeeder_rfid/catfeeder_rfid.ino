#include <Servo.h>
#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9
#define SRV_PIN 11
#define DOR_OPEN 160
#define DOR_CLOSE 0


Servo doorServo;
int servoPos = 0;

RFID rfid(SS_PIN, RST_PIN);

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Serial communication up........."));
  //Start SPI interface
  SPI.begin();
  While(!SPI);
  Serial.println(F("SPI communication up........."));
  //Initialize the RFID client
  rfid.init();
  Serial.println(F("RFID initialized client........."));
  // This is the PWM digital pin to attach servo control wire to.
  doorServo.attach(SRV_PIN);
  Serial.println(F("Servo attached to PIN(PWM)" + SRV_PIN + "........."));

}

void loop() {

  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      if (rfid.serNum[0] != serNum0 && rfid.serNum[1] != serNum1
          && rfid.serNum[2] != serNum2 && rfid.serNum[3] != serNum3
          && rfid.serNum[4] != serNum4) {
        /* With a new cardnumber, show it. */
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];

        //Serial.println(" ");
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        Serial.println(" ");
      } else {
        /* If we have the same ID, just write a dot. */
        Serial.print(".");
        //Open the cat door
        doorServo.write(DOR_OPEN);
      }
    }
  }

}
