#include <Arduino.h>
#include "keyboard.h"

Keyboard::Keyboard(uint8_t numKeys_, uint8_t *pins, uint8_t *scale, uint8_t lowestNote_)
    : numKeys(numKeys_), lowestNote(lowestNote_)
{
    keys = new Key[numKeys_];
    for (int i = 0; i < numKeys_; i++)
    {
        pinMode(pins[i], INPUT_PULLDOWN);
        keys[i].pin = pins[i];
        keys[i].active = false;
        keys[i].note = scale[i];
    }
    keyboardState = KeyboardState::Latch;
}

Keyboard::~Keyboard()
{
    delete[] keys;
}

void Keyboard::setKeyboardState(KeyboardState newState)
{
    keyboardState = newState;
    if (keyboardState == KeyboardState::Normal)
    {
        for (int i = 0; i < numKeys; i++)
        {
            Key &currentKey = keys[i];
            currentKey.active = false;
            usbMIDI.sendNoteOff(currentKey.note + lowestNote, 127, 1);
        }
    }
}

void Keyboard::update()
{
    for (int i = 0; i < numKeys; i++)
    {
        Key &currentKey = keys[i];
        uint8_t currentReading = digitalRead(currentKey.pin);

        switch (keyboardState)
        {
        case KeyboardState::Latch:
            if (currentReading)
            {
                currentKey.active = !currentKey.active;
                if (currentKey.active)
                {
                    usbMIDI.sendNoteOn(currentKey.note + lowestNote, 127, 1);
                }
                else
                {
                    usbMIDI.sendNoteOff(currentKey.note + lowestNote, 127, 1);
                }
            }
            break;

        case KeyboardState::Normal:
            if (!currentReading && currentKey.active)
            {
                usbMIDI.sendNoteOff(currentKey.note + lowestNote, 127, 1);
                currentKey.active = false;
            }
            else if (currentReading && !currentKey.active)
            {
                usbMIDI.sendNoteOn(currentKey.note + lowestNote, 127, 1);
                currentKey.active = true;
            }
            break;
        }
    }
}