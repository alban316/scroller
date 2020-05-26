#ifndef LOGGER_H_
#define LOGGER_H_


class Logger {
public:
  static void log(const char *msg, int *vars, int len);
  static void log(const char *msg);
};



#endif
