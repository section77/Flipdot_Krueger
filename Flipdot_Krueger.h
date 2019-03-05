#ifndef _FLIPDOT_KRUEGER_H
#define _FLIPDOT_KRUEGER_H

#include "Arduino.h"
#include <Flipdot_Control.h>

class Flipdot_Krueger : public Flipdot_Control
{
  public:
    Flipdot_Krueger();
    void flipToBlack(uint8_t x, uint8_t y);
    void flipToColor(uint8_t x, uint8_t y);
  private:
    bool isPointInRange(uint8_t x, uint8_t y);
    void flipDot(uint8_t moduleIndex, uint8_t rowIndex, uint8_t columnIndex, boolean shouldShowYellow);
    void setRowAddress(uint8_t rowIndex);
    void setColumnAddress(uint8_t columnIndex);
    void flipDotAtModule(uint8_t moduleIndex, boolean shouldShowYellow);
    void flipDotYellowAtModule(uint8_t moduleIndex);
    void flipDotBlackAtModule(uint8_t moduleIndex);
};

#endif