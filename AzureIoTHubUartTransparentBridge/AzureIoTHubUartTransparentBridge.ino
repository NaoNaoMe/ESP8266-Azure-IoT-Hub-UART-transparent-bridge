//******************************************************************************
// AzureIoTHubUartTransparentBridge
// Version 1.0.0
// Note
// Example Transparent UART to AzureIoTHub for esp8266"
//******************************************************************************

#include <ESP8266WiFi.h>
#include "AzureIoTHub.h"

AzureIoTHub Azure;

const char* ssid = "your-ssid";
const char* password = "ssid-pass";

const String ConnectionString = "HostName=xxxx.azure-devices.net;DeviceId=xxxx;SharedAccessKey=xxxx";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Azure.begin(ConnectionString);
  Azure.setCallback(onAzureCallback);
}

void onAzureCallback(uint8_t* rbuf, unsigned int bufLength) {
  Serial.write((byte*)rbuf, (int)bufLength);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if(Azure.connect()) {
      Azure.run();
      if(Serial.available()) {
        int bufLength = Serial.available();
        byte tbuf[bufLength];
        Serial.readBytes(tbuf, bufLength);
        Azure.push((uint8_t*)tbuf, (unsigned int)bufLength);
      }
    }
    else {
      Serial.println("AzureIoTHub not established");
      delay(500);
    }
  }
  else {
    Serial.println("Not connected to the Internet");
    delay(500);
  }
}



