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
const int joyPin[] = {0, 1};

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

// for my wiring VRX = pin 0 and VRY = pin 1
// for some reason idle appears to be 52???
void processInput(Shape *shape, Layer *background, int analogToggle) {
  int buttonState = digitalRead(buttonPin);
  int analogVal = analogRead(joyPin[0]); //analogToggle is for either X or Y, but I only care about X for now
  int treatedVal = (analogVal * 9 / 1024) + 48; // per docs apply this formula (data * 9 / 1024) + 48;

  if (buttonState == HIGH) {
    Logger::log("button pushed!");
    shape->tryRotate(background);
  }

  int analogDelta = treatedVal - 52;
  if (analogDelta < 0) {
    shape->tryLeftRight(background, 1);
  }

  else if (analogDelta > 0) {
    shape->tryLeftRight(background, -1);
  }

  //int vars[] = {analogDelta};
  //Logger::log("analog = ?", vars, 1);
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
  int analogToggle = 0;

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
      analogToggle = !analogToggle;
      processInput(&shape, background, analogToggle);
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

  // may not need to delete if I re-use them for some idle screen animation in outer loop??
  delete displ;
  delete background;
}
