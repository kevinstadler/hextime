#include <ezTime.h>

// 11° 15' east is 11.25/360th of a full day, which has 24*60*60 seconds, so it's 2700 seconds (45 minutes)
#define FLORENCE_OFFSET 2700 // in seconds

#define SECONDFRACTION_BASE (24 * 60 * 60 * 256)
#define SECONDFRACTION_BASE (24 * 60 * 60 * 256)

// 32 post-comma fractions of the day, theoretical resolution up to 8 hex digits...
uint32_t toFUHMT(uint32_t ts, uint16_t ms = 0) {
  // up to 25 bit (17 bit for seconds in day, last 8 bit encode 256ths of a second)
  uint64_t secondFractions = (((ts + FLORENCE_OFFSET) % (24*60*60)) << 8) | ((ms << 8) / 1000);
  // convert from base 86400*256 to 2**24 -- need more than 32 bit in between..
  return (secondFractions << 32) / SECONDFRACTION_BASE;
}

// most significant digit = 0, least significant = 7
byte hexDigit(uint32_t hexTime, byte digit) {
  return (hexTime >> (28 - 4*digit)) & 0xF;
}
