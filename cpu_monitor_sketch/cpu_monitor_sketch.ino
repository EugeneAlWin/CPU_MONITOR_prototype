#include <GyverOLED.h>
#include "utils.h"
#include "interface.h"

constexpr byte BUTTON_PIN_DIGITAL = 2;
constexpr byte INTERRUPT_PIN_D2 = 0;

volatile SCREENS currentScreen;
volatile STATES currentState;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN_DIGITAL, INPUT_PULLUP);
  attachInterrupt(INTERRUPT_PIN_D2, requestScreenChange, RISING);
  currentState = WAIT_FOR_CONNECTION;
  currentScreen = CPU_GPU;

  initializeDisplay(&oled);
}

void loop()
{
  if (currentState == WAIT_FOR_CONNECTION)
    return waitForConnection(&currentState);

  else if (currentState == SHOW_SCREEN)
    return requestAnimationFrame(&oled);

  else if (currentState == CHANGE_SCREEN)
    return requestScreenChange();
}

// int ByteReceived = 0; // INT for received serial data
// void setup() {
//   Serial.begin(9600); // Serial communication begin to read data
// }
// void loop() {
//   // check for the serial data at serial port
//   if (Serial.available() > 0) {
//     // read byte of received data:
//     ByteReceived = Serial.read();
//     // prints the received data on serial monitor
//     Serial.write("f");
//   }
// }