#ifndef LAYER_H_
#define LAYER_H_

class Layer {
public:
  Layer();
  Layer(Layer *source);
  ~Layer();

  bool collisionOrBoundary(Layer *layer);
  void merge(Layer *layer);
  void fill(short n);
  void dump();

  short *digVal;
};

#endif
