#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h> 

// Replace with the service UUID and characteristic UUID of your ESP32
#define SERVICE_UUID "0000180a-0000-1000-8000-00805f9b34fb"
#define CHARACTERISTIC_UUID "00002a23-0000-1000-8000-00805f9b34fb"

BLEServer *server;
BLEService *service;
BLECharacteristic *characteristic;

void setup() {
  // Start the BLE server
  BLEDevice::init("ESP32");
  server = BLEDevice::createServer();
  service = server->createService(SERVICE_UUID);
  characteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  characteristic->addDescriptor(new BLE2902());
  service->start();
  server->getAdvertising()->start();
}

void loop() {
  // Send data to the web app
  String data = "Hello from ESP32";
  characteristic->setValue(data.c_str());
  characteristic->notify();
  delay(1000);
}
