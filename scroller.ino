#include "point.h"
#include "layer.h"
#include "shape.h"
#include "logger.h"
#include <SPI.h>

#define REG_DECODE (0x09)
#define REG_DIGIT(pos) ((pos) + 1)
#define REG_INTENSITY (0x0A)
#define REG_SCANLIMIT (0x0B)
#define REG_SHUTDOWN (0x0C)
#define REG_DISPLAYTEST (0x0F)

#define ON (0x1)
#define OFF (0x0)


Point ShapeTemplate[2][4] = {
  {Point(0,0), Point(-1,0), Point(1,0), Point(-1,-1)}, // L Shape, Left
  {Point(0,0), Point(-1,0), Point(1,0), Point(1, -1)}, // L Shape, Right
};

void set_register(byte address, byte value)
{
  digitalWrite(SS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS, HIGH);
}


void init_doggydoo()
{
  set_register(REG_DISPLAYTEST, OFF);
  set_register(REG_INTENSITY, 0x8);
  set_register(REG_SHUTDOWN, OFF);
  set_register(REG_SCANLIMIT, 7);
  set_register(REG_DECODE, B00000000);
}



void setup (void) {
  digitalWrite(SS, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

  Serial.begin(9600);
  Serial.println("Test from Arduino world!");

  init_doggydoo();
}


void render(Layer *layer) {
  set_register(REG_SHUTDOWN, OFF);

  for (int i = 0; i < 8; i++)
    set_register(REG_DIGIT(i), layer->digVal[i]);

  set_register(REG_SHUTDOWN, ON);
}



void loop (void) {
  //init background layer with all zeros
  Layer *background = new Layer();
  Layer *foreground;

  Shape shape = Shape(ShapeTemplate[0], 0, 0, 0);

  if (shape.trySpawn(background)) {
    foreground = shape.layer;
    render(foreground);
  }

  else {
    Logger::log("Game Over!");
  }


  delay(1000);

}
