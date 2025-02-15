#include <cmath>
#include <cstdio>
#include <stdint.h>

#include "hextime.h"

#define MAXVAL 4294967296
#define DAY_SECONDS (24 * 60 * 60)
const uint32_t SECONDFRACTION_BASE = DAY_SECONDS * 256;

uint32_t degreesToFraction(float easting) {
  return 4294967296 * (easting / 360.0);
}

// hex time is represented as the 32 post-comma fractions of the day, which means a
// theoretical resolution of up to 8 hex digits
uint32_t toDayFraction(uint32_t seconds, uint16_t ms) {
  // up to 25 bit (17 bit for seconds in day, last 8 bit encode 256ths of a second)
  uint64_t secondFractions = ((seconds % DAY_SECONDS) << 8) | ((ms << 8) / 1000);
  // convert from base 86400*256 to 2**32 -- need more than 32 bit in between..
  return (secondFractions << 32) / SECONDFRACTION_BASE;
}

uint32_t fromDayFraction(uint32_t dayFraction) {
  return dayFractionToMs(dayFraction) / 1000;
}

uint32_t dayFractionToMs(uint32_t dayFraction) {
  return dayFraction / 49.7102696;
}

uint8_t hexDigit(uint32_t fraction, uint8_t digit, uint32_t offset, uint8_t basis) {
	//fraction += offset;
	// TODO refactor for all powers of 2
	if (basis == 16) {
		uint8_t bitsPerDigit = 4;
		return (fraction >> ( 32 - bitsPerDigit * (digit+1) )) & (basis - 1);
	} else {
		// FIXME
		fraction = (fraction / pow(basis, 4)) * pow(basis, digit+1);
		uint32_t mx = MAXVAL / pow(basis, 4);
		return (fraction / mx) % basis;
		// digit 0 -> val / ( max / basis )
		// digit 1 -> val / ( max / basis**2 )
		/* uint32_t dv = MAXVAL / pow(basis, digit+1); */
		/* return (fraction / dv) % basis; */
	}
}

uint8_t sprintHexTime(char *str, uint32_t hexTime, uint8_t n_digits, uint32_t offset, bool period, bool upper) {
  char format[6];
  sprintf(format, "%s%%0%u%s", period ? "." : "", n_digits, upper ? "X" : "x");
  return sprintf(str, format, (hexTime + offset) >> (32 - 4 * n_digits));
}
