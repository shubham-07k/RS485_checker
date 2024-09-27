#define MAX485_DE_RE 4

// half second wait
const uint32_t TIMEOUT = 500UL;

// Requesting msg
uint8_t msg[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x03, 0x65, 0xCD};

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);
  delay(1000);
}

void loop() {
  uint32_t startTime = 0;

  Serial.print("TX: ");
  hexMessage( msg, sizeof(msg) );

  // send the command
  digitalWrite(MAX485_DE_RE, HIGH);
  delay( 10 );
  Serial1.write( msg, sizeof(msg) );
  Serial1.flush();
  digitalWrite(MAX485_DE_RE, LOW);

  Serial.print("RX: ");
  
  // read any data received and print it out
  startTime = millis();
  while ( millis() - startTime <= TIMEOUT ) {
    if (Serial1.available()) {
      hexByte(Serial1.read());
    }
  }
  Serial.println();
  delay(2000);
}

void hexMessage( uint8_t values[], uint8_t sz ) {
  for (uint8_t i = 0; i < sz; i++) {
    hexByte( values[i] );
  }
  Serial.println();
}

void hexByte(byte b)
{
  Serial.print((b >> 4) & 0xF, HEX);
  Serial.print(b & 0xF, HEX);
  Serial.print(' ');
}

/*
TX: 01 03 00 1E 00 03 65 CD 
RX: 01 03 06 00 09 00 0C 00 19 FC BD
*/


