#include <SPI.h>
#include <LoRa.h>

// LoRa pins
const int csPin = 24;
const int resetPin = 26;
const int irqPin = 25;

// Frquency for LoRa in Hz
const long freq = 4337E5; // 433.7 MHz

void onReceive(int packetSize) {
  if (packetSize == 0) return;
  String incoming = "";
  while (LoRa.available()) {
    digitalWrite(2, HIGH);
    incoming += (char)LoRa.read();
  }
  Serial.print(incoming);
  Serial.print(",");
  Serial.print(LoRa.packetRssi());
  Serial.print(",");
  Serial.println(LoRa.packetSnr());
  digitalWrite(2, LOW);
}
  
void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600); 
  LoRa.setPins(csPin, resetPin, irqPin);
  // Tries to start up LoRa module. If it doesn't start, goes into infinite loop
  if (!LoRa.begin(freq)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(10);
  LoRa.setSignalBandwidth(125E3);
  // LoRa.setGain(6);
}

void loop() {
  onReceive(LoRa.parsePacket());
}
