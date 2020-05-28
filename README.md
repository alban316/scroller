## Tetris-style clone for Arduino

This was an exercise in learning SPI and refreshing my C++ coding skills (which still have a long way to go). It's written for Arduino Uno and, as such, has hardware dependencies. In this case:

* LED 8x8 Matrix driven by MAX7219
* An analog joystick
* A digital pushbutton
* Arduino Uno

##### Some known issues
* Rand() needs to be seeded from millis(). As is, the same pieces are generated in the same sequence every time.
* After about 5 or so pieces the game seems to puke. Possibly a memory issue? I tried to conserve RAM by using shorts instead of ints and **delete**(ing) everything that was instantiated with **new** to avoid memory leaks.
* It's possible to scroll off the screen to the right despite some effort in my code to avoid this.

The above issues will probably never be resolved (by me) since my overall goals were achieved. Making a viable game was never one of them. There's enough here that works to prove the concept.

##### Remarks
* The Logger class was created to abstract debugging output so that I could have separate implementations for the Arduino (using HardwareSerial) and desktop (using iostream), but the rest of the code would otherwise be the same. 

##### Links
* [Project on Hackaday.IO](https://hackaday.io/project/171994-arduino-tetris-clone-with-max7219-8x8-matrix)
