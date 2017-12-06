void dashboard() {
  String temp;


  headingText("DASHBOARD", 1);
  paragraph(1);

  for (int ch = 0; ch < (sizeof(relayPins) / sizeof(int)); ch++) {
    client.print("<script>function toggleTrigger");
    client.print(ch);
    client.print("(item){var requestpost=new XMLHttpRequest();if(item.className=='btn1 on'){document.getElementById('btnBack");
    client.print(ch);
    client.print("').style.backgroundColor='#77B068';item.className='btn1 off';item.innerHTML=\"<span class='checkmark '><div class='checkmark_stem '></div><div class='checkmark_kick '></div></span>\";requestpost.open('POST','trigger?");
    client.print(ch);
    client.print("=ON',true);requestpost.send(null)}else{document.getElementById('btnBack");
    client.print(ch);
    client.print("').style.backgroundColor='#B37D7D';item.className='btn1 on';item.innerHTML=\"<span class='cross '><div class ='cross1 '> </div><div class='cross2 '></div></span>\";requestpost.open('POST','trigger?");
    client.print(ch);
    client.println("=OFF',true);requestpost.send(null)}}</script>");

    boolean isam = true;
    temp = ("CHANNEL ");
    temp += ch + 1;
    temp += (".");
    headingText(temp, 3);
    client.println(" <table id='t02'> ");
    client.print("<tr><th></th><th>Sun</th><th>Mon</th><th>Tue</th><th>Wed</th><th>Thu</th><th>Fri</th><th>Sat</th></tr> <tr><th>Days</th>");

    for (int count = 0; count < 7; count++) {
      if (relayMemory[ch][count])
        client.print("<td><span class='checkmark'><div class='checkmark_stem'></div><div class='checkmark_kick'></div></span></td>");
      else
        client.print("<td><span class='cross'><div class='cross1'></div><div class='cross2'></div></span></td>");
    }
    client.print("</tr><tr><th>ON</th><td colspan='7'>");
    if (relayMemory[ch][7] > 11)
      isam = false;
    else
      isam = true;
    if (relayMemory[ch][7] > 12)
      temp = zeroPrint((relayMemory[ch][7]) - 12);
    else if (relayMemory[ch][7] == 0)
      temp = "12";
    else
      temp = zeroPrint(relayMemory[ch][7]);


    temp += (":");
    temp += zeroPrint(relayMemory[ch][8]);
    if (isam)
      temp += ("am");
    else
      temp += ("pm");
    client.print(temp);

    client.print("</td></tr><tr><th>OFF</th><td colspan='7'>");
    if (relayMemory[ch][9] > 11)
      isam = false;
    else
      isam = true;
    if (relayMemory[ch][9] > 12)
      temp = zeroPrint((relayMemory[ch][9]) - 12);
    else if (relayMemory[ch][9] == 0)
      temp = "12";
    else
      temp = zeroPrint(relayMemory[ch][9]);

    temp += (":");
    temp += zeroPrint(relayMemory[ch][10]);
    if (isam)
      temp += ("am");
    else
      temp += ("pm");
    client.print(temp);
    client.print("</td></tr><tr><td colspan='4' id='btnBack");
    client.print(ch);
    client.print("' style='background-color: #");
    if (relayMemory[ch][12]) {
      client.print("77B068");
      client.print(" '><a class='btn1 off' onClick='toggleTrigger");
      client.print(ch);
      client.print("(this)'>");
      client.print("<span class='checkmark'><div class='checkmark_stem'></div><div class='checkmark_kick'></div></span>");
    }
    else {
      client.print("B37D7D");
      client.print(" '><a class='btn1 on' onClick='toggleTrigger");
      client.print(ch);
      client.print("(this)'>");
      client.print("<span class='cross'><div class ='cross1'> </div><div class='cross2'></div></span>");
    }


    client.print(" </a></td><td colspan='4'><a class='btn1' href='");
    temp = ("edit/");
    temp += ch + 1;
    client.print(urlMaker(temp));
    client.println("'>edit</a></td></tr></table>");
    paragraph(3);
  }

 headingText("Info", 4);
 client.println("<ul style='list-style-type:disc'><li>DAYS, Selected days timers are enabled.</li><li>ON, Timers switch ON time.</li><li>OFF, Timers switch OFF time.</li><li>TRIGGER, This big button is used to show the current state of the timer, pressing will TIGGER it ON or OFF; When pressed ON, TIGGER will activate for the saved interval regardless of its days and times and deactivated after set time.</li><li>EDIT, Edit the current timer; Links in menu may also be used.</li></ul>");
   return;
}



void editPage(int ch) {
  client.print("<script>");
  client.print("function time(){document.getElementById('radioTime').checked='true';}function interval(){document.getElementById('radioInterval').checked='true';}");
  client.print("function toggleState(item){var requestpost = new XMLHttpRequest(); if(item.className=='btn1 on'){document.getElementById('btnBack').style.backgroundColor='#77B068';item.className='btn1 off'; item.innerHTML=\"<span class='checkmark'><div class='checkmark_stem'></div><div class='checkmark_kick'></div></span>\";    requestpost.open('POST', '");
  client.print(ch);
  client.print("/?=ON', true);requestpost.send(null);}else{document.getElementById('btnBack').style.backgroundColor='#B37D7D';item.className='btn1 on';  item.innerHTML =\"<span class='cross'><div class ='cross1'> </div><div class='cross2'></div></span>\"; requestpost.open('POST', '");
  client.print(ch);
  client.print("/?=OFF', true);requestpost.send(null);}}");
  client.println("</script>");
  String temp;

  temp = ("EDIT CHANNEL ");
  temp += ch + 1;
  temp += (".");
  headingText(temp, 1);
  paragraph(1);

  temp = "update/";
  temp += ch;
  temp += "/";
  startForm(urlMaker(temp));

  client.print("<table><tr><th>State</th><td colspan='7' id='btnBack' style='background-color: #");
  if (relayMemory[ch][11]) {
    client.print("77B068");
    client.print(" '><a class='btn1 off' onClick='toggleState(this)'>");
    client.print("<span class='checkmark'><div class='checkmark_stem'></div><div class='checkmark_kick'></div></span>");
  }
  else {
    client.print("B37D7D");
    client.print(" '><a class='btn1 on' onClick='toggleState(this)'>");
    client.print("<span class='cross'><div class ='cross1'> </div><div class='cross2'></div></span>");
  }

  client.print(" </a></tr><tr></td><th rowspan='2'>Days</th><th>Sun</th><th>Mon</th><th>Tue</th><th>Wed</th><th>Thu</th><th>Fri</th><th>Sat</th></tr><tr>");


  for (int count = 0; count < 7; count++) {
    if (relayMemory[ch][count]) {
      client.print("<td><input type='checkbox' checked='true' name='ch");
      client.print(count);
      client.print("' value='1'></td>");
    }
    else {
      client.print("<td><input type='checkbox' name='ch");
      client.print(count);
      client.print("' value='1'></td>");
    }
  }

  client.print("</tr><tr><th>ON</th><td colspan='7'>");

  temp = zeroPrint((relayMemory[ch][7]));
  temp += ":";
  temp += zeroPrint((relayMemory[ch][8]));
  input("ONTIME", "time", "", "", 200, temp, true, false);

  client.print("</td></tr>  <tr><th>OFF</th> <td colspan='3'>");
  temp = zeroPrint((relayMemory[ch][9]));
  temp += ":";
  temp += zeroPrint((relayMemory[ch][10]));
  input("opt", "radio", "", "id='radioTime' checked", 9, "Time", true, false);
  input("OFFTIME", "time", "", "onClick='time();'", 100, temp, false, false);
  client.print("</td><td>OR</td> <td colspan='3'>");
  input("opt", "radio", "", "id='radioInterval'", 9, "Interval", true, false);
  input("OFFINTERVAL", "number", "", "onClick='interval();'", 70, timeDif(relayMemory[ch][7], relayMemory[ch][8], relayMemory[ch][9], relayMemory[ch][10], 1), false, false);

  client.println("</td></tr></table>");
  paragraph(1);
  gotoPageButton(urlMaker("dashboard"), "Cancel");
  submitButton("Save");
  paragraph(2);
  headingText("Info", 4);
 client.println("<ul style='list-style-type:disc'><li>STATE, Switches ON or OFF this timer.</li><li>DAYS, Select the days to enable this timer.</li><li>ON, Switch ON time, This time should be earlier then switch OFF time.</li><li>OFF, Select either a set time to switch OFF or a interval in minutes from ON time, OFF time should be later then ON time.</li><li>INTERVAL, The time period between ON and OFF that will be used as the trigger on the Dashboard and this timer.</li></ul>");
   return;
}


String timeDif(int t1, int t2, int t3, int t4, int output) {
  String temp;

  if (output == 0) { // Input:HH:MM HH:MM, Outputs HH:MM
    int tMM = t2 + t4;
    int tHH = t3 - t1;
    while (tMM >= 60) {
      tHH++;
      tMM = tMM - 60;
    }
    temp += (tHH);
    temp += (":");
    temp += (tMM);
    return temp;
  }

  //   t1:t2 t3:t4
  else if (output == 1) { // Input:HH:MM HH:MM, Outputs MM  
    int tMM = t4 - t2;
    int tHH = t3 - t1;

    if (t2 > t4) {
      tMM = tMM + 60;
      tHH--;
      while (tHH >= 1) {
        tHH--;
        tMM = tMM + 60;
      }
    }
    else {
      if (t3 > t1)
        while (tHH >= 1) {
          tHH--;
          tMM = tMM + 60;
        }
    }
    temp += (tMM);
    return temp;
  }

  else if (output == 2) { // Input:HH:MM MM:CH, Outputs HH:MM
    int tMM = t2 + t3;
    int tHH = t1;
    while (tMM >= 60) {
      tHH++;
      tMM = tMM - 60;
    }
    temp += (tHH);
    temp += (":");
    temp += (tMM);
    relayMemory[t4][9] = tHH;
    relayMemory[t4][10] = tMM;
    Serial.println(temp);
    return temp;
  }

  else {
    return "error";
  }
}




void generalPage() {
  startForm("a");
  headingText("GENERAL SETTINGS", 1);
  paragraph(1);
  client.print("<table id='t01'><tr><td>DEVICE NAME</td><td>");
  input("NAME", "text", "[0-9A-Za-z _-]{1,19}", "", 150, deviceName , true, !Adminloggedin);
  client.print("</td></tr><tr><td>SYSTEM VERSION</td><td>");
  client.print(systemVersion);
  client.print("</td></tr><tr><td>CSS VERSION</td><td>");
  client.print(cssVersion);
  client.print("</td></tr><tr><td>PASSWORD</td> <td <td colspan='2'>");
  input("KEY", "password", "[0-9A-Za-z _-]{6,19}", "", 150, HTTPpass , false, !Adminloggedin);
  client.println("</td></tr></table>");
  paragraph(1);
  gotoPageButton(urlMaker("dashboard"), "Cancel");
  submitButton("Save");
  paragraph(1);
  gotoPageButton(urlMaker("?reboot"), "Reboot");
  gotoPageButton(urlMaker("?restore"), "Restore Factory Defaults");
  paragraph(2);
  headingText("Info", 4);
  client.println("<ul style='list-style-type:disc'><li>DEVICE NAME, Nickname used to identify this device; Name will be used as webapp titel.</li><li>SYSTEM VERSION, Current software version on this device.</li><li>CSS VERSION, Current cascading style sheets version on this device.</li><li>PASSWORD, Guest login password (admin login required).</li></ul>");
    endForm();
  return;
}


void networkPage() {
  startForm("a");
  headingText("NETWORK SETTINGS", 1);
  paragraph(1);
  client.print("<table id='t01'><tr><td>SSID</td><td>");
  input("SSID", "text", "", "",  150, localSSID , false, false);
  client.print("</td><td style='width:32px;'>");
  tableButton(urlMaker( "wifi"), "scan") ;
  client.print("</td></tr><tr><td>PASSWORD</td><td colspan='2'>");
  input("KEY", "password", "", "", 150, localPASS , true, false);
  client.print( "</td></tr><tr><td>ACCESSPOINT</td><td colspan='2'>");
  input("AP", "text", "[0-9 A-Z a-z _ - ]{5,19}", "", 150, APssid, true, false);
  client.print("</td></tr><tr><td>IP ADDRESS</td><td colspan = '2'>");
  input("IP", "text", "[0-9.]{7,15}", "", 100, IPtoString(localIPaddress[0], localIPaddress[1], localIPaddress[2], localIPaddress[3]), true, false);
  client.print("</td></tr><tr><td>PORT</td><td colspan = '2'>");
  input("PORT", "text", "[0-9]{1,4}", "", 40, String(httpPort), true, false);
  client.print( "</td></tr><tr><td>MAC ADDRESS</td><td colspan = '2'>");
  client.print( MACtoString());
  client.print( "</td></tr></table> ");
  paragraph(1);
  gotoPageButton(urlMaker("dashboard"), "Cancel");
  submitButton("Save & Reboot");
  paragraph(2);
  headingText("Info", 4);
  client.print("<ul style = 'list-style-type:disc'><li>SSID, Wireless network name, pressing 'EDIT' to scan for local networks.</li><li>ACCESS POINT, When the device can't connect to a network a new network will be created with this SSID name.( 5-19 characters )</li><li>IP ADDRESS, Local network IP address ( e.g. xxx.xxx.xxx.xxx ).</li><li>PORT, HTTP port number ( 0-9999 ).</li><li>MAC ADDRESS, Devices unique Mac address.</li></ul>");
  endForm();
  return;
}

void wifi() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    headingText("NO WIFI NETWORKS FOUND!", 1);
    headingText("Try refreshing the page..", 3);
  }
  else {
    headingText("SELECT WIFI", 1);
    paragraph(1);
    client.print("<table id='t01'><tr><th style='width : 1px; '>No.</th><th>SSID</th><th>SIGNAL</th> <th></th></tr>");
    for (int i = 0; i < n; ++i)
    {
      client.print("<tr><td>");
      client.print(i + 1);
      client.print("</td><td>");
      client.print(WiFi.SSID(i));
      client.print("</td><td style='width: 1px; '>");
      client.print(map(WiFi.RSSI(i), -100, -40, 0, 100));
      client.print("%</td><td style='width: 1px; '><a class='btn1' href='");
      client.print(urlMaker("?SELECTED="));
      client.print(WiFi.SSID(i));
      client.print("'>SELECT</a></td></tr>");
    }

    client.print(" </table>");
    paragraph(1);
    gotoPageButton(urlMaker( "network"), "Back");
    paragraph(2);
    headingText("Info", 4);
    client.print("<ul style='list - style - type : disc'><li>No. WiFi listed number.</li><li>SSID, Local wireless network name.</li><li>SIGNAL, WiFi signal strength in percentage.  (-100dBm to -40dBm)</li><li>SELECT, Pressing will update WiFi settings (reboot for changes to take effect).</li></ul>");
  }
  return;
}

void timepage() {
  startForm(urlMaker("time/POST"));
  headingText("TIME SETTINGS", 1);
  paragraph(1);
  client.print("<table id='t01'><tr><td>SERVER ADDRESS</td><td>");
  input("NTPSERVER", "text", "", "", 150, ntpServerName , false, !Adminloggedin);
  client.print("</td></tr> <tr> <td>SERVER PORT</td><td>");
  input("PORT", "number", "[0-9A-Za-z _-]{5,19}", "", 150, String(ntpPort) , true, !Adminloggedin);
  client.print( "</td> </tr><tr><td>TIME ZONE</td> <td>");
  input("ZONE", "text", "[0-9A-Za-z _-]{1,2}", "", 150, String(timeZone) , true, false);
  client.print( "</td></tr></table>");
  paragraph(1);
  gotoPageButton(urlMaker( "dashboard"), "Cancel");
  submitButton("Save & Update");
  client.print("<input type='button' class='btn' onclick=\"var d = new Date(); var n = d.getTime(); n = n/1000; var linktouse = '");
  client.print(urlMaker("time/SYNC="));
  client.print("' + n; location.href = linktouse; \" value='Sycn From PC' />");
  paragraph(2);
  headingText("Info", 4);
  client.print("<ul style='list-style-type:disc'><li>SERVER ADDRESS, Network Time Protocol (NTP) Server. (time.nist.gov)</li><li>SERVER PORT, NTP conncetion port. (2390) </li><li>TIME ZONE, Local timezone. </li></ul>");
    endForm();
  return;
}

void logpage() {
  startForm("a");
  headingText("SYSTEM LOG", 1);
  paragraph(1);
  client.print("<table id='t01'><tr><th style='width:1px;'>No.</th><th style='width:1px;'>TIME</th><th>MESSAGE</th></tr>");

  int dateStart = 0;
  int dateEnd ;
  int logEnd = 1 ;
  int cont;
  while ( logEnd != logFile.length() - 1) {
    dateStart = logFile.indexOf("<", dateStart) + 1;
    dateEnd = logFile.indexOf("@" , dateStart );
    logEnd = logFile.indexOf(">" , dateEnd);

    client.print( "<tr><td>");
    client.print( cont + 1);
    client.print( "</td><td>");
    client.print(  logFile.substring(dateStart , dateEnd));
    client.print(" </td><td>");
    client.print(  logFile.substring(dateEnd + 1,  logEnd));
    client.print("</td></tr>");
    cont++;
  }
  client.print( "</td></tr></table>");
  return;
}

void menubarItems() {
  menuStart();
  submenuItem("menu");
  menuItem("dashboard", urlMaker("dashboard"));
  for (int chCount = 0; chCount < (sizeof(relayPins) / sizeof(int)); chCount++) {
    String lable = "CHANNEL ";
    lable += chCount + 1;
    String url = "edit/";
    url += chCount + 1;
    menuItem(lable, urlMaker(url));
  }
  
  submenuItem("settings");
  menuItem("general", urlMaker("general"));
  menuItem("network", urlMaker("network"));
  menuItem("time", urlMaker( "time"));
  menuItem("system log", urlMaker("log"));
  submenuItem("user");
  menuItem("logout", " / logout");
  menuEnd();
  return;
}

void redirectPage(String urlToUse) {
  client.print("HTTP/1.1 200 OK \r\n");
  client.print("Content-Type: text/html \r\n");
  client.print("Connection: close \r\n");   // the connection will be closed after completion of the response
  client.print("Refresh:0; URL=");
  client.print(urlToUse);
  client.print("\r\n");
  client.print("<!DOCTYPE HTML> \r\n");
  client.print("<html> \r\n");
  client.print("loading... ");
  client.print("<br /> \r\n");
  client.print("</html> \r\n");
  return;
}


String urlMaker(String urlToUse) {
  String temp;
  temp = "/";
  if (Adminloggedin) {
    temp += "admin/";
    temp += HTTPAdminpass;
    temp += "/";
  }
  else {
    temp += "guest/";
    temp += HTTPpass;
    temp += "/";
  }
  temp += urlToUse;
  return temp;
}




