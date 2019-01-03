#include "Arduino.h"
#include "Flipdot_Krueger.h"

// pin assignments
const uint8_t ROW_1 = 2;
const uint8_t ROW_2 = 3;
const uint8_t ROW_3 = 4;
const uint8_t ROW_4 = 5;
const uint8_t COLUMN_1 = 6;
const uint8_t COLUMN_2 = 7;
const uint8_t COLUMN_3 = 8;
const uint8_t COLUMN_4 = 9;
const uint8_t MODULE_1 = 10;
const uint8_t MODULE_2 = 11;
const uint8_t DATA = 12;
const uint8_t ENABLE = 13;

const uint8_t MODULE_PINS[] = {MODULE_1, MODULE_2};
const uint8_t COLUMN_BIT_PINS[] = {COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4};
const uint8_t ROW_BIT_PINS[] = {ROW_1, ROW_2, ROW_3, ROW_4};
const uint8_t MATRIX_HEIGHT = 16;
const uint8_t MODULE_WIDTH = 16;
const uint8_t MATRIX_WIDTH = sizeof(MODULE_PINS) * MODULE_WIDTH;

const int FLIP_PULSE_WIDTH_IN_MYS = 500;
const int PAUSE_BETWEEN_DOT_FLIPS_IN_MS = 0;

Flipdot_Krueger::Flipdot_Krueger() {
  pinMode(ROW_1, OUTPUT);
  pinMode(ROW_2, OUTPUT);
  pinMode(ROW_3, OUTPUT);
  pinMode(ROW_4, OUTPUT);
  pinMode(COLUMN_1, OUTPUT);
  pinMode(COLUMN_2, OUTPUT);
  pinMode(COLUMN_3, OUTPUT);
  pinMode(COLUMN_4, OUTPUT);
  pinMode(MODULE_1, OUTPUT);
  pinMode(MODULE_2, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  digitalWrite(ROW_1, LOW);
  digitalWrite(ROW_2, LOW);
  digitalWrite(ROW_3, LOW);
  digitalWrite(ROW_4, LOW);
  digitalWrite(COLUMN_1, LOW);
  digitalWrite(COLUMN_2, LOW);
  digitalWrite(COLUMN_3, LOW);
  digitalWrite(COLUMN_4, LOW);
  digitalWrite(MODULE_1, LOW);
  digitalWrite(MODULE_2, LOW);
  digitalWrite(DATA, LOW);
  digitalWrite(ENABLE, LOW);
}

bool Flipdot_Krueger::isPointInRange(uint8_t x, uint8_t y) {
  if (x < 0 || x >= MATRIX_WIDTH) {
    return false;
  }

  if (y < 0 || y >= MATRIX_HEIGHT) {
    return false;
  }

  return true;
}

void Flipdot_Krueger::flipToBlack(uint8_t x, uint8_t y) {
  if (!isPointInRange(x, y)) {
    return;
  }

  uint8_t moduleIndex = x / 16;
  uint8_t rowIndex = (MATRIX_HEIGHT - 1) - y;
  uint8_t columnIndex = (MATRIX_WIDTH - 1) - x;

  flipDot(moduleIndex, rowIndex, columnIndex, false);
}

void Flipdot_Krueger::flipToColor(uint8_t x, uint8_t y) {
  if (!isPointInRange(x, y)) {
    return;
  }

  uint8_t moduleIndex = x / 16;
  uint8_t rowIndex = (MATRIX_HEIGHT - 1) - y;
  uint8_t columnIndex = (MATRIX_WIDTH - 1) - x;

  flipDot(moduleIndex, rowIndex, columnIndex, true);
}

void Flipdot_Krueger::flipDot(uint8_t moduleIndex, uint8_t rowIndex, uint8_t columnIndex, boolean shouldShowYellow) {
  setRowAddress(rowIndex);
  setColumnAddress(columnIndex);
  flipDotAtModule(moduleIndex, shouldShowYellow);
  
  if (PAUSE_BETWEEN_DOT_FLIPS_IN_MS > 0) {
    delay(PAUSE_BETWEEN_DOT_FLIPS_IN_MS);
  }
}

void Flipdot_Krueger::setRowAddress(uint8_t rowIndex) {
  for (uint8_t rowIndexBit = 0; rowIndexBit < sizeof(ROW_BIT_PINS); rowIndexBit++) {
    boolean isBitSet = bitRead(rowIndex, rowIndexBit);
    if (isBitSet) {
      digitalWrite(ROW_BIT_PINS[rowIndexBit], HIGH);
    } else {
      digitalWrite(ROW_BIT_PINS[rowIndexBit], LOW);
    }
  }
}

void Flipdot_Krueger::setColumnAddress(uint8_t columnIndex) {
  for (uint8_t columnIndexBit = 0; columnIndexBit < sizeof(COLUMN_BIT_PINS); columnIndexBit++) {
    boolean isBitSet = bitRead(columnIndex, columnIndexBit);
    if (isBitSet) {
      digitalWrite(COLUMN_BIT_PINS[columnIndexBit], HIGH);
    } else {
      digitalWrite(COLUMN_BIT_PINS[columnIndexBit], LOW);
    }
  }
}

void Flipdot_Krueger::flipDotAtModule(uint8_t moduleIndex, boolean shouldShowYellow) {
  if (shouldShowYellow) {
    flipDotYellowAtModule(moduleIndex);
  } else {
    flipDotBlackAtModule(moduleIndex);
  }
}

void Flipdot_Krueger::flipDotYellowAtModule(uint8_t moduleIndex) {
  digitalWrite(DATA, HIGH);
  digitalWrite(MODULE_PINS[moduleIndex], HIGH);
  digitalWrite(ENABLE, HIGH);
  delayMicroseconds(FLIP_PULSE_WIDTH_IN_MYS);
  digitalWrite(ENABLE, LOW);
  digitalWrite(MODULE_PINS[moduleIndex], LOW);
}

void Flipdot_Krueger::flipDotBlackAtModule(uint8_t moduleIndex) {
  digitalWrite(DATA, LOW);
  digitalWrite(MODULE_PINS[moduleIndex], HIGH);
  digitalWrite(ENABLE, HIGH);
  delayMicroseconds(FLIP_PULSE_WIDTH_IN_MYS);
  digitalWrite(ENABLE, LOW);
  digitalWrite(MODULE_PINS[moduleIndex], LOW);
}