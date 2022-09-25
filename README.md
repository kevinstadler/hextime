## `hextime`

The `hextime` library provides functions for converting timestamps based on SI seconds to the more appropriate representation as 32 bit fractions-of-a-day, plus convenience functions for displaying them in [hexadecimal time](https://en.wikipedia.org/wiki/Hexadecimal_time) format.

### Usage

```cpp
#include <hextime.h>

uint32_t ts = 123456789; // some unix epoch timestamp

// by default this is now the fraction of day at the Florence Meridian
uint32_t timeOfDay = toHexTime(ts);
// use the Greenwich (UTC) Meridian instead
uint32_t timeOfDayAtGreenWich = toHexTime(ts, 0);

// get one hex digit
uint8_t hexHour = hexDigit(timeOfDay);
uint8_t hexMinute = hexDigit(timeOfDay, 1);

// get a whole 4 hex digit representation with leading period
// (don't forget to clean up the length 6 array after!)
char *hexString = printHexTime(timeOfDay, 4);
```

### Prior art

* The spiritual ancestor of all hexadecimal time representations is probably John W. Nystrom's [Tonal system](https://en.wikipedia.org/wiki/Tonal_system) (1859/1863)
* In the early days of the internet, Mark V. Rogers and Pete Boardman proposed [some new terminology and modifications to hexadecimal time representations](http://www.intuitor.com/hex/hexclock.html)
* Steffen Eitner maintains the wonderful (if woefully analog) [Konsensuhr](http://www.steffen-eitner.homepage.t-online.de/tempilo/tempkons.htm), alongside some other hexadecimal clocks with more fun digits.
* The official website of the [International Bureau for hexadecimal metrology](http://hexadecimal.florencetime.net/) contains all information regarding the True Hexadecimal Prime Meridian (through Florence)
* the Futile Software Corporation also provides an online reference implementation and conversion tool for [Florence Universal Hexadecimal Mean Time](https://thiswasyouridea.com/time/)
* (Jack Hughes [The Colour Clock](http://thecolourclock.com/) is a fun idea, but sadly the time conversion implementation seems off.)

### License

This library is provided without warranty under some appropriate FOSS license.
