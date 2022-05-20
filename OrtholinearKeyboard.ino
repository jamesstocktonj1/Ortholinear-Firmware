#include "Adafruit_TinyUSB.h"

void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);
uint8_t read_buttons(void);

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);


//uint8_t keys[6] = {HID_KEY_A, 0, 0, 0, 0, 0};
//uint8_t keys[6] = {HID_KEY_GUI_LEFT, 0, 0, 0, 0, 0};

uint8_t keys[2] = {HID_KEY_CAPS_LOCK, HID_KEY_2};

uint8_t pinState, npinState;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);

  pinState = read_buttons();

  USBDevice.setManufacturerDescriptor("James Stockton");
  //TinyUSBDevice.setManufacturerDescriptor("Hello");
  USBDevice.setProductDescriptor("Ortholinear Keyboard");
  
  usb_hid.setReportCallback(NULL, hid_report_callback);
  usb_hid.begin();

  while(!TinyUSBDevice.mounted()); 
}

void loop() {

  npinState = read_buttons();


  if(npinState ^ pinState) {
    uint8_t buf[6] = {0, };
    //uint8_t i = 0;

    uint8_t pinDif = npinState ^ pinState;

    Serial.print("Button Difference: ");
    Serial.print(npinState ^ pinState, BIN);
    Serial.print("\tButton State: ");
    Serial.print(npinState);
    Serial.print("\n");
    /*
    if((pinDif & (1 << 0)) && !(pinState & (1 << 0))) {
      buf[i++] = keys[0];
    }
    if((pinDif & (1 << 1)) && !(pinState & (1 << 1))) {
      buf[i++] = keys[1];
    }
    */
    
    if(TinyUSBDevice.suspended()) {
      TinyUSBDevice.remoteWakeup();
    }
    
    if((pinDif & ~pinState) & (1 << 0)) {
      //usb_hid.keyboardPress(0, '1');
      //buf[i++] = keys[0];
      buf[0] = keys[0];
      usb_hid.keyboardReport(0, 0, buf);
    }
    if((pinDif & ~pinState) & (1 << 1)) {
      usb_hid.keyboardPress(0, '2');
      //buf[i++] = keys[1];
    }

    if((pinDif & pinState) & 0b11) {
      usb_hid.keyboardRelease(0);
    }
    
    //usb_hid.keyboardReport(0, 0, buf);
    //delay(10);
    //usb_hid.keyboardRelease(0);

    pinState = npinState;
  }
    
  delay(20);
}

uint8_t read_buttons() {
  uint8_t buttonState = 0;

  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);

  if(digitalRead(0) == 0) {
    buttonState += 1;
  }


  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);

  if(digitalRead(0) == 0) {
    buttonState += 2;
  }


  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  
  return buttonState;
}

void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {

  (void) report_id;
  (void) bufsize;

  uint8_t temp = buffer[0];

  Serial.print("Report: ");
  Serial.print(report_id);
  Serial.print("\tSize: ");
  Serial.print(bufsize);
  Serial.print("\n");

  digitalWrite(LED_BUILTIN, temp & (1 << 1));
}
