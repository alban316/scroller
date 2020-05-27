#include "layer.h"
#include "logger.h"

Layer::Layer() {
  digVal = new int[8];

  for (int i = 0; i < 8; i++) {
    digVal[i] = 0;
  }
}

// create a layer from a copy
Layer::Layer(Layer *source) {
  digVal = new int[8];

  for (int i = 0; i < 8; i++) {
    digVal[i] = source->digVal[i];
  }
}

void Layer::dump() {
  for (int i = 0; i < 8; i++) {

    int vars[] = {i, digVal[i]};
    Logger::log("row ? = ?", vars, 2);
  }
}

bool Layer::collisionOrBoundary(Layer *layer) {
  for (int i = 0; i < 8; i++) {
    if (((digVal[i] & layer->digVal[i]) != 0) | (digVal[i] > 255))
      return true;

    // still need vertical boundary e.g. i == 7 and digVal[i] > 0
  }

  return false;
}

// fill with 1's instead of 0's, for testing
void Layer::fill() {
  for (int i = 0; i < 8; i++) {
    digVal[i] = 255;
  }
}
