#include <Wire.h>
#include <CC2500.h>
#include <ColourConversion.h>
#include <LivingColors.h>
#include <EEPROM.h>

#define lcMOSI 11
#define lcMISO 12
#define lcSCK  13
#define lcCS   10

#define LED   7
#define LEARN 8

#define COMMAND_OFF '0'
#define COMMAND_COLOR '1'
#define COMMAND_EFFECT_COLOR_CYCLE '2'

LivingColors livcol(lcCS, lcSCK, lcMOSI, lcMISO);

struct LightData
{
  char command;
  char h0;
  char h1;
  char h2;
  char s0;
  char s1;
  char s2;
  char v0;
  char v1;
  char v2;
};

bool lampState = false;

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(LED, OUTPUT);
  pinMode(LEARN, INPUT);
  digitalWrite(LED, LOW);

  livcol.init();
  livcol.clearLamps();

  // Learn a new remote address
  if (digitalRead(LEARN) == HIGH) {
    digitalWrite(LED, HIGH);
    livcol.learnLamps();
    digitalWrite(LED, LOW);

    // Address not found
    if (livcol.getNumLamps() == 0) {
      while (1) {
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        delay(1000);
      }
    }

    // Write address on EEPROM
    unsigned char learnedAdress[9] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    livcol.getLamp(0, learnedAdress);
    Serial.println("learned addr:");
    for (int x=0; x<9; x++) {
      Serial.print(learnedAdress[x], HEX);
      Serial.print(", ");
      EEPROM.write(x, learnedAdress[x]);
    }
    Serial.println("");
  }

  // Read address on EEPROM
  unsigned char address[9] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  Serial.println("Read addr:");
  byte val;
  for (int y=0; y<9; y++) {
    val = EEPROM.read(y);
    address[y] = val;
    Serial.print(val, HEX);
    Serial.print(", ");
  }
  Serial.println("");

  // Address not found on EEPROM. Need to learn it ?
  if (address[8] != 0x11) {
    while (1) {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
    }
  }

  livcol.addLamp(address);

  Wire.begin(0x21);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

// Function that executes whenever data is received from master
// This function is registered as an event, see setup()
void receiveEvent(int howMany) {
  char buf[13];
  int i=0;
  while (1 <= Wire.available() && i<=12) {
    char c = Wire.read();
    buf[i] = c;
    i++;
  }
  buf[i]=0;

  // c|hhh-sss-vvv
  LightData lightData;
  lightData.command = buf[0];
  lightData.h0 = buf[2];
  lightData.h1 = buf[3];
  lightData.h2 = buf[4];
  lightData.s0 = buf[6];
  lightData.s1 = buf[7];
  lightData.s2 = buf[8];
  lightData.v0 = buf[10];
  lightData.v1 = buf[11];
  lightData.v2 = buf[12];

  send(lightData);
}

void send(LightData lightData) {
  // Turn off
  if (lightData.command == COMMAND_OFF) {
    livcol.turnLampOff(Val('0'));
    lampState = false;

    return;
  }

  // Effect color cycle
  if (lightData.command == COMMAND_EFFECT_COLOR_CYCLE) {
    livcol.turnLampOnRotating(Val('0'));
    lampState = true;

    return;
  }

  // Set color
  byte valH = Val(lightData.h0, lightData.h1, lightData.h2);
  byte valS = Val(lightData.s0, lightData.s1, lightData.s2);
  byte valV = Val(lightData.v0, lightData.v1, lightData.v2);

  if (lampState == false) {
    livcol.turnLampOnHSV(Val('0'), valH, valS, valV);
    lampState = true;

    return;
  }

  livcol.setLampColourHSV(Val('0'), valH, valS, valV);
}

byte Val(char c) {
  byte t = 0;

  if (c >= '0' && c <= '9') {
    t = c - '0';
  }

  return t;
}

byte Val(char c1, char c2, char c3) {
  return Val(c3) + 10 * Val(c2) + 100 * Val(c1);
}
