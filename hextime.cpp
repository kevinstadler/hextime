#include "hextime.h"

#define DAY_SECONDS (24 * 60 * 60)
const uint32_t SECONDFRACTION_BASE = DAY_SECONDS * 256;

uint32_t degreesToSeconds(float easting) {
  return (DAY_SECONDS * easting) / 360;
}

// hex time is represented as the 32 post-comma fractions of the day, which means a
// theoretical resolution of up to 8 hex digits
uint32_t toHexTime(uint32_t ts, uint16_t ms, uint32_t offset) {
  // up to 25 bit (17 bit for seconds in day, last 8 bit encode 256ths of a second)
  uint64_t secondFractions = (((ts + offset) % DAY_SECONDS) << 8) | ((ms << 8) / 1000);
  // convert from base 86400*256 to 2**32 -- need more than 32 bit in between..
  return (secondFractions << 32) / SECONDFRACTION_BASE;
}

uint32_t fromHexTime(uint32_t hexTime, uint32_t offset) {
  return 0;
}

uint8_t hexDigit(uint32_t hexTime, uint8_t digit) {
  return (hexTime >> (28 - 4*digit)) & 0x0F;
}

char* printHexTime(uint32_t hexTime, uint8_t n_digits) {
  char format[6];
  sprintf(format, "%%0%ux", n_digits);
  char *str = new char[n_digits+2];
  sprintf(str, format, hexTime >> (32 - 4 * n_digits));
  return str;
}
