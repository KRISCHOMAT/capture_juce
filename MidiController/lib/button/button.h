#pragma once

class Button
{
public:
    Button(uint8_t pin_, uint8_t cc_);
    void update();

private:
    uint8_t pin;
    uint8_t cc;
    boolean active;
};
