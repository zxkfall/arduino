/*
 * SendRawDemo.cpp - demonstrates sending IR codes with sendRaw
 *
 * This example shows how to send a RAW signal using the IRremote library.
 * The example signal is actually a 32 bit NEC signal.
 * Remote Control button: LGTV Power On/Off.
 * Hex Value: 0x20DF10EF, 32 bits
 *
 * If it is a supported protocol, it is more efficient to use the protocol send function
 * (here sendNEC) to send the signal.
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2020-2022 Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */
#include <Arduino.h>

// #if !defined(ARDUINO_ESP32C3_DEV)  // This is due to a bug in RISC-V compiler, which requires unused function sections :-(.
// #define DISABLE_CODE_FOR_RECEIVER  // Disables static receiver code like receive timer ISR handler and static IRReceiver and irparams data. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not required.
// #endif

//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition
//#define NO_LED_FEEDBACK_CODE      // Saves 566 bytes program memory
//#define USE_OPEN_DRAIN_OUTPUT_FOR_SEND_PIN // Use or simulate open drain output mode at send pin. Attention, active state of open drain is LOW, so connect the send LED between positive supply and send pin!

#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>
#define RAW_BUFFER_LENGTH  750
void setup() {
  // pinMode(9, OUTPUT);

  Serial.begin(115200);
  IrSender.begin();  // Start with IR_SEND_PIN -which is defined in PinDefinitionsAndMore.h- as send pin and enable feedback LED at default feedback LED pin
}


void loop() {

  Serial.println(F("Send NEC 16 bit address=0xFB04 and command 0x08 with exact timing (16 bit array format)"));
  Serial.flush();

  const uint16_t rawData[] = {9030,4470, 680,520, 680,520, 680,520, 680,1620, 630,570, 680,520, 630,570, 630,570, 630,1670, 630,570, 680,520, 680,1620, 630,570, 630,570, 630,570, 680,520, 630,570, 630,570, 630,570, 680,520, 680,520, 680,1620, 630,570, 680,520, 680,520, 680,520, 680,520, 680,520, 680,1620, 680,520, 680,1620, 680,520, 680,520, 680,1620, 680,520, 680,19970, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,1670, 630,1670, 630};  // Protocol=UNKNOWN Hash=0x626521E5 70 bits (incl. gap and start) received

uint16_t rawData4[279] = {9030,4470, 680,520, 680,520, 630,570, 680,1620, 630,570, 680,520, 680,520, 680,520, 680,1620, 630,570, 630,570, 680,1620, 630,570, 680,520, 630,570, 630,570, 680,520, 680,520, 680,520, 680,520, 630,570, 630,1670, 630,570, 630,570, 680,520, 630,570, 630,570, 630,570, 680,1620, 680,520, 630,1670, 630,570, 630,570, 630,1670, 630,570, 630,20020, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,1670, 630,1670, 630,40020, 8980,4520, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,1670, 630,1670, 630,570, 630,570, 630,1670, 630,570, 630,20020, 630,570, 630,570, 630,570, 630,570, 630,570, 580,620, 630,570, 630,570, 630,570, 630,570, 580,620, 630,570, 580,620, 580,620, 580,620, 580,620, 580,620, 580,620, 580,620, 580,620, 630,570, 630,570, 630,570, 580,620, 580,620, 580,620, 580,620, 580,620, 580,1720, 580,1720, 580,620, 580,1720, 580};  // Protocol=UNKNOWN Hash=0xC944E467 140 bits (incl. gap and start) received

uint16_t rawData1[140] = {9030,4470, 680,520, 680,520, 630,570, 680,1620, 630,570, 680,520, 680,520, 680,520, 680,1620,
 630,570, 630,570, 680,1620, 630,570, 680,520, 630,570, 630,570, 680,520, 680,520, 680,520,
  680,520, 630,570, 630,1670, 630,570, 630,570, 680,520, 630,570, 630,570, 630,570, 680,1620,
   680,520, 630,1670, 630,570, 630,570, 630,1670, 630,570, 630,20020, 630,570, 630,570, 630,570, 
   630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 
   630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 
   630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 630,1670, 630,1670, 630,40020} ;
uint16_t rawData2[140] ={
   8980,4520, 630,570, 630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,1670, 
   630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 
   630,570, 630,570, 630,1670, 630,570, 630,570, 630,570, 630,570, 630,570, 630,570, 630,1670, 
   630,1670, 630,1670, 630,570, 630,570, 630,1670, 630,570, 630,20020, 630,570, 630,570, 630,570, 
   630,570, 630,570, 580,620, 630,570, 630,570, 630,570, 630,570, 580,620, 630,570, 580,620, 
   580,620, 580,620, 580,620, 580,620, 580,620, 580,620, 580,620, 630,570, 630,570, 630,570, 
   580,620, 580,620, 580,620, 580,620, 580,620, 580,1720, 580,1720, 580,620, 580,1720, 580,5000};  // Protocol=UNKNOWN Hash=0xC944E467 140 bits (incl. gap and start) received


  // IrSender.sendRaw(rawData1, 140, NEC_KHZ);  // Note the approach used to automatically calculate the size of the array.
  // IrSender.sendRaw(rawData2, 140, NEC_KHZ);  // Note the approach used to automatically calculate the size of the array.
  IrSender.sendRaw(rawData4, 279, 38);
  delay(5000);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal

}
