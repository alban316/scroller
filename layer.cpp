#include "layer.h"
#include "logger.h"

Layer::Layer() {
  digVal = new int[8];

  for (int i = 0; i < 8; i++) {
    digVal[i] = 0;
  }
}

Layer::~Layer() {
  delete digVal;
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
    //int vars[] = {digVal[i], layer->digVal[i], digVal[i] & layer->digVal[i]};
    //Logger::log("this = ?, layer = ?, & = ?", vars, 3);
    
    if (((digVal[i] & layer->digVal[i]) != 0) | (digVal[i] > 255)) {
      return true;
    }
      
  }

  return false;
}

void Layer::merge(Layer *layer) {
  for (int i = 0; i < 8; i++) {
    digVal[i] = digVal[i] | layer->digVal[i];
  }
}

// fill an arbitrary value;
void Layer::fill(int n) {
  for (int i = 0; i < 8; i++) {
    digVal[i] = n;
  }
}
