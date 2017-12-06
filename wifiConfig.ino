boolean testWifi() {

  logprint(false, "Connecting to WiFi..");
  for (int c = 0; c < 60; c++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("\r\n");
      return true;    // Connected
    }
     GFX_wifiConecting();
    delay(500);
    Serial.print(60 - c);   // Print count down timer.
    Serial.print(". ");
  }

  logprint(false, "Connecting to WiFi ERROR..");
  return false; // No Conection
}



void setupAP() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.softAP(APssid.c_str(), APpass.c_str());
  logprint(false, "WiFi AP mode");
  Serial.println(scanForWifi());

  // LOCAL SERVER >>
  httpServer.begin();
  printWifiStatus();
  // http SEVER <<
}

void setupSTA() {
  WiFi.config(IPAddress(localIPaddress[0] , localIPaddress[1] , localIPaddress[2] , localIPaddress[3] ), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  WiFi.mode(WIFI_STA);
  logprint(false, "Connecting to WiFi SUCCESS!");
  GFX_wifiConenected();


  // LOCAL SERVER >>
  httpServer.begin();
  printWifiStatus();
  // LOCAL SEVER <<

  // NTP >>
  udp.begin(ntpPort);
  setSyncProvider(getNtpTime);
  // NTP <<
}


String scanForWifi() {
  String temp;
  int n = WiFi.scanNetworks();
  if (n == 0)
    temp += ("No networks found");
  else
  {
    temp += n;
    temp += (" Networks found");
    temp += ("\r\n");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      temp += (i + 1);
      temp += (": ");
      temp += (WiFi.SSID(i));
      temp += ("  (");
      temp += WiFi.RSSI(i);
      temp += ("dBm) - (");
      temp  +=   (map(WiFi.RSSI(i), -90, -40, 0, 100));
      temp += ("%)");
      temp += ("\r\n");

    }
  }
  return temp;
}

void printWifiStatus() {
  IPAddress ip = WiFi.localIP();
  //
  Serial.println("\r\n###################");
  Serial.print("Local SSID: ");
  Serial.println(localSSID);
  Serial.print("Local IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(httpPort);
  Serial.print("AP SSID: ");
  Serial.println(APssid);
  Serial.print("AP IP Address: ");
  Serial.print(WiFi.softAPIP());
  Serial.print(":");
  Serial.println(httpPort);
  Serial.print("MAC: ");
  Serial.println((MACtoString()));
  Serial.println("###################\r\n");
}


String IPtoString(int ip1, int ip2, int ip3, int ip4) {
  String IPtemp;
  IPtemp += ip1;
  IPtemp += (".");
  IPtemp += ip2;
  IPtemp += (".");
  IPtemp += ip3;
  IPtemp += (".");
  IPtemp += ip4;
  return IPtemp;
}


String MACtoString() {
  String MACtemp;
  byte mac[6];
  WiFi.macAddress(mac);

  String MACtemp0 = (String(mac[0], HEX));
  String MACtemp1 = (String(mac[1], HEX));
  String MACtemp2 = (String(mac[2], HEX));
  String MACtemp3 = (String(mac[3], HEX));
  String MACtemp4 = (String(mac[4], HEX));
  String MACtemp5 = (String(mac[5], HEX));

  MACtemp = MACtemp0 + ":";
  MACtemp += MACtemp1 + ":";
  MACtemp += MACtemp2 + ":";
  MACtemp += MACtemp3 + ":";
  MACtemp += MACtemp4 + ":";
  MACtemp += MACtemp5;

  MACtemp.toUpperCase();
  return MACtemp;
}


