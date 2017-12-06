time_t updateTime() {
  logprint(false, "NTP Sync SUCCESS");
  return timetosave + timeZone * SECS_PER_HOUR;
}
time_t getNtpTime()
{

  while (udp.parsePacket() > 0) ; // discard any previously received packets
  logprint(false, "NTP Syncing");
  GFX_timeSyncing();
  WiFi.hostByName(ntpServerName.c_str(), timeServerIP);
  sendNTPpacket(timeServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 5000) {
    delay(0);
    int size = udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      logprint(false, "NTP Sycn SUCCESS");
      GFX_timeSynced();
      udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer

      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  logprint(false, "NTP Sync ERROR!");
  return 0; // return 0 if unable to get the time
}

unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

void uptimeUpdate() {
  long seconds = (millis() / 1000);
  if (millis() - uptimeLastUpdate >= 1000) {
    uptime[3] = (seconds / 86400)  ; // days
    uptime[2] = (seconds - (86400 * uptime[3])) / 3600 ; // hours
    uptime[1] = (seconds - ((86400 * uptime[3]) + (3600 * uptime[2]))) / 60; // minutes
    uptime[0] = (seconds - ((86400 * uptime[3]) + (3600 * uptime[2]) + (60 * uptime[1] ))); // seconds
    uptimeLastUpdate = millis();
  }
}
