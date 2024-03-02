#ifndef Keyboard_H
#define Keyboard_H

class Keyboard
{
private:
    enum KeyboardState
    {
        Latch,
        Normal
    };
    struct Key
    {
        uint8_t pin;
        uint8_t note;
        boolean active;
    };

public:
    Keyboard(uint8_t numKeys_, uint8_t *pins, uint8_t *scale, uint8_t lowestNote_);
    ~Keyboard();
    void update();
    void setKeyboardState(KeyboardState newState);

private:
    uint8_t numKeys;
    uint8_t lowestNote;
    Key *keys;
    int debounceDelay;
    KeyboardState keyboardState;
};

#endif