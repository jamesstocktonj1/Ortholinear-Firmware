#include "Adafruit_TinyUSB.h"
#include "pins.h"
#include "keys.h"


// keyboard setup constants
#define PRODUCT_DESCRIPTOR "Ortholinear Keyboard"
#define MANUFACTURER_DESCRIPTOR "JStockton"
//#define KEYBOARD_PID 0x0000
//#define KEYBOARD_VID 0X0000


// usb hid setup
void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD);


// keyboard multiplexing functions
void init_pins(void);
uint16_t read_columns(uint8_t rowIndex);
uint8_t read_keys(void);
void print_keys(void);

// keyboard led functions
void set_led_states(void);
void write_leds(void);

// key status arrays
uint16_t key_status[4] = {0, };
uint16_t key_previous[4] = {0, };
uint16_t key_diff[4] = {0, };

// led status arrays
bool writeLeds = false;
uint16_t led_state[4] = {0, };


// keyboard special key functions
void copy_func(uint8_t state);
void paste_func(uint8_t state);


// core 0 functions
void setup() {

  // set usb descriptors
  // product descriptor
  #ifdef PRODUCT_DESCRIPTOR
  TinyUSBDevice.setProductDescriptor(PRODUCT_DESCRIPTOR);
  #endif

  // manufacturer descriptor
  #ifdef MANUFACTURER_DESCRIPTOR
  TinyUSBDevice.setManufacturerDescriptor("JStockton");
  #endif

  // set usb id values (vid, pid)
  #ifdef KEYBOARD_VID && KEYBOARD_PID
  TinyUSBDevice.setID(KEYBOARD_VID, KEYBOARD_PID);
  #endif

  // setup usb and pins
  usb_hid.begin();
  init_pins();

  // wait for usb connection
  while(!TinyUSBDevice.mounted()) delay(1);
}

void loop() {

  /*
  if(read_keys()) {
    print_keys();
  }
  
  delay(20);*/
  USR_KEY_FUNC_0(1);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  usb_hid.keyboardRelease(0x00);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);

  delay(2000);


  USR_KEY_FUNC_1(1);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  usb_hid.keyboardRelease(0x00);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);

  delay(2000);
}

// core 1 functions
void setup1() {}

void loop1() {

  if(writeLeds) {
    digitalWrite(LED_BUILTIN, HIGH);
    write_leds();
    digitalWrite(LED_BUILTIN, LOW);
  }
  /*
  copy_func();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  usb_hid.keyboardRelease(0x00);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);

  delay(2000);


  paste_func();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  usb_hid.keyboardRelease(0x00);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);

  delay(2000);*/
}


void init_pins() {

  pinMode(LED_BUILTIN, OUTPUT);

  // itterate through rows
  for(int i=0; i<4; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }

  // itterate through button columns
  for(int j=0; j<12; j++) {
    pinMode(button_columns[j], INPUT_PULLUP);
  }

  // itterate through led columns
  for(int k=0; k<10; k++) {
    pinMode(led_columns[k], OUTPUT);
    pinMode(led_columns[k], LOW);
  }
}

uint16_t read_column(uint8_t rowIndex) {

  uint16_t columnStatus = 0;

  // set row values (all 1 except rowIndex)
  for(int i=0; i<4; i++) {
    digitalWrite(rows[i], i!=rowIndex);
  }

  // itterate through columns
  for(int j=0; j<12; j++) {

    // read value and add to status
    if(digitalRead(button_columns[j]) == 0) {
      columnStatus += (1 << j);
    }
    //columnStatus += (digitalRead(button_columns[j]) * (1 << j));
  }

  // reset row values
  for(int i=0; i<4; i++) {
    digitalWrite(rows[i], HIGH);
  }

  return columnStatus;
}

uint8_t read_keys() {

  uint16_t temp;
  uint8_t change = 0;

  // itterate through rows
  for(int i=0; i<4; i++) {
    
    // set previous key value
    key_previous[i] = key_status[i];

    // set new key values
    temp = read_column(i);
    key_status[i] = temp;
    key_diff[i] = temp ^ key_previous[i];

    // set change flag
    if(temp) {
      change = 1;
    }

    delay(2);
  }

  // update led array
  set_led_states();

  return change;
}

void print_keys() {

  // itterate through rows
  for(int i=0; i<4; i++) {

    // itterate through columns
    for(int j=0; j<12; j++) {

      if(key_status[i] & key_diff[i] & (1 << j)) {

        // log button presses
        Serial.print("Button Pressed: row ");
        Serial.print(i);
        Serial.print(" columns ");
        Serial.print(j);
        Serial.print("\n");
      }

      // log button release
      if(!(key_status[i] & key_diff[i] & (1 << j))) {

        // log button presses
        Serial.print("Button Released: row ");
        Serial.print(i);
        Serial.print(" columns ");
        Serial.print(j);
        Serial.print("\n");
      }
    }
  }
}


void write_leds() {

  // itterate through rows
  for(int i=0; i<4; i++) {

    // set row values (all 1 except rowIndex)
    for(int k=0; k<4; k++) {
      digitalWrite(rows[k], k!=i);
    }

    // itterate through columns
    for(int j=0; j<10; j++) {

      digitalWrite(led_columns[i], led_state[i] & (1 << j));
    }

    delay(LED_WAIT_TIME);
  }

  // reset pin states
  for(int i=0; i<4; i++) {
    digitalWrite(rows[i], HIGH);
  }

  for(int j=0; j<10; j++) {
    digitalWrite(led_columns[j], LOW);
  }
}


void set_led_states() {

  // itterate through rows
  for(int i=0; i<4; i++) {

    led_state[i] = key_status[i];
  }
}



void copy_func(uint8_t state) {

  if(state) {
    // control modifier (bit 4) + c
    uint8_t modifier = (1 << 4);
    uint8_t keys[1] = {HID_KEY_C};

    // send report: id 0
    usb_hid.keyboardReport(0x00, modifier, keys);
  }
}

void paste_func(uint8_t state) {

  if(state) {
    // control modifier (bit 4) + c
    uint8_t modifier = (1 << 4);
    uint8_t keys[1] = {HID_KEY_V};

    // send report: id 0
    usb_hid.keyboardReport(0x00, modifier, keys);
  }
}
