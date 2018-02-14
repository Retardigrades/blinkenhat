#include "LEDBand.h"

LEDBand::LEDBand(const CRGBSet &leds, const uint8_t numLEDs, float gamma)
    : leds(leds), numLEDs(numLEDs), gamma(gamma) {}
