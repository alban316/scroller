#ifndef LAYER_H_
#define LAYER_H_

class Layer {
public:
  Layer();
  virtual ~Layer() {};

  void merge(Layer *layer);
  void shiftLt();
  void shiftRt();
  void shiftDn();
  void dump();

  int *digVal;
};

#endif
