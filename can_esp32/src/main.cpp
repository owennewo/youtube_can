#include <Arduino.h>
#include <CAN.h>

// default pins crx=4 ctx=5

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet, id=0x");
  Serial.print(CAN.packetId(), HEX);

  static int led_state = HIGH;
  led_state = !led_state;
  digitalWrite(BUILTIN_LED, led_state);

  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  } else {
    Serial.print(", length=");
    Serial.print(packetSize);

    int byte_index=0;
    // only print packet data for non-RTR packets
    while (CAN.available()) {
      Serial.print(" byte["); Serial.print(byte_index); Serial.print("]=");  Serial.print(CAN.read()); Serial.print(" ");
      byte_index++;
    }
    Serial.println();
  }

}

void setup() {

  pinMode(BUILTIN_LED, OUTPUT);

  Serial.begin(115200);
  delay(1000);
  Serial.println("Setup");

  if (!CAN.begin(1000E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
  
}

void loop() {

  // static byte counter = 0;
  // static int identifier = 0x12;

  // delay(1000);
  // CAN.beginPacket(identifier);
  // CAN.write(counter);
  // CAN.write(255); // up to 8 bytes
  // CAN.endPacket();

  // Serial.println("sent");

}
