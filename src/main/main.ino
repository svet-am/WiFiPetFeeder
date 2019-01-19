/*

  This example  prints the board's MAC address, and
  scans for available WiFi networks using the NINA module.
  Every ten seconds, it scans again. It doesn't actually
  connect to any network, so no encryption scheme is specified.
  BSSID and WiFi channel are printed

  Circuit:
  * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  This example is based on ScanNetworks

  created 1 Mar 2017
  by Arturo Guadalupi
*/

#include <SPI.h>
#include <WiFiNINA.h>

#define DEBUG 0x00000001

void setup() {
  //Initialize serial and wait for port to open:
  if(DEBUG){
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  }

  // check for the WiFi module:
  if(DEBUG){
    if (WiFi.status() == WL_NO_MODULE) {
      Serial.println("Communication with WiFi module failed!");
      // don't continue
      while (true);
    }
  }

  String fv = WiFi.firmwareVersion();
  if(DEBUG){
    if (fv < "1.0.0") {
      Serial.println("Please upgrade the firmware");
    }
  }

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  if(DEBUG){
    Serial.print("MAC: ");
  }
  printMacAddress(mac);

  // scan for existing networks:
  if(DEBUG){
    Serial.println();
    Serial.println("Scanning available networks...");
  }
  listNetworks();
}

void loop() {
  delay(10000);
  // scan for existing networks:
  if(DEBUG){
    Serial.println("Scanning available networks...");
  }
  listNetworks();
}

void listNetworks() {
  // scan for nearby networks:
  if(DEBUG){
    Serial.println("** Scan Networks **");
  }
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    if(DEBUG){
      Serial.println("Couldn't get a WiFi connection");
    }
    while (true);
  }

  // print the list of networks seen:
  if(DEBUG){
    Serial.print("number of available networks: ");
    Serial.println(numSsid);
  }

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    if(DEBUG){
      Serial.print(thisNet + 1);
      Serial.print(") ");
      Serial.print("Signal: ");
      Serial.print(WiFi.RSSI(thisNet));
      Serial.print(" dBm");
      Serial.print("\tChannel: ");
      Serial.print(WiFi.channel(thisNet));
    }
    byte bssid[6];
    if(DEBUG){
      Serial.print("\t\tBSSID: ");
    }
    printMacAddress(WiFi.BSSID(thisNet, bssid));
    if(DEBUG){
      Serial.print("\tEncryption: ");
    }
    printEncryptionType(WiFi.encryptionType(thisNet));
    if(DEBUG){
      Serial.print("\t\tSSID: ");
      Serial.println(WiFi.SSID(thisNet));
      Serial.flush();
    }
  }
  if(DEBUG){
    Serial.println();
  }
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      if(DEBUG){
        Serial.print("WEP");
      }
      break;
    case ENC_TYPE_TKIP:
      if(DEBUG){
        Serial.print("WPA");
      }
      break;
    case ENC_TYPE_CCMP:
      if(DEBUG){
        Serial.print("WPA2");
      }
      break;
    case ENC_TYPE_NONE:
      if(DEBUG){
        Serial.print("None");
      }
      break;
    case ENC_TYPE_AUTO:
      if(DEBUG){
        Serial.print("Auto");
      }
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      if(DEBUG){
        Serial.print("Unknown");
      }
      break;
  }
}

void print2Digits(byte thisByte) {
  if (thisByte < 0xF) {
    if(DEBUG){
      Serial.print("0");
    }
  }
  if(DEBUG){
    Serial.print(thisByte, HEX);
  }
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      if(DEBUG){
        Serial.print("0");
      }
    }
    if(DEBUG){
      Serial.print(mac[i], HEX);
    }
    if (i > 0) {
      if(DEBUG){
        Serial.print(":");
      }
    }
  }
  if(DEBUG){
    Serial.println();
  }
}
