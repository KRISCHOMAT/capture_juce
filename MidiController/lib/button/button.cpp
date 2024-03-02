#include <Arduino.h>
#include "button.h"

Button::Button(uint8_t pin_, uint8_t cc_) : pin(pin_), cc(cc_)
{
    pinMode(pin_, INPUT_PULLDOWN);
}

void Button::update()
{
    uint8_t currentReading = digitalRead(pin);
    if (!currentReading && active)
    {
        usbMIDI.sendControlChange(cc, 0, 1);
    }
    else if (currentReading && !active)
    {
        usbMIDI.sendControlChange(cc, 127, 1);
    }
}