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


// globals & consts
Point ShapeTemplate[2][4] = {
  {Point(0,0), Point(-1,0), Point(1,0), Point(-1,-1)}, // L Shape, Left
  {Point(0,0), Point(-1,0), Point(1,0), Point(1, -1)}, // L Shape, Right
};

const int buttonPin = 2;


void set_register(byte address, byte value)
{
  digitalWrite(SS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS, HIGH);
}


void init_max()
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

  // init button
  pinMode(buttonPin, INPUT);

  init_max();
}


void render(Layer *layer) {
  set_register(REG_SHUTDOWN, OFF);

  for (int i = 0; i < 8; i++)
    set_register(REG_DIGIT(i), layer->digVal[i]);

  set_register(REG_SHUTDOWN, ON);
}


void processInput(Shape *shape, Layer *background) {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    Logger::log("button pushed!");
    shape->tryRotate(background);
  }
}


void loop (void) {
  Layer *background = new Layer();
  Layer *displ = new Layer();

  Shape shape = Shape(ShapeTemplate[0], 0, 0, 0);

  int elapsed = millis();
  int lastInput = 0;
  int lastStatus = 0;
  int lastDrop = 0;
  int quit = elapsed;

  bool playing = shape.trySpawn(background, 0, -2);

  while (playing) {
    elapsed = millis();

    displ->fill(0);
    displ->merge(background);
    displ->merge(shape.layer);
    render(displ);

    // process input ever 100 ms
    if (elapsed - lastInput > 100) {
      lastInput = elapsed;
      processInput(&shape, background);
    }

    // process drop!!
    if (elapsed - lastDrop > 1000) {
      lastDrop = elapsed;
      
      if (!shape.tryDrop(background, 1)) {
        background->merge(shape.layer);
        shape = Shape(ShapeTemplate[0], 0, 0, 0);
        playing = shape.trySpawn(background, 0, -2);
      }      
    }

    // for testing, output idle every 1 sec
    if (elapsed - lastStatus > 1000) {
      lastStatus = elapsed;
      Logger::log("idle");
    }

    if (elapsed - quit > 20000) {
      playing = false;
    }

  }

  Logger::log("Game Over!");
}
