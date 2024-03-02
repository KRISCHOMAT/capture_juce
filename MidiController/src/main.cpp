#include <Arduino.h>
#include "pot.h"
#include "keyboard.h"
#include "button.h"

#define MIDI_CHANNEL 1

const int POT_NUM = 6;

uint8_t keyPins[8] = {9, 8, 7, 6, 5, 4, 3, 2};
uint8_t scale[8] = {0, 2, 3, 5, 7, 9, 10, 12};
Keyboard keyboard(8, keyPins, scale, 60);

Pot pots[POT_NUM] = {
    Pot(A9, 23),
    Pot(A8, 24),
    Pot(A7, 25),
    Pot(A6, 26),
    Pot(A5, 27),
    Pot(A4, 26)};

Button button(10, 22);

void setup()
{
  // Serial.begin(9600);
  usbMIDI.begin();
}

void loop()
{

  keyboard.update();
  button.update();

  for (int i = 0; i < POT_NUM; i++)
  {
    Reading reading = pots[i].getReading();
    if (reading.isUpdated)
    {
      // usbMIDI.sendControlChange(reading.cc, reading.val, MIDI_CHANNEL);
    }
  }
}
