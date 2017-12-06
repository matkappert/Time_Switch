

void refreshEprom() {
  EEPROM.begin(512);
  localSSID  = memoryRead(0, 20);
  localPASS = memoryRead(20, 40);
  APssid = memoryRead(40, 60);
  //APpass = memoryRead(60, 80);
  localSSID.replace('+', ' ');
  localPASS.replace('+', ' ');
  APssid.replace('+', ' ');
  APpass.replace('+', ' ');
  localIPaddress[0] = memoryRead(80, 83).toInt();
  localIPaddress[1] = memoryRead(83, 86).toInt();
  localIPaddress[2] = memoryRead(86, 89).toInt();
  localIPaddress[3] = memoryRead(89, 92).toInt();
  httpPort = memoryRead(92, 96);
  timeZone = memoryRead(96, 99).toInt();
  ntpPort = memoryRead(99, 103).toInt();
  ntpServerName = memoryRead(103, 120);
  deviceName = memoryRead(120, 140);
  HTTPpass = memoryRead(140, 160);
  deviceName.replace('+', ' ');
  HTTPpass.replace('+', ' ');

  int memoryAddressCount = memoryStartAddress;
  for (int chCount = 0; chCount < (sizeof(relayPins) / sizeof(int)); chCount++) {
    for (int dataCount = 0; dataCount < 7; dataCount++) {

      relayMemory[chCount][dataCount] = memoryRead(memoryAddressCount, (memoryAddressCount + 1)).toInt();
      memoryAddressCount++;
    }
    for (int dataCount = 7; dataCount < 11; dataCount++) {
      relayMemory[chCount][dataCount] = memoryRead(memoryAddressCount, (memoryAddressCount + 2)).toInt();
      memoryAddressCount += 2;
    }
    relayMemory[chCount][11] = memoryRead(memoryAddressCount, (memoryAddressCount + 1)).toInt();
    memoryAddressCount++;
  }



  //
  //
  // localSSID: 0,20
  // localPASS: 20, 40
  // APssid: 40, 60
  // APpass: 60, 80
  // localIPaddress  0:80, 83, 1:83, 86, 2:86, 89, 3:89, 92
  // httpPort: 92, 96
  //
  // timeZone: 96, 99
  // ntpPort: 99, 103
  // ntpServerName: 103, 120
  //
  // deviceName: 120, 140
  // HTTPpass: 140, 160
  //
}

void relayMemorySave() {

  int memoryAddressCount = memoryStartAddress;
  for (int chCount = 0; chCount < (sizeof(relayPins) / sizeof(int)); chCount++) {

    for (int dataCount = 0; dataCount < 7; dataCount++) {
      memoryWrite(memoryAddressCount, (memoryAddressCount + 1), String(relayMemory[chCount][dataCount]));
      memoryAddressCount++;
    }
    for (int dataCount = 7; dataCount < 11; dataCount++) {
      memoryWrite(memoryAddressCount, (memoryAddressCount + 2), String(relayMemory[chCount][dataCount]));
      memoryAddressCount += 2;
    }
    memoryWrite(memoryAddressCount, (memoryAddressCount + 1), String(relayMemory[chCount][11]));
    memoryAddressCount++;
  }
}

String memoryRead(int startToUse, int endToUse) {
  String temp = "";
  char x;
  for (int i = startToUse; i < endToUse; ++i)
  {

    x = char(EEPROM.read(i));
    if (x == '^') {
      break;
    }
    else {
      temp += x;
    }
  }

  return temp;
}

void memoryClear(int startToUse, int endToUse) {
  for (int i = startToUse; i < endToUse; ++i)
  {
    EEPROM.write(i, '0');
  }
  EEPROM.commit();
}

void memoryWrite(int startToUse, int endToUse, String textToUse) {
  int count = 0;
  for (int i = startToUse; i < endToUse; ++i)
  {
    EEPROM.write(i, textToUse[count]);
    count++;
  }
  // EEPROM.commit();\
}


String zeroPrint(int numberToUse) {
  String temp;
  if (numberToUse < 10) {
    temp = "0";
    temp += numberToUse;
  }
  else {
    temp =  numberToUse;
  }
  return temp;
}

void logprint(boolean useTime, String textToUse) {
  String currenttime;
  String temp;
  if (useTime) {
    currenttime += hour();
    currenttime += ":";
    currenttime += minute();
    currenttime += ":";
    currenttime += second();
    currenttime += " ";
    currenttime += day();
    currenttime += "/";
    currenttime += month();
    currenttime += "/";
    currenttime += year();
  }
  else {
    currenttime += "booting";
  }
  temp += "<";
  temp += currenttime;
  temp += "@";
  temp += textToUse;
  temp +=  ">";
  logFile = temp + logFile;
  Serial.print(currenttime);
  Serial.print(" - ");
  Serial.print(textToUse);
  Serial.println(".");
  return;
}


String replaceString(String stringToUse, String itemToUse) {
  int stringStart = 1 ;
  while ( stringStart != -1) {
    stringStart =  stringToUse.indexOf( itemToUse);
    stringToUse.remove(stringStart, 3);
    stringToUse = stringToUse.substring(0, stringStart) + " " + stringToUse.substring(stringStart);
  }
  return stringToUse;
}


void factoryRestore() {
  memoryClear(0, 500);
  memoryWrite(0, 20, "Yellow House Modem^");
  memoryWrite(20, 40, "appletree^");
  memoryWrite(40, 60, "TIME SWITCH SETUP^");
  memoryWrite(60, 80, "appletree^");
  memoryWrite(80, 83, "192");
  memoryWrite(83, 86, "168");
  memoryWrite(86, 89, "1");
  memoryWrite(89, 92, "40");
  memoryWrite(92, 96, "80^");
  memoryWrite(96, 99, "10");
  memoryWrite(99, 103, "2390");
  memoryWrite(103, 120, "time.nist.gov^");
  memoryWrite(120, 140, "TIME SWITCH^");
  memoryWrite(140, 160, "appletree^");
  EEPROM.commit();
  logprint(false, "factory Restore SUCCESS!");
  restartCountdown = true;
}
