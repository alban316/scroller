#ifndef LAYER_H_
#define LAYER_H_

class Layer {
public:
  Layer();
  Layer(Layer *source);
  virtual ~Layer() {};

  bool collisionOrBoundary(Layer *layer);
  void merge(Layer *layer);
  void fill();
  void shiftLt();
  void shiftRt();
  //void shiftDn();
  void dump();

  int *digVal;
};

#endif
