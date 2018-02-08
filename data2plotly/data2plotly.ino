#define ssid       "SSID" // your ssid
#define pass       "password" // your password
#define userName   "username"
#define APIKey     "apikey"
#define fileName   "Climate data simple" // "Climate data"
#define fileopt    "overwrite"
#define nTraces    2
#define maxpoints  "250000"
#define world_readable true
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include <Time.h>
#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11
#define prog_char  char PROGMEM
const boolean kCreatePlot = true;
char *tokens[nTraces] = {"xxxxxxxxxx","xxxxxxxxxx"};
char stream_site[60] = {0};
SoftwareSerial debugSerial(10, 11); // RX, TX
DHT dht(DHTPIN, DHTTYPE);
const PROGMEM  char  cmd_0[] = {"AT\r\n"};
const PROGMEM  char  cmd_1[] = {"ATE1\r\n"};
const PROGMEM  char  cmd_2[] = {"AT+CWMODE=1\r\n"};
const PROGMEM  char  cmd_3[] = {"AT+CIPMODE=0\r\n"};
const PROGMEM  char  cmd_4[] = {"AT+RST\r\n"};
const PROGMEM  char  cmd_5[] = {"AT+CIPMUX=1\r\n"};
const PROGMEM  char  cmd_6[] = {"AT+CWJAP=\""};
const PROGMEM  char  cmd_7[] = {"AT+CIPCLOSE=\""};
const PROGMEM  char  cmd_8[] = {"AT+CIPSTART="};
const PROGMEM  char  cmd_9[] = {",\"TCP\",\""};
const PROGMEM  char  cmd_10[] = {"AT+CIPSEND="};
const PROGMEM  char  cmd_11[] = {","};
const PROGMEM  char  resp_0[] = {"OK"};
const PROGMEM  char  resp_1[] = {"ready"};
const PROGMEM  char  resp_2[] = {"no change"};
const PROGMEM  char  resp_3[] = {"CONNECT"};
const PROGMEM  char  resp_4[] = {"Unlink"};
const PROGMEM  char  resp_5[] = {"Linked"};
const PROGMEM  char  resp_6[] = {">"};
const PROGMEM  char  resp_7[] = {"~"};
const PROGMEM  char  error[] = {"*ERROR "};
const PROGMEM  char  error_0[] = {"0*"};
const PROGMEM  char  error_1[] = {"1*"};
const PROGMEM  char  error_2[] = {"2*"};
const PROGMEM  char  error_3[] = {"3*"};
const PROGMEM  char  error_4[] = {"4*"};
const PROGMEM  char  error_5[] = {"5*"};
const PROGMEM  char  error_6[] = {"6*"};
const PROGMEM  char  error_7[] = {"7*"};
const PROGMEM  char  error_8[] = {"8*"};
const PROGMEM  char  error_9[] = {"9*"};
const PROGMEM  char  error_10[] = {"10*"};
const PROGMEM  char  error_11[] = {"11*"};
const PROGMEM  char  error_12[] = {"12*"};
const PROGMEM  char  error_13[] = {"13*"};
const PROGMEM  char  error_14[] = {"14*"};
const PROGMEM  char  error_15[] = {"15*"};
const PROGMEM  char  error_16[] = {"16*"};
const PROGMEM  char  string_0[] = {"Initializing plot with Plot.ly server...\r\n"};
const PROGMEM  char  string_1[] = {"\",\""};
const PROGMEM  char  string_2[] = {"\""};
const PROGMEM  char  string_3[] = {"\",80"};
const PROGMEM  char  string_4[] = {"POST /clientresp HTTP/1.1\r\n"};
const PROGMEM  char  string_5[] = {"Host: plot.ly:80\r\n"};
const PROGMEM  char  string_6[] = {"User-Agent: Arduino/1.6.7\r\n"};
const PROGMEM  char  string_7[] = {"Content-Type: application/x-www-form-urlencoded\r\n"};
const PROGMEM  char  string_8[] = {"Content-Length: "};
const PROGMEM  char  string_9[] = {"version=2.3&origin=plot&platform=arduino&un="};
const PROGMEM  char  string_10[] = {"&key="};
const PROGMEM  char  string_11[] = {"&args=["};
const PROGMEM  char  string_12[] = {"{\"y\": [], \"x\": [], \"type\": \"scatter\", \"stream\": {\"token\": \""};
const PROGMEM  char  string_13[] = {"\", \"maxpoints\": "};
const PROGMEM  char  string_14[] = {"}}"};
const PROGMEM  char  string_15[] = {", "};
const PROGMEM  char  string_16[] = {"]&kwargs={\"fileopt\": \""};
const PROGMEM  char  string_17[] = {"\", \"filename\": \""};
const PROGMEM  char  string_18[] = {"\", \"world_readable\": "};
const PROGMEM  char  string_19[] = {"true"};
const PROGMEM  char  string_20[] = {"false"};
const PROGMEM  char  string_21[] = {"}"};
const PROGMEM  char  string_22[] = {"Successfully Initialized.\r\n"};
const PROGMEM  char  string_23[] = {"Please visit: \"http://plot.ly/~"};
const PROGMEM  char  string_24[] = {"\"."};
const PROGMEM  char  string_25[] = {"POST / HTTP/1.1\r\n"};
const PROGMEM  char  string_26[] = {"Accept: application/json\r\n"};
const PROGMEM  char  string_27[] = {"Accept-Encoding: gzip, deflate\r\n"};
const PROGMEM  char  string_28[] = {"Connection: close\r\n"};
const PROGMEM  char  string_29[] = {"Content-Length: "};
const PROGMEM  char  string_30[] = {"Content-Type: application/json\r\n"};
const PROGMEM  char  string_31[] = {"Host: stream.plot.ly\r\n"};
const PROGMEM  char  string_32[] = {"plotly-streamtoken: "};
const PROGMEM  char  string_33[] = {"\r\n{\"x\": \""};
const PROGMEM  char  string_34[] = {"\", \"y\": "};
const PROGMEM  char  string_35[] = {"}\n\r\n"};
const PROGMEM  char  string_36[] = {"GET / HTTP/1.1\r\n"};
const PROGMEM  char  string_37[] = {"Host: niradynamics.se\r\n"};
const char* const resp_table[] PROGMEM = {resp_0, resp_1, resp_2, resp_3, resp_4, resp_5, resp_6, resp_7};
char buffer[20] = {0};
float read_value[nTraces] = {0};
uint8_t last_send_time = 61; // Not a valid number

/* ---------------       Setup       --------------- */
void setup() {
  // Setup Serial
  dht.begin();
  debugSerial.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(8000);
  delay(1000);
  esp8266Initialize();
  if (kCreatePlot) {
    plotLyInitialize();
    esp8266Disconnect(0);   // Making sure disconnected
  }
  setSyncProvider(getTimeFunction);
  setSyncInterval(86400); // 24h
  if (timeStatus() == timeSet) debugSerial.println("The internal clock is set!");
}
/* ---------------       Loop        --------------- */
void loop() {
  debugSerial.println("Reading Humidity and Temperature...");
  read_value[0] = dht.readTemperature();
  read_value[1] = dht.readHumidity();
  if (isnan(read_value[0]) || isnan(read_value[1])) { // Check if any reads failed and exit early (to try again).
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  debugSerial.println("Sending Jason...");
  
  time_t t = now();
  if (minute(t) != last_send_time) {
    String timeStr = String(year(t)) + "-" + parseDigits(month(t)) + "-" + parseDigits(day(t)) + " "
                     + parseDigits(hour(t)) + ":" + parseDigits(minute(t)) + ":" + parseDigits(second(t));
    for (int i = 0; i < nTraces; i++) {
      esp8266Connect(0, "stream.plot.ly");
      while (!plotLyPlot(timeStr, read_value[i], tokens[i])) {esp8266Connect(0, "stream.plot.ly");}
      delay(5000); // Wait a few seconds before disconnecting
      esp8266Disconnect(0); // disconnect if send was successful
    }
    last_send_time = minute(t);
  }
}
/* ---------------     Functions     --------------- */
void printConstString2debugSerial(const prog_char str[]) {
  char c;
  if (!str) return;
  while ((c = pgm_read_byte(str++)))
    debugSerial.write(c);
}
void printConstString2esp8266Serial(const prog_char str[]) {
  char c;
  if (!str) return;
  while ((c = pgm_read_byte(str++)))
    Serial.write(c);
}
boolean findResponse(unsigned char a, const prog_char error_str[]) {
  strcpy_P(buffer, (char*)pgm_read_word(&(resp_table[a])));
  if (!Serial.find(buffer)) {
    printConstString2debugSerial(error);
    printConstString2debugSerial(error_str);
    debugSerial.println();
    return false;
  }
  else {
    return true;
  }
}
int readLine(int readch, char *read_buffer, int len) {
  static int pos = 0;
  int rpos;
  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len - 1) {
          read_buffer[pos++] = readch;
          read_buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}
void esp8266Initialize() {
  printConstString2debugSerial(string_0);           // send debug "Initializing plot with Plot.ly server...\r\n"
  // Startup test
  printConstString2esp8266Serial(cmd_0);            // send "AT\r\n"
  if (!findResponse(0, error_0)) {
    while (1) {}
  }                  // find "OK"
  // Turn ECHO off
  printConstString2esp8266Serial(cmd_1);            // send "ATE1\r\n"
  if (!findResponse(0, error_1)) {
    while (1) {}
  }                  // find "OK"
  // Put WiFi into Station mode
  printConstString2esp8266Serial(cmd_2);            // send "AT+CWMODE=1\r\n"
  if (!findResponse(2, error_2)) {                  // find "no change"
    printConstString2esp8266Serial(cmd_2);          // send "AT+CWMODE=1\r\n"
    if (!findResponse(0, error_3)) {
      while (1) {}
    }                // find "OK"
  }
  /* Does not seem to work, but 0 corresponds to default mode
  // Set data transmission mode to no data (0)
  printConstString2esp8266Serial(cmd_3);            // send "AT+CIPMODE=0\r\n"
  if(!findResponse(0,error_4)){while(1){}}          // find "OK"
  */
  // Restart ESP8266
  printConstString2esp8266Serial(cmd_4);            // send "AT+RST\r\n"
  if (!findResponse(0, error_5)) {
    while (1) {}
  }                  // find "ready" (1)
  delay(2000);                                      // find OK and wait 2 seconds instead of finding "ready"
  // Enable multiple connections (MUX)
  printConstString2esp8266Serial(cmd_5);            // send "AT+CIPMUX=1\r\n"
  if (!findResponse(0, error_6)) {
    while (1) {}
  }                  // find "OK"
  printConstString2esp8266Serial(cmd_6);            // send "AT+CWJAP=\"
  Serial.print(ssid);                               // send ssid
  printConstString2esp8266Serial(string_1);         // send "\",\""
  Serial.print(pass);                               // send password
  printConstString2esp8266Serial(string_2);         // send "\""
  Serial.println();
  if (!findResponse(0, error_7)) {
    while (1) {}
  }                  // find "OK"
}
void esp8266Disconnect(unsigned char id) {
  printConstString2esp8266Serial(cmd_7);            // send "AT+CIPCLOSE=\""
  Serial.print(id);                                 // send id
  printConstString2esp8266Serial(string_2);         // send "\""
  Serial.println();
  if (!findResponse(4, error_8)) {                  // find "Unlink"
    printConstString2esp8266Serial(cmd_7);          // send "AT+CIPCLOSE=\""
    Serial.print(id);                               // send id
    printConstString2esp8266Serial(string_2);       // send "\""
    Serial.println();
    while (1) {}
  }
}
void esp8266Connect(unsigned char id, char *url) {
  int p = (int)url;
  printConstString2esp8266Serial(cmd_8);            // send "AT+CIPSTART="
  Serial.print(id);                                 // send id
  printConstString2esp8266Serial(cmd_9);            // send ”,\”TCP\",\""
  url = (char *)p;
  while (*url) {                                    // send URL
    Serial.print(*url);
    url++;
  }
  printConstString2esp8266Serial(string_3);         // send "\",80"
  Serial.println();
  if (!findResponse(5, error_9)) {                  // find "Linked"
    printConstString2esp8266Serial(cmd_8);          // send "AT+CIPSTART="
    Serial.print(id);                               // send id
    printConstString2esp8266Serial(cmd_9);          // send ”,\”TCP\",\""
    url = (char *)p;
    while (*url) {                                  // send URL
      Serial.print(*url);
      url++;
    }
    printConstString2esp8266Serial(string_3);       // send "\",80"
    Serial.println();
    if (findResponse(3, error_10)) {                // find "CONNECT"
      esp8266Disconnect(0);
      printConstString2esp8266Serial(cmd_8);        // send "AT+CIPSTART="
      Serial.print(id);                             // send id
      printConstString2esp8266Serial(cmd_9);        // send ”,\”TCP\",\""
      url = (char *)p;
      while (*url) {                                // send URL
        Serial.print(*url);
        url++;
      }
      printConstString2esp8266Serial(string_3);     // send "\",80"
      Serial.println();
      if (!findResponse(5, error_11)) {
        while (1) {}
      }                // find "Linked"
    }
  }
}
void plotLyInitialize() {
  unsigned int i = 0;
  char charbuffer;
  unsigned int content_length = 136 + strlen(userName) + strlen(fileopt) + nTraces * (87 + strlen(maxpoints)) + (nTraces - 1) * 2 + strlen(fileName); // Changed 126 -> 136 since API key length has changed
  if (world_readable) {
    content_length += 4;
  }
  else {
    content_length += 5;
  }
  String contentLengthString = String(content_length);
  const char* contentLengthConstString = contentLengthString.c_str();
  unsigned int post_length = content_length + 141 + strlen(contentLengthConstString);
  esp8266Connect(0, "plot.ly");                     // id = 0
  printConstString2esp8266Serial(cmd_10);           // send "AT+CIPSEND=”
  Serial.print(0);                                  // id = 0
  printConstString2esp8266Serial(cmd_11);           // send ","
  Serial.println(post_length);
  if (findResponse(6, error_12)) {                  // find ">"
    printConstString2esp8266Serial(string_4);       // send "POST /clientresp HTTP/1.1\r\n"
    printConstString2esp8266Serial(string_5);       // send "Host: plot.ly:80\r\n"
    printConstString2esp8266Serial(string_6);       // send "User-Agent: Arduino/1.6.7\r\n"
    printConstString2esp8266Serial(string_7);       // send "Content-Type: application/x-www-form-urlencoded\r\n"
    printConstString2esp8266Serial(string_8);       // send "Content-Length: "
    Serial.print(content_length);
    Serial.println();
    Serial.println();
    printConstString2esp8266Serial(string_9);       // send "version=2.3&origin=plot&platform=arduino&un="
    Serial.print(userName);                         // send userName
    printConstString2esp8266Serial(string_10);      // send "&key="
    Serial.print(APIKey);                           // send APIKey
    printConstString2esp8266Serial(string_11);      // send "&args=["
    for (int i = 0; i < nTraces; i++) {
      printConstString2esp8266Serial(string_12);    // send "{\"y\": [], \"x\": [], \"type\": \"scatter\", \"stream\": {\"token\": \""
      Serial.print(tokens[i]);                      // send token
      printConstString2esp8266Serial(string_13);    // send "\", \"maxpoints\": "
      Serial.print(maxpoints);                      // send maxpoints
      printConstString2esp8266Serial(string_14);    // send "}}"
      if (nTraces > 1 && i != nTraces - 1) {
        printConstString2esp8266Serial(string_15);  // send ", "
      }
    }
    printConstString2esp8266Serial(string_16);      // send "]&kwargs={\"fileopt\": \""
    Serial.print(fileopt);                          // send fileopt
    printConstString2esp8266Serial(string_17);      // send "\", \"filename\": \""
    Serial.print(fileName);                         // send fileName
    printConstString2esp8266Serial(string_18);      // send "\", \"world_readable\": "
    if (world_readable) {
      printConstString2esp8266Serial(string_19);    // send "true"
    }
    else {
      printConstString2esp8266Serial(string_20);    // send "false"
    }
    printConstString2esp8266Serial(string_21);      // send "}"
    if (findResponse(7, error_13)) {                // find "~"
      i = 0;
      while (1) {
        while (!Serial.available()) {}
        charbuffer = Serial.read();
        if (charbuffer == 34) {
          break;
        }
        stream_site[i] = charbuffer;
        i++;
      }
      if (!findResponse(0, error_14)) {             // find "OK"
        while (1) {}
      }
      printConstString2debugSerial(string_22);      // send debug "Successfully Initialized.\r\n"
      printConstString2debugSerial(string_23);      // send debug "Please visit: \"http://plot.ly/~"
      i = 0;
      while (stream_site[i]) {
        debugSerial.print(stream_site[i]);
        i++;
      }
      printConstString2debugSerial(string_24);      // send debug "\"."
      debugSerial.println();
    }
    else {
      while (1) {}
    }
  }
  else {
    while (1) {}
  }
}
bool plotLyPlot(String xString, float y, char *token) {
  String yString = String(y);
  const char* xConstString = xString.c_str();
  const char* yConstString = yString.c_str();
  unsigned int jason_length = 16 + strlen(xConstString) +  strlen(yConstString);
  String jasonLengthString = String(jason_length);
  const char* jasonLengthConstString = jasonLengthString.c_str();
  unsigned int post_length = 230 + jason_length + strlen(jasonLengthConstString);
  printConstString2esp8266Serial(cmd_10);           // send "AT+CIPSEND=”
  Serial.print(0);                                  // id = 0
  printConstString2esp8266Serial(cmd_11);           // send ","
  Serial.println(post_length);
  if (findResponse(6, error_15)) {                  // find ">"
    printConstString2esp8266Serial(string_25);      // send "POST / HTTP/1.1\r\n"                                       17 bytes
    printConstString2esp8266Serial(string_26);      // send "Accept: application/json\r\n"                              26 bytes
    printConstString2esp8266Serial(string_27);      // send "Accept-Encoding: gzip, deflate\r\n"                        32 bytes
    printConstString2esp8266Serial(string_28);      // send "Connection: close\r\n"                                     19 bytes
    printConstString2esp8266Serial(string_29);      // send "Content-Length: "                                          16 bytes
    Serial.print(jason_length);
    Serial.print("\r\n");                           // send "\r\n"                                                       2 bytes
    printConstString2esp8266Serial(string_30);      // send "Content-Type: application/json\r\n"
    printConstString2esp8266Serial(string_31);      // send "Host: stream.plot.ly\r\n"                                  22 bytes
    printConstString2esp8266Serial(string_6);       // send "User-Agent: Arduino/1.6.7\r\n"                             27 bytes
    printConstString2esp8266Serial(string_32);      // send "plotly-streamtoken: "                                      20 bytes
    while (*token) {                                // send token                                                       10 bytes
      Serial.print(*token);
      token++;
    }
    Serial.print("\r\n");                           // send "\r\n"                                                       2 bytes
  }
  else {
    return false;
  }
  printConstString2esp8266Serial(string_33);        // send "\r\n{\"x\": \""                                             2 bytes + 7 bytes JSON
  Serial.print(xString);                            // send x
  printConstString2esp8266Serial(string_34);        // send "\", \"y\": "                                                8 bytes JSON
  Serial.print(y);                                  // send y
  printConstString2esp8266Serial(string_35);        // send "}\n\r\n"                                                    3 bytes + 1 bytes JSON
  if (findResponse(0, error_16)) {                  // find "OK"
    debugSerial.println("Sent data!");
    return true;
  }
  else {
    debugSerial.println("*Couldn't send data!!*");
    return false;
  }
}
time_t getTimeFunction() {
  esp8266Connect(1, "niradynamics.se");
  unsigned int post_length = 117;
  printConstString2esp8266Serial(cmd_10);           // send "AT+CIPSEND=”
  Serial.print(1);                                  // id = 1
  printConstString2esp8266Serial(cmd_11);           // send ","
  Serial.println(post_length);
  if (findResponse(6, error_15)) {                  // find ">"
    printConstString2esp8266Serial(string_36);      // send "GET / HTTP/1.1\r\n"                                        16 bytes
    printConstString2esp8266Serial(string_27);      // send "Accept-Encoding: gzip, deflate\r\n"                        32 bytes
    printConstString2esp8266Serial(string_28);      // send "Connection: close\r\n"                                     19 bytes
    printConstString2esp8266Serial(string_37);      // send "Host: niradynamics.se\r\n"                                 23 bytes
    printConstString2esp8266Serial(string_6);       // send "User-Agent: Arduino/1.6.7\r\n"                             27 bytes
    if (findResponse(0, error_16)) {                // find "OK"
      debugSerial.println("Sent request for date and time!");
    }
    else {
      debugSerial.println("*Couldn't send request for date and time!!*");
      return 0;
    }
  }
  long time_ms = millis();
  long time_lim = 60000; // wait on answer for maximum 60 seconds
  TimeElements tm;
  time_t t = 0;
  while (true) {
    if (readLine(Serial.read(), stream_site, 80) > 0) {
      if (String(stream_site).substring(0, 5) == "Date:") {
        String secondStr = extractValFromDateTimeString(String(stream_site), 19, 7, 9); // Second
        String minuteStr = extractValFromDateTimeString(String(stream_site), 19, 4, 6); // Minute
        String hourStr = extractValFromDateTimeString(String(stream_site), 19, 1, 3); // Hour
        String weekDayStr = translateWeekDay(extractValFromDateTimeString(String(stream_site), 1, 1, 4)); // Weekday
        String dayStr = extractValFromDateTimeString(String(stream_site), 7, 1, 3); // Day
        String monthStr = translateMonth(extractValFromDateTimeString(String(stream_site), 12, 1, 4)); // Month
        String yearStr = extractValFromDateTimeString(String(stream_site), 15, 1, 5); // Year
        tm.Second = secondStr.toInt();
        tm.Minute = minuteStr.toInt();
        tm.Hour   = hourStr.toInt();
        tm.Wday   = weekDayStr.toInt();
        tm.Day    = dayStr.toInt();
        tm.Month  = monthStr.toInt();
        tm.Year   = yearStr.toInt() - 1970;
        t = makeTime(tm);
      }
      else if ( (String(stream_site).substring(0, 3) == "OK") || (millis() > (time_ms + time_lim)) ) {
        break;
      }
    }
  }
  esp8266Disconnect(1); // Making sure disconnected
  return t;
}
/* ---------------    Time + Date    --------------- */
String extractValFromDateTimeString(String dateTime, uint8_t search_ind, uint8_t start_ind, uint8_t stop_ind) {
  uint8_t first_space_ind = dateTime.indexOf(' ', search_ind); // dateTime example: Date: Mon, 15 Jan 2018 19:06:13 GMT
  String dateTimeStr = dateTime.substring(first_space_ind + start_ind, first_space_ind + stop_ind);
  return dateTimeStr;
}
String translateMonth(String monthStr) {
  if (monthStr.equals(String("Jan"))) return String("01");
  if (monthStr.equals(String("Feb"))) return String("02");
  if (monthStr.equals(String("Mar"))) return String("03");
  if (monthStr.equals(String("Apr"))) return String("04");
  if (monthStr.equals(String("May"))) return String("05");
  if (monthStr.equals(String("Jun"))) return String("06");
  if (monthStr.equals(String("Jul"))) return String("07");
  if (monthStr.equals(String("Aug"))) return String("08");
  if (monthStr.equals(String("Sep"))) return String("09");
  if (monthStr.equals(String("Oct"))) return String("10");
  if (monthStr.equals(String("Nov"))) return String("11");
  if (monthStr.equals(String("Dec"))) return String("12");
}
String translateWeekDay(String weekDayStr) {
  if (weekDayStr.equals(String("Mon"))) return String("01");
  if (weekDayStr.equals(String("Tue"))) return String("02");
  if (weekDayStr.equals(String("Wed"))) return String("03");
  if (weekDayStr.equals(String("Thu"))) return String("04");
  if (weekDayStr.equals(String("Fri"))) return String("05");
  if (weekDayStr.equals(String("Sat"))) return String("06");
  if (weekDayStr.equals(String("Sun"))) return String("07");
}
String parseDigits(uint8_t number) {
  if (number > 9) return String(number);
  else return "0" + String(number);
}

