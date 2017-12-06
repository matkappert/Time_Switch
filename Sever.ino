void mdns1() {
  client = httpServer.available();

  if (client) {
    String req = client.readStringUntil('\r');
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) {
      Serial.print("Invalid request: ");
      Serial.println(req);
      client.flush();
    }
    else {
      req = req.substring(addr_start + 1, addr_end);
      Serial.print("Request: ");
      Serial.println(req);
      client.flush();
      logoutLastMillis = millis();


      if (req == ("/login")) {
        header(0, deviceName);
        client.print(" <form class='login' name='login' action=\"javascript:location.href = 'LOGINKEY=' + window.document.login.password.value\"><br>PASSWORD REQUIRED</br><input type='password' name='password' autocomplete='on'  /><br><input class='btn' type='submit' value='LOGIN'/></br><noscript>Javascript is required to access this area. Yours seems to be disabled.</noscript> </form>\r\n</body>\r\n</html>\r\n");
        return;
      }

      else if (req == ("/logout")) {
        Adminloggedin = false;
        redirectPage("/login");
        return;
      }


      else if (req == (urlMaker("dashboard"))) {
        header(0, deviceName);
        menubarItems();
        dashboard();
        footer();
        return;
      }

      else if (req.startsWith(urlMaker("edit"))) {
        for (int ch = 0; ch < (sizeof(relayPins) / sizeof(int)); ch++) {
          String temp = "edit/";
          temp += (ch + 1);
          if (req == (urlMaker(temp))) {
            header(0, deviceName);
            menubarItems();
            editPage((ch));
            footer();
            return;
          }
          temp = "edit/";
          temp += (ch);
          temp += "/?=ON";
          if (req == (urlMaker(temp)) ) {
            relayMemory[ch][11] = 1;
            relayMemorySave();
            EEPROM.commit();
          }
          temp = "edit/";
          temp += (ch);
          temp += "/?=OFF";
          if (req == (urlMaker(temp))) {
            relayMemory[ch][11] = 0;
            relayMemorySave();
            EEPROM.commit();
          }
          else if (req.startsWith(urlMaker("edit/ajax_time"))) {
            client.print("ajax_time=");
            client.println(currentTimeDate());
            return;
          }

        }
      }

      else if (req == (urlMaker("network"))) {
        header(0, deviceName);
        menubarItems();
        networkPage();
        footer();
        return;
      }

      else if (req == (urlMaker("wifi"))) {
        header(0, deviceName);
        menubarItems();
        wifi();
        footer();
        return;
      }

      else if (req == (urlMaker("time"))) {
        header(0, deviceName);
        menubarItems();
        timepage();
        footer();
        return;
      }
      else if (req == (urlMaker("log"))) {
        header(0, deviceName);
        menubarItems();
        logpage();
        footer();
        return;
      }

      else if (req == (urlMaker("general"))) {
        header(0, deviceName);
        menubarItems();
        generalPage();
        footer();
        return;
      }


      else if ( req.startsWith(urlMaker("update/")) ) {
        req += "^";
        int chStart = req.indexOf("update/") + 7;
        int chEnd = req.indexOf("/" , chStart);
        int ch = (req.substring(chStart, chEnd).toInt());

        int ontimeHStart = req.indexOf("ONTIME=") + 7;
        int ontimeHEnd = req.indexOf("%3A" , ontimeHStart);
        int ontimeMEnd = req.indexOf("&OFFTIME" , ontimeHStart);

        int offtimeHStart = req.indexOf("&OFFTIME=") + 9;
        int offtimeHEnd = req.indexOf("%3A" , offtimeHStart);
        int offtimeMEnd = req.indexOf("&" , offtimeHStart);


        relayMemory[ch][7] = (req.substring(ontimeHStart, ontimeHEnd)).toInt();
        relayMemory[ch][8] = (req.substring((ontimeHEnd + 3), ontimeMEnd)).toInt();

        int optStart = req.indexOf("&opt=") + 5;
        int optEnd = req.indexOf("&" , optStart);
        String temp = req.substring(optStart, optEnd);
        Serial.println(temp);
        Serial.println(ch);
        if (temp == "Time") {
          relayMemory[ch][9] = (req.substring(offtimeHStart, offtimeHEnd)).toInt();
          relayMemory[ch][10] = (req.substring((offtimeHEnd + 3), offtimeMEnd)).toInt();
        }
        else if (temp == "Interval") {
          int intervalStart = req.indexOf("&OFFINTERVAL=") + 13;
          int intervalEnd = req.indexOf("^" , intervalStart);
          int interval = (req.substring(intervalStart, intervalEnd)).toInt();
          timeDif(relayMemory[ch][7], relayMemory[ch][8], interval, ch, 2);
        }





        int days[7];

        for (int count = 0; count < 7; count++) {
          String urlToUse = "ch";
          urlToUse += count;
          urlToUse += "=";
          int x = req.indexOf(urlToUse) + 4;
          if (x == 3)
            relayMemory[ch][count] = 0;
          else
            relayMemory[ch][count] = 1;
        }

        relayMemorySave();


        EEPROM.commit();
        refreshEprom();

        redirectPage(urlMaker("dashboard"));
        return;
      }


      else if (req.startsWith(urlMaker("trigger?")) ) {
        //guest/appletree/trigger?0=ON

        req += "^";
        int chStart = req.indexOf("trigger?") + 8;
        int chEnd = req.indexOf("=" , chStart);
        int stateEnd = req.indexOf("^" , chEnd);
        int ch = (req.substring(chStart, chEnd).toInt());
        String st = (req.substring((chEnd + 1), stateEnd));

        if (st == "ON") {
          relayTrigger[ch][0] = millis();
        }
        else if (st == "OFF") {
          relayTrigger[ch][0] = 0;
        }
        redirectPage(urlMaker("dashboard"));
      }


      else if ( req.startsWith(urlMaker("a?SSID=")) ) {
        req += "^";
        //a?SSID=Yellow+House+Modem&KEY=appletree&AP=BLUESUN+SETUP&IP=192.168.1.21&PORT=80
        memoryClear(0, 96);

        int ssidStart = req.indexOf("SSID=") + 5;
        int ssidEnd = req.indexOf("&" , ssidStart);
        int passStart = req.indexOf("KEY=", ssidEnd) + 4;
        int passEnd = req.indexOf("&" , passStart);
        int apSsidStart = req.indexOf("AP=", passEnd) + 3;
        int apSsidEnd = req.indexOf("&" , apSsidStart);

        int ip1Start = req.indexOf("IP=", apSsidEnd) + 3;
        int ip1End = req.indexOf("." , ip1Start);
        int ip2Start = req.indexOf(".", ip1End) + 1;
        int ip2End = req.indexOf("." , ip2Start);
        int ip3Start = req.indexOf(".", ip2End) + 1;
        int ip3End = req.indexOf("." , ip3Start);
        int ip4Start = req.indexOf(".", ip3End) + 1;
        int ip4End = req.indexOf("&" , ip4Start);

        int portStart = req.indexOf("PORT=", ip4Start) + 5;
        int portEnd = req.indexOf("^" , portStart);

        localSSID =  req.substring(ssidStart, ssidEnd) + "^";
        localPASS =  req.substring(passStart, passEnd) + "^";
        APssid =  req.substring(apSsidStart, apSsidEnd) + "^";
        httpPort =  req.substring(portStart, portEnd) + "^";
        String tempIP1 =  req.substring(ip1Start, ip1End) + "^";
        String tempIP2 =  req.substring(ip2Start, ip2End) + "^";
        String tempIP3 =  req.substring(ip3Start, ip3End) + "^";
        String tempIP4 =  req.substring(ip4Start, ip4End) + "^";


        memoryWrite(0, 20, localSSID);
        memoryWrite(20, 40, localPASS);
        memoryWrite(40, 60, APssid);
        memoryWrite(60, 80, APpass);
        memoryWrite(80, 83, tempIP1);
        memoryWrite(83, 86, tempIP2);
        memoryWrite(86, 89, tempIP3);
        memoryWrite(89, 92, tempIP4);
        memoryWrite(92, 96, httpPort);

        // localSSID: 0,20
        // localPASS: 20, 40
        // APssid: 40, 60
        // APpass: 60, 80
        // localIPaddress  0:80, 83, 1:83, 86, 2:86, 89, 3:89, 92
        // httpServer: 92, 96

        EEPROM.commit();
        refreshEprom();

        rebootPage(IPtoString(localIPaddress[0], localIPaddress[1], localIPaddress[2], localIPaddress[3]));

        restartCountdown = true;
        return;
      }


      else if ( req.startsWith("/LOGINKEY=") ) {
        req += "^";
        int keyStart = req.indexOf("LOGINKEY=") + 9;
        int keyEnd = req.indexOf("^" , keyStart);
        String tempKey =  req.substring(keyStart, keyEnd);
        if (tempKey == HTTPAdminpass) {
          Adminloggedin = true;
          logprint(true, "ADMIN LOGGED IN");
          redirectPage(urlMaker("dashboard"));
        }
        else if (tempKey == HTTPpass) {
          Adminloggedin = false;
          redirectPage(urlMaker("dashboard"));
        }
        else {
          redirectPage("/logout");
          return;
        }
      }

      else if ( req.startsWith(urlMaker( "a?NAME=")) ) {
        req += "^";
        int nameStart = req.indexOf("NAME=") + 5;
        int nameEnd = req.indexOf("&" , nameStart);
        int keyStart = req.indexOf("KEY=") + 4;
        int keyEnd = req.indexOf("^" , keyStart);
        deviceName =  req.substring(nameStart, nameEnd) + "^";
        HTTPpass =  req.substring(keyStart, keyEnd) + "^";


        memoryWrite(120, 140, deviceName);
        memoryWrite(140, 160, HTTPpass);
        // deviceName: 120, 140
        // HTTPpass: 140, 160
        EEPROM.commit();
        refreshEprom();
        redirectPage(urlMaker("general"));
        return;
      }


      else if ( req.startsWith(urlMaker( "?SELECTED=") )) {
        req += "^";
        int ssidStart = req.indexOf("SELECTED=") + 9;
        int ssidEnd = req.indexOf("^" , ssidStart);
        localSSID =  req.substring(ssidStart, ssidEnd) + "^";
        localSSID = replaceString(localSSID, "%20");
        delay(2);
        memoryWrite(0, 20, localSSID);
        EEPROM.commit();
        refreshEprom();
        Serial.print("\r\n\r\nSSID = "); Serial.println(localSSID);
        redirectPage(urlMaker("network"));
        return;
      }


      else if ( req.startsWith(urlMaker("time/SYNC=")) ) {
        req += "^";
        int timeStart = req.indexOf("SYNC=") + 5;
        int timeEnd = req.indexOf("^" , timeStart);
        timetosave = 0;
        String timetosave1 =  req.substring(timeStart, timeEnd);
        timetosave = timetosave1.toInt();
        setSyncProvider(updateTime);
        redirectPage(urlMaker("time"));
        return;
      }


      else if (req.startsWith(urlMaker("ajax_time"))) {
        client.print("ajax_time=");
        client.println(currentTimeDate());
      }



      else if ( req.startsWith(urlMaker("time/POST?")) ) {
        // a?NTPSERVER=time.nist.gov&PORT=2390&ZONE=10
        req += "^";
        int serverStart = req.indexOf("NTPSERVER=") + 10;
        int serverEnd = req.indexOf("&" , serverStart);
        int portStart = req.indexOf("PORT=") + 5;
        int portEnd = req.indexOf("&" , portStart);
        int zoneStart = req.indexOf("ZONE=") + 5;
        int zoneEnd = req.indexOf("^" , zoneStart);

        ntpServerName =  req.substring(serverStart, serverEnd) + "^";
        ntpPort =  req.substring(portStart, portEnd).toInt();
        timeZone =  req.substring(zoneStart, zoneEnd).toInt();

        memoryWrite(96, 99, String(timeZone));
        memoryWrite(99, 103, String(ntpPort));
        memoryWrite(103, 120, ntpServerName);

        EEPROM.commit();
        refreshEprom();

        // NTP >>
        udp.begin(ntpPort);
        Serial.print("Local port: ");
        Serial.println(udp.localPort());
        setSyncProvider(getNtpTime);
        // NTP <<
        redirectPage(urlMaker("time"));
        return;
      }


      else if ( req == (urlMaker( "?reboot"))) {
        rebootPage(IPtoString(localIPaddress[0], localIPaddress[1], localIPaddress[2], localIPaddress[3]));
        restartCountdown = true;
        return;
      }

      else if ( req == (urlMaker( "?restore"))) {
        factoryRestore();
        return;
      }

      else {
        redirectPage("/logout");
        return;
      }

    }

  }

}





