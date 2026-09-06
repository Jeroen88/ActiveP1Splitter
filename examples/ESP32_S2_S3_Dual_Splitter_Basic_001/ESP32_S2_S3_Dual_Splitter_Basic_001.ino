#include <Arduino.h>
#include "esp32-hal-matrix.h"

// Define the pins for the P1 splitter hardware. ESP32-S2 and ESP32-S3 differ a little bit on the positioning of the GPIO's on the pin headers
#if defined(ARDUINO_LOLIN_S2_MINI)
const int P1_IN_RX = 17;
const int P1_IN_RTS = 21;

const int P1_OUT_1_TX = 7;
const int P1_OUT_1_CTS = 4;

const int P1_OUT_2_TX = 18;
const int P1_OUT_2_CTS = 16;

#elif defined(ARDUINO_LOLIN_S3_MINI)
const int P1_IN_RX = 17;
const int P1_IN_RTS = 21;

const int P1_OUT_1_TX = 12;
const int P1_OUT_1_CTS = 5;

const int P1_OUT_2_TX = 18;
const int P1_OUT_2_CTS = 16;

#else
#error "Unsupported board"
#endif


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.println("\nStarted\n");

  // HardwareSerial Serial1 to read from
  // Since the DSMR protocol uses an inverted serial signal, the 5th argument is 'true'
  Serial1.begin(115200, SERIAL_8N1, P1_IN_RX, -1, true);

  // The P1_IN_RTS pin is connected to a transistor that pulls the actual pin of the meter to 5v. 
  // Because the transistor inverts the signal, pulling LOW actually pulls the RJ11 RTS pin to +5v, so HIGH
  pinMode(P1_IN_RTS, OUTPUT);
  digitalWrite(P1_IN_RTS, LOW);

  // HardwareSerial Serial0 to write to
  // Although the DSMR protocol of course also needs an inverted serial signal on the output, here the 5th argument is omitted (so 'false')
  // because the optocoupler hardware inverts it
  Serial0.begin(115200, SERIAL_8N1, -1, P1_OUT_1_TX);

  // Duplicate UART0 TX onto the second GPIO
  pinMatrixOutAttach(P1_OUT_2_TX, U0TXD_OUT_IDX, false, false);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()) {
    digitalWrite(LED_BUILTIN, HIGH);

    while(Serial1.available()) {
      // Read from P1 input port
      int c = Serial1.read();
      // Write to both P1 output ports at once (making use of the TX pin duplication at setup())
      Serial0.write(c);
      // Log to the serial monitor
      Serial.write(c);
    }
    // Send any bytes in the output buffer
    Serial0.flush();

    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(10);
}
