#pragma once

struct Reading
{
    boolean isUpdated;
    uint8_t val;
    uint8_t cc;
};

class Pot
{
public:
    Pot(uint8_t pin_, uint8_t cc_);

    Reading getReading();

private:
    float alpha{0.5f};
    uint8_t pin;
    uint8_t cc;
    uint8_t filteredReading{0};
    uint8_t previous{0};
};
