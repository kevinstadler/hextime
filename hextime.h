#define GREENWICH_MERIDIAN 0
// 11° 15' east is 11.25/360th of a full day, which has 24*60*60 seconds, so it's 2700 seconds (45 minutes)
#define FLORENCE_MERIDIAN 2700 // in seconds

// helper function for converting arbitrary longitudes to SI second differences
uint32_t degreesToSeconds(float east);

// convert a unix timestamp (+ms fraction) to 32bit fraction-of-day representation
uint32_t toHexTime(uint32_t ts, uint16_t ms = 0, uint32_t offset = FLORENCE_MERIDIAN);

uint32_t fromHexTime(uint32_t hexTime, uint32_t offset = FLORENCE_MERIDIAN);

// extract individual hex digit values, where most significant digit = 0, least significant = 7
uint8_t hexDigit(uint32_t hexTime, uint8_t digit = 0);

char* printHexTime(uint32_t hexTime, uint8_t n_digits = 2);
