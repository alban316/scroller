
/////////////////////////////////////
// The arduino Serial version
/////////////////////////////////////

#include "logger.h"
#include <HardwareSerial.h>

void Logger::log(const char *msg, int *vars, int len) {
  char c;
  int i = 0;

  for (const char *p = msg; c = *p; p++) {
    if (c == '?') {
      Serial.print(vars[i]);
      i++;
    }

    else
      Serial.print(c);
  }

  Serial.print("\n\r");
}


void Logger::log(const char *msg) {
  char c;

  for (const char *p = msg; c = *p; p++) {
      Serial.print(c);
  }

  Serial.print("\n\r");
}
