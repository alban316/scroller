
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



/*
#include "logger.h"
#include "string.h"
#include <HardwareSerial.h>

void Logger::log(String msg, int *vars, int len) {
  int indexOf = msg.indexOf('?');
  if (indexOf > 0) {
    String sub0 = msg.substring(0, indexOf);
    String sub1 = msg.substring(indexOf +1, msg.length() - indexOf);
    int var0 = vars[0];

    int varRemain[len - 1];
    for (int i = 1; i <= len; i++) {
      varRemain[i - 1] = vars[i];
    }

    return sub0 + var0 + Logger::log(sub1, varRemain, len - 1);
  }

  else
    return msg;
}
*/
