#include <Arduino.h>
#include "pot.h"

Pot::Pot(uint8_t pin_, uint8_t cc_) : pin(pin_), cc(cc_){};

Reading Pot::getReading()
{
    uint8_t newReading = map(analogRead(pin), 0, 1024, 0, 127);
    filteredReading = alpha * newReading + (1 - alpha) * filteredReading;
    filteredReading = newReading == 127 ? newReading : filteredReading;
    Reading reading{previous != filteredReading, filteredReading, cc};
    previous = filteredReading;
    return reading;
}