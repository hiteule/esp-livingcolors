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

LivingColors livcol(lcCS, lcSCK, lcMOSI, lcMISO);

char SerBuf[BufSize];

struct LightData
{
  char r0;
  char r1;
  char r2;
  char g0;
  char g1;
  char g2;
  char b0;
  char b1;
  char b2;
};

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
  char buf[25];
  int i=0;
  while (1 <= Wire.available()) {
    char c = Wire.read();
    buf[i] = c;
    i++;
  }
  buf[i]=0;

  // rrr-ggg-bbb
  LightData lightData;
  lightData.r0 = buf[0];
  lightData.r1 = buf[1];
  lightData.r2 = buf[2];
  lightData.g0 = buf[4];
  lightData.g1 = buf[5];
  lightData.g2 = buf[6];
  lightData.b0 = buf[8];
  lightData.b1 = buf[9];
  lightData.b2 = buf[10];

  send(lightData);
}

void send(LightData lightData) {
  // Black: turn off
  if (lightData.r0 == '0' && lightData.r1 == '0' && lightData.r2 == '0'
    && lightData.g0 == '0' && lightData.g1 == '0' && lightData.g2 == '0'
    && lightData.b0 == '0' && lightData.b1 == '0' && lightData.b2 == '0') {
    livcol.turnLampOff(Val('0'));

    return;
  }

  byte valR = Val(lightData.r0, lightData.r1, lightData.r2);
  byte valG = Val(lightData.g0, lightData.g1, lightData.g2);
  byte valB = Val(lightData.b0, lightData.b1, lightData.b2);

  livcol.turnLampOnRGB(Val('0'), valR, valG, valB);
}

byte Val(char c) {
  byte t = 0;
  if (c>='0')
    if (c<='9')
    {
      t = c - '0';
    }
  return t;      
}

byte Val(char c1, char c2, char c3)
{
  return Val(c3) + 10 * Val(c2) + 100 * Val(c1); 
}
