#define FIRST_SEGMENT 4 - (N_DIGITS+1) / 2

#include <LedController.hpp>

#define LED_CONTROL_CLK_PIN D5
#define LED_CONTROL_DATA_PIN D6
#define LED_CONTROL_CS_PIN D7
#define LED_CONTROL_NUM_SEGMENTS 2

LedController<LED_CONTROL_NUM_SEGMENTS, 1> ledController = LedController<LED_CONTROL_NUM_SEGMENTS, 1>(LED_CONTROL_DATA_PIN, LED_CONTROL_CLK_PIN,
    LED_CONTROL_CS_PIN);

void showPeriod(bool on) {
  ledController.setChar(0, 4 + N_DIGITS/2, ' ', on);
}

void setupDisplay() {
  ledController.activateAllSegments();
  ledController.setIntensity(1);
  ledController.clearMatrix();
  showPeriod(true);
}
