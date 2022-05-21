// File for defining pins for the Split Ortholinear Keyboard
// James Stockton
// 19/05/2022


// multiplexing timings
#define LED_WAIT_TIME 10


// multiplexing rows
#define ROW0 0
#define ROW1 1
#define ROW2 2
#define ROW3 3

uint8_t rows[4] = {
  ROW0,
  ROW1,
  ROW2,
  ROW3
};

//multiplexing button columns
#define BUTTON_COLUMN0  4
#define BUTTON_COLUMN1  6
#define BUTTON_COLUMN2  8
#define BUTTON_COLUMN3  10
#define BUTTON_COLUMN4  12
#define BUTTON_COLUMN5  14
#define BUTTON_COLUMN6  16
#define BUTTON_COLUMN7  18
#define BUTTON_COLUMN8  20
#define BUTTON_COLUMN9  22
#define BUTTON_COLUMN10  27
#define BUTTON_COLUMN11  28

uint8_t button_columns[12] = {
  BUTTON_COLUMN0,
  BUTTON_COLUMN1,
  BUTTON_COLUMN2,
  BUTTON_COLUMN3,
  BUTTON_COLUMN4,
  BUTTON_COLUMN5,
  BUTTON_COLUMN6,
  BUTTON_COLUMN7,
  BUTTON_COLUMN8,
  BUTTON_COLUMN9,
  BUTTON_COLUMN10,
  BUTTON_COLUMN11
};

//multiplexing led columns
#define LED_COLUMN0 5
#define LED_COLUMN1 7
#define LED_COLUMN2 9
#define LED_COLUMN3 11
#define LED_COLUMN4 13
#define LED_COLUMN5 15
#define LED_COLUMN6 17
#define LED_COLUMN7 19
#define LED_COLUMN8 21
#define LED_COLUMN9 26

uint8_t led_columns[10] = {
  LED_COLUMN0,
  LED_COLUMN1,
  LED_COLUMN2,
  LED_COLUMN3,
  LED_COLUMN4,
  LED_COLUMN5,
  LED_COLUMN6,
  LED_COLUMN7,
  LED_COLUMN8,
  LED_COLUMN9
};
