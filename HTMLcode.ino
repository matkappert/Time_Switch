int uptime[4];
#define cssVersion "1.0.5"


String currentTimeDate() {
  String temp;
  temp += "System Time - ";
  temp += hourFormat12();
  temp += ":";
  temp += zeroPrint(minute());
  temp += ":";
  temp += zeroPrint(second());
  if (isPM())
    temp += "PM,&nbsp;&nbsp;";
  else
    temp += "AM,&nbsp;&nbsp;";
  temp += day();
  temp += "/";
  temp += month();
  temp += "/";
  temp += year();

  temp += ". &nbsp;&nbsp;&nbsp; Uptime - ";
  temp += zeroPrint(uptime[3]);
  temp += "d ";
  temp += zeroPrint(uptime[2]);
  temp += "h ";
  temp += zeroPrint(uptime[1]);
  temp += "m ";
  temp += zeroPrint(uptime[0]);
  temp += "s.";
  return temp;
}


void header(int refreshTimeToUse, String TitleToUse) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: keep-alive");  // the connection will be closed after completion of the response
  if (refreshTimeToUse > 0) {
    client.print("Refresh: ");  // refresh the page automatically every x sec
    client.println(refreshTimeToUse);
  }
  else {
    client.print("Refresh: ");  // refresh the page automatically every x sec
    client.println(300);
  }
  client.print("\r\n");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=0.7'></meta>");
  client.println("<meta name='format-detection' content='telephone=no' />");
  client.print("<link rel='apple-touch-icon-precomposed' sizes='114x114' href='");  // 114px
  client.print("http://raw.githubusercontent.com/matkappert/temp/gh-pages/timer114.png");
  client.print("'></link><link rel='icon' type='image/x-icon' href='");  // 64px
  client.print("http://raw.githubusercontent.com/matkappert/temp/gh-pages/timer64.png");
  client.print("'></link>");

  // Head >>
  // Style >>
  client.println("<head>");
  client.println("<style>");
  client.println("/* V1.0.4 *//* Copyright MK, 2015 */ @media screen and (max-width: 600px) {.menu {border-top: solid #E8E8E8 1px;text-align:center;padding:8px;text-transform: uppercase;font-family: Arial;font-size: 12px;background-color:#454545;color:#FFFFFF;display: block;text-decoration: none;}#nav {width:100%; padding:40px 000;list-style-type: none;}.submenu {text-align:center;padding:0px;text-transform: uppercase;font-family: Arial;font-size: 10px;color:#ffffff;}#section {min-width=200px float:top;margin: 0px;padding:10px 10px 50px 10px;}.foottxt {color:#FFFFFF;}}");
  client.println("@media screen and (min-width: 600px) {.menu {border-top: solid #E8E8E8 1px;text-align:center;padding:8px;text-transform: uppercase;font-family: Arial;font-size: 15px;background-color:#454545;color:#FFFFFF;display: block;text-decoration: none;}#nav {list-style-type: none;position:fixed;width:180px;float:left;padding:10px 0px;background-color:#E8E8E8;border-right: solid #454545 1px;left:0px;top:40px;height:100%;}#footnote {position:fixed;width:170px;float:left;left:3px;bottom:17px;height:16px;color:ff0000;}");
  client.println(".submenu {background-color:#f1f1f1;border-top: solid #454545 1px;text-align:center;padding:0px;margin: 13px 0 0;text-transform: uppercase;font-family: Arial;font-size: 12px;color:#000000;}#section {min-width=600px float:top;margin: 0px;padding:60px 30px 100px 200px;top:40px;}.foottxt {color:#606060;font-size: 10px;}}.menu:hover, a:active {background-color: #696969;}.btn1 {text-decoration: none;text-align:center;text-transform: uppercase;font-family: Arial;font-size: 12px;color:#000;margin:auto;display:block;}");
  client.println(".btn {margin: 15px 4px 10px 4px;border: solid #303030 3px;padding: 8px 15px 8px 15px;text-decoration: none;-webkit-appearance: none;border-radius:0px;font-family: Arial;font-size: 15px;background-color:#454545;color:#FFFFFF;}.btn:hover, a:active {background-color: #696969;}.btn1:hover, a:active {background-color:transparent;}html, body {height:100%;}.header {position:fixed;left:0px;top:0px;height:40px;width:100%; font-size: 200%;background-color: #454545;color: #FFFFFF;text-align: center;z-index:1;}");
  client.println(".login {position:fixed;left:0px;top:20%; height:40px;width:100%; font-size: 200%; color: #454545;text-align: center;}.footer { z-index:2; position:fixed;left:0px;bottom:0px;height:20px;width:100%;background-color: #454545;color: #FFFFFF;text-align: center;}");
  client.println("table{width:100%}table,th,td{border:1px solid black;border-collapse:collapse}th,td{padding:5px;text-align:left}table th{background-color:#E3E3E3}");
  // Art >>
  client.println(" .checkmark {margin:auto;display:block;width:22px;height:22px;-ms-transform:rotate(45deg);-webkit-transform:rotate(45deg);transform:rotate(45deg);width:22px;height:22px;background-color:#77B068;border-radius:11px;left:0;top:0;}.checkmark_stem {position:absolute;width:3px;height:13px;background-color:#fff;left:11px;top:4px;}.checkmark_kick {position:absolute;width:5px;height:3px;background-color:#fff;left:7px;top:14px;}.cross {margin:auto;display:block;width:22px;height:22px;-ms-transform:rotate(45deg);-webkit-transform:rotate(45deg);transform:rotate(45deg);width:22px;height:22px;background-color:#B37D7D;border-radius:11px;left:0;top:0;}.cross1 {position:absolute;width:3px;height:17px;background-color:#fff;left:10px;top:3px;}.cross2 {position:absolute;width:17px;height:3px;background-color:#fff;left:3px;top:10px;}");
  // Art <<

  client.println("</style>");
  // Style <<

  client.print("<title>");
  client.print(TitleToUse);
  client.println("</title> ");
  client.print("<a class='header'>");
  client.print(TitleToUse);
  client.println("</a>");

  // Script >>
  client.println("<script>");
  client.print("var i = 1;function refreshData() {var request = new XMLHttpRequest();request.onreadystatechange = function () {if (this.readyState == 4) {if (this.status == 200) {if (this.responseText !== null) {i = i+1;\r\n");
  client.print("var ajaxTime = 'ajax_time=';if (this.responseText.indexOf(ajaxTime) != -1) {this.ajaxTime = this.responseText.replace(ajaxTime, '');document.getElementById('ajax_time').innerHTML = this.ajaxTime;}\r\n");
  client.print("setTimeout(function () {refreshData();}, 1000); }}}}; request.open('POST', 'ajax_time ' + i, true);request.send(null);}\r\n");
  client.print("</script>");
  // Script <<

  client.println("</head>\r\n\r\n");
  // Head <<
  client.println("<body onload=\"refreshData()\">\r\n");
  client.print("<a id='ajax_time' class='footer'>");
  client.print(currentTimeDate());
  client.println("</a>");
  return;
}



// MENU >>

void menuStart() {
  client.println("<div id='nav'>");
  return;
}
void submenuItem(String textToUse) {
  client.print("<li class='submenu'>");
  client.print(textToUse);
  client.println("</li>");
  return;
}

void menuItem(String textToUse, String linkToUse) {
  client.print("<li><a class='menu' href='");
  client.print(linkToUse);
  client.print("'>");
  client.print(textToUse);
  client.println("</a></li>");
  return;
}

void menuEnd() {
  client.print("<div class='foottxt' id='footnote'>Copyright MK, 2015.</div></div><div id='section'>");
  return;
}

// MENU <<


// BUTTONS >>

void gotoPageButton(String linkToUse, String textToUse) {
  client.print("<a class='btn' href='");
  client.print(linkToUse);
  client.print("'>");
  client.print(textToUse);
  client.println("</a>");
  return;
}

void tableButton(String linkToUse, String textToUse) {
  client.print("<a class='btn1' href='");
  client.print(linkToUse);
  client.print("'>");
  client.print(textToUse);
  client.println("</a>");
  return;
}


void submitButton(String textToUse) {
  client.print("<input class='btn' type='submit' value='");
  client.print(textToUse);
  client.println("'>");
  return;
}

// BUTTONS <<




void input(String nameToUse, String typeToUse, String patternToUse, String extraToUse, int widthToUse, String textToPrint, boolean isRequired, boolean isReadonly) {
  // <input name='textbox1' type='text' pattern='[0-9A-Za-z _-]{5,19}' value='1a2b3c' required='true'/>
  client.print("<input name='");
  client.print(nameToUse);
  client.print("' type='");
  client.print(typeToUse);
  client.print("' ");
  if (patternToUse != "") {
    client.print("pattern='");
    client.print(patternToUse);
    client.print("'");
  }
  if (extraToUse != "") {
    client.print(" ");
    client.print(extraToUse);
    client.print(" ");
  }
  client.print("style='width:");
  client.print(widthToUse);
  client.print("px;'");
  if (textToPrint != "") {
    client.print("value='");
    client.print(textToPrint);
    client.print("' ");
  }
  if (isReadonly)
    client.print("disabled='true'");
  if (isRequired)
    client.print("required='ture'");
  client.println("/>");
}


void headingText(String textToUse,  int sizeToUse) {
  // <H1>NETWORK SETTINGS</H1>
  client.print("<H");
  client.print(sizeToUse);
  client.print(">");
  client.print(textToUse);
  client.print("</H");
  client.print(sizeToUse);
  client.print(">");
  return;
}

void paragraph(int numberToUse) {
  if ( numberToUse < 1) {
    client.print(" <br>");
  }
  else {
    while ( numberToUse > 0) {
      client.println("&nbsp;</p>");
      numberToUse -- ;
    }
  }
  return;
}


void space(int numberToUse) {
  while ( numberToUse >= 1) {
    client.print("&nbsp;");
    numberToUse -- ;
  }
  return;
}




void endForm() {
  client.print("</form> ");
  return;
}

void startForm(String textToUse) {
  client.print("<form method='get' action='");
  client.print( textToUse);
  client.print("'>");
  return;
}



void rebootPage(String IPaddress) {
  String link = "http://" + IPaddress;

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.print("Refresh:6; URL=");
  client.print(link);
  client.println("\r\n");
  client.println(" <!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1' />");
  client.print("Rebooting... ");
  paragraph(1);
  client.print(IPaddress);
  paragraph(1);
  gotoPageButton(link, "Refresh");
  client.println(" <br />");
  client.println(" </html>");
  return;
}

void footer() {
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  return;
}

