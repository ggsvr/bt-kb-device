
#include <Adafruit_TinyUSB.h>

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD()
};

// USB HID object. For ESP32 these values cannot be changed after this declaration
// desc report, desc len, protocol, interval, use out endpoint
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);

void setup() {
  // put your setup code here, to run once:
  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(115200);
  
  usb_hid.begin();
  while( !TinyUSBDevice.mounted() ) delay(1);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buffer[7];
  if (Serial1.available()) {
    Serial1.readBytes(buffer, sizeof(buffer));
    uint8_t modifiers = buffer[0];

    while (!usb_hid.ready()) delay(1);
    usb_hid.keyboardReport(0, modifiers, buffer+1);
    Serial.print("modifiers: ");
    Serial.println(modifiers);
    Serial.print("keys: ");
    for (int i = 1; i < 7; ++i) {
      Serial.print(buffer[i]);
      Serial.print(", ");
    }
    Serial.println();
  }
}
