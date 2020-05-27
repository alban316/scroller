#ifndef LAYER_H_
#define LAYER_H_

class Layer {
public:
  Layer();
  Layer(Layer *source);
  ~Layer();

  bool collisionOrBoundary(Layer *layer);
  void merge(Layer *layer);
  void fill(int n);
  void shiftLt();
  void shiftRt();
  //void shiftDn();
  void dump();

  int *digVal;
};

#endif
