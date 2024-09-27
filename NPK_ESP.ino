#include <ModbusMaster.h> //Library for interfacing with RS485

#define DE_RE 4

ModbusMaster node;

byte values[11];

void preTransmission()
{
  digitalWrite(DE_RE, HIGH);
}

void postTransmission()
{
  digitalWrite(DE_RE, LOW);
}

void setup()
{
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);

  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  node.begin(1, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop()
{
  uint8_t result = node.readHoldingRegisters(0,3);
  Serial.print("Received Successfully\n");

  delay(1000);

  if (result == node.ku8MBSuccess)
  {
    Serial.print("Nitro: ");
    Serial.print(node.getResponseBuffer(0), HEX);
    Serial.println(" mg/kg");
    Serial.print("Phos: ");
    Serial.print(node.getResponseBuffer(1),HEX);
    Serial.println(" mg/kg");
    Serial.print("Pot: ");
    Serial.print(node.getResponseBuffer(3), HEX);
    Serial.println(" mg/kg");

  }

  else
  {
    Serial.print("Failed, Response Code: ");
    Serial.print(result, HEX);
    Serial.println("");
    delay(5000);
  }
  
  Serial.print("\n");
  delay(1000);
}