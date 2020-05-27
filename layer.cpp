#include "layer.h"
#include "logger.h"

Layer::Layer() {
  digVal = new int[8];

  for (int i = 0; i < 8; i++) {
    digVal[i] = 0;
  }
}


void Layer::dump() {
  for (int i = 0; i < 8; i++) {

    int vars[] = {i, digVal[i]};
    Logger::log("row ? = ?", vars, 2);
  }
}
