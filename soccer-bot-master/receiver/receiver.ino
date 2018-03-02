
#include <SPI.h>
#include <DW1000.h>
#include <ArduinoJson.h>

// Motor
uint8_t motorOutputL;
uint8_t motorOutputR;
const int forward = 4;
const int reverse = 7;
const int l_pwm = 3;
const int r_pwm = 6;

// Reset
const int rst = 8;


// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

// DEBUG packet sent status and count
volatile boolean received = false;
volatile boolean error = false;
volatile int16_t numReceived = 0; // todo check int type
String message;
int threshold = 550;

void setup() {
  // motor
  
  // DEBUG monitoring
  Serial.begin(9600);
  Serial.println(F("### DW1000-arduino-receiver-test ###"));
  // initialize the driver
  DW1000.begin(PIN_IRQ, PIN_RST);
  DW1000.select(PIN_SS);
  Serial.println(F("DW1000 initialized ..."));
  // general configuration
  DW1000.newConfiguration();
  DW1000.setDefaults();
  DW1000.setDeviceAddress(6);
  DW1000.setNetworkId(10);
  DW1000.enableMode(DW1000.MODE_LONGDATA_RANGE_LOWPOWER);
  DW1000.commitConfiguration();
  Serial.println(F("Committed configuration ..."));
  // DEBUG chip info and registers pretty printed
  char msg[128];
  DW1000.getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000.getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  
  DW1000.getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);
  // attach callback for (successfully) received messages
  DW1000.attachReceivedHandler(handleReceived);
  DW1000.attachReceiveFailedHandler(handleError);
  DW1000.attachErrorHandler(handleError);
  // start reception
  receiver();
}

void handleReceived() {
  // status change on reception success
  received = true;
}

void handleError() {
  error = true;
}

void receiver() {
  DW1000.newReceive();
  DW1000.setDefaults();
  // so we don't need to restart the receiver manually
  DW1000.receivePermanently(true);
  DW1000.startReceive();
}

void loop() {
  // enter on confirmation of ISR status change (successfully received)
  StaticJsonBuffer<200> jsonBuffer;
  if (received) {
    numReceived++;
    // get data as string
    DW1000.getData(message);
    JsonObject& root = jsonBuffer.parseObject(message);
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }
    int verti = root["x"];
    int hori = root["y"];
    
    if (verti > 600) {
      foward();
    } else if (verti < 400) {
      backward();
    } else if (hori > 600) {
      turnLeft();
    } else if (hori < 400) {
      turnRight();
    } else {
      Stop();
    }


    
    Serial.println(verti);
    Serial.println(hori);

    
    Serial.print("Received message ... #"); Serial.println(numReceived);
    Serial.print("Data is ... "); Serial.println(message);
    Serial.print("FP power is [dBm] ... "); Serial.println(DW1000.getFirstPathPower());
    Serial.print("RX power is [dBm] ... "); Serial.println(DW1000.getReceivePower());
    Serial.print("Signal quality is ... "); Serial.println(DW1000.getReceiveQuality());
    received = false;
  }
  if (error) {
    Serial.println("Error receiving a message");
    error = false;
    DW1000.getData(message);
    Serial.print("Error data is ... "); Serial.println(message);
  }
}

void foward() {

    delay(10);
}

void backward() {
    delay(10);
}

void turnLeft() {
  
    delay(10);
}

void turnRight() {

    delay(10);
}

void Stop() {
  
    delay(10);
}
