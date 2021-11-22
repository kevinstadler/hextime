#define N_DIGITS 4 // how many hex digits will be shown -- 6 is a BLAZE
#define MAX_DELAY 200 // the max delay controls poti responsiveness

#include <ESP8266WiFi.h>
#include "time.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  WiFi.begin("The_fastest_internet_alive", "N0m0repr0blems!!");
  setupDisplay();

  bool blink;
  while (WiFi.status() != WL_CONNECTED) {
    showPeriod(blink);
    delay(700);
    blink = !blink;
  }
  showPeriod(true);

  // get NTP
  setServer("at.pool.ntp.org");
  waitForSync();
}

void loop() {
  // TODO read poti, update ndigits accordingly
  
  uint32_t fuhmt = toFUHMT(now(), ms(LAST_READ));
//  Serial.printf("%05x\n", fuhmt >> 12);
  for (unsigned int i = 0; i < N_DIGITS; i++) {
    ledController.setDigit(0, FIRST_SEGMENT + i, hexDigit(fuhmt, N_DIGITS - 1 - i), false);
  }
  // look at the first invisible hex digit to determine how long we need to wait
  uint32_t hexTilNextDigit = 16 - hexDigit(fuhmt, N_DIGITS);
  int32_t msTilNextDigit = (hexTilNextDigit*24*60*60*1000) >> (4 * (N_DIGITS+1));
  delay(min(msTilNextDigit, MAX_DELAY));
}
