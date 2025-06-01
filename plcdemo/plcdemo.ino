#include "PLC.h"

PLC plc;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600); // open the serial port at 9600 bps:


plc.init();
delay(1500);//Delay to let system boot

}

void loop() {
  // put your main code here, to run repeatedly:

    plc.load(0);
    plc.out(200);


  // plc.loadnot(0);
  // plc.andnotload(200);
  // plc.timer(100,100);
  // plc.out(200);
  
  // plc.loadnot(0);
  // plc.andnotload(201);
  // plc.timer(101,50);
  // plc.out(201);

  // plc.loadnot(0);
  // plc.andnotload(202);
  // plc.timer(102,150);
  // plc.out(202);
  
  // plc.loadnot(0);
  // plc.andnotload(203);
  // plc.timer(103,250);
  // plc.out(203);

  // plc.load(0);
  // plc.load(201);
  // plc.counter(900,10);
  // plc.load(900);
  // plc.func(147,25);

  /************************   and circuit 2   ***********************/

  // plc.load(0);
  // plc.orload(200);
  // andload(1);
  // andnotload(2);
  // plc.out(200);
  
  /************************   Multiple output circuit 1   ***********************/

  // load(0);
  // out(200);
  // andnotload(1);
  // out(201);
  // andload(2);
  // out(202);



  /************************   10 saniye timer    ***********************/
  // plc.loadnot(200);
  // plc.timer(100,100);
  // plc.out(200);
  // load(100);
  // func(147,25);


  /************************   buton ile 5 e kadar counter    ***********************/
  // plc.load(0);
  // load(1);
  // plc.load(200);
  // plc.counter(900,5);
  // plc.out(201);
  // plc.load(900);
  // plc.func(147,25);

}

