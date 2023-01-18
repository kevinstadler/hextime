#ifndef hextime_h
#define hextime_h

#define GREENWICH_MERIDIAN 0
// 11° 15' east is 11.25/360th of a full day, which has 24*60*60 seconds, so it's 2700 seconds (45 minutes)
#define FLORENCE_MERIDIAN 2700 // in seconds

// helper function for converting arbitrary longitudes (positive only!) to fraction-of-day offsets
uint32_t degreesToFraction(float easting);

// convert a number of SI seconds or unix timestamp (+ms fraction) to 32bit fraction-of-day representation
uint32_t toDayFraction(uint32_t seconds, uint16_t ms = 0);

// return number of SI seconds elapsed in the given fraction of day
uint32_t fromDayFraction(uint32_t dayFraction);

// essentially a rebase from 2**32 to 86400000
uint32_t dayFractionToMs(uint32_t dayFraction);

// extract individual hex digit values, where most significant digit = 0, least significant = 7
uint8_t hexDigit(uint32_t hexTime, uint8_t digit = 0, uint32_t offset = FLORENCE_MERIDIAN);

uint8_t sprintHexTime(char *str, uint32_t dayFraction, uint8_t n_digits, uint32_t offset = FLORENCE_MERIDIAN, bool period = true, bool upper = false);

// returns the number of SI ms until the given digit (starting at 0) will overflow/flip
uint32_t msUntilNextOverflow(uint8_t n_digit, uint32_t seconds, uint16_t ms = 0);

#endif
