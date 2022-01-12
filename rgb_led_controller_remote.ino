#include <IRremote.h>

#define RPIN 3           //Red channel pin number
#define GPIN 5           //Green channel pin number
#define BPIN 6           //Blue channel pin number
#define LEDPIN 13         //Remote feedback led pin number

struct color {
  int red;
  int green;
  int blue;
};

struct remoteCommand {
  bool repeat;
  uint8_t command;
};

struct color prevColor, nextColor, transitionColor, tempColor;
long colGenTime;    
bool paused=false, saveMode=false, enabled=true;
int duration = 10;      //duration between color change

color generateColor(){
  //define a new color struct
  struct color newColor;

  //get random values for R G B
  randomSeed(random(analogRead(A0)));
  int rVal = random(256);
  randomSeed(random(analogRead(A0)));
  int gVal = random(256);
  randomSeed(random(analogRead(A0)));
  int bVal = random(256);

  //Lower intensity color prevention code
  if(rVal<100 && gVal<100 && bVal<100){
    switch(random(100)%3){
      case 0:
        rVal = random(150, 256);
        gVal = random(100);
        bVal = random(100);
        break;
      case 1:
        rVal = random(100);
        gVal = random(150, 256);
        bVal = random(100);
        break;
      case 2:
        rVal = random(100);
        gVal = random(100);
        bVal = random(150, 256);
        break;
    }
  }
  
  newColor.red = rVal;
  newColor.green = gVal;
  newColor.blue = bVal;
  return newColor;
}

void colorTransition(){
  //Transition from one color to another
  printDebugData();
  digitalWrite(LEDPIN, HIGH);
  for(int i=0; i<255; i++){
    if(transitionColor.red!=nextColor.red){
      if(transitionColor.red > nextColor.red){
        transitionColor.red--;
      } else {
        transitionColor.red++;
      }
    }
    if(transitionColor.green!=nextColor.green){
      if(transitionColor.green > nextColor.green){
        transitionColor.green--;
      } else {
        transitionColor.green++;
      }
    }
    if(transitionColor.blue!=nextColor.blue){
      if(transitionColor.blue > nextColor.blue){
        transitionColor.blue--;
      } else {
        transitionColor.blue++;
      }
    }
    analogWrite(RPIN, transitionColor.red);
    analogWrite(GPIN, transitionColor.green);
    analogWrite(BPIN, transitionColor.blue);
    delay(10);
  }
  digitalWrite(LEDPIN, LOW);
}

void handleRemoteCode(struct remoteCommand readCode){
  color savedColor;
  if(!readCode.repeat){
    switch(readCode.command){
      case 0x12:              //power
        if(enabled){
          tempColor = prevColor;
          prevColor = nextColor;
          nextColor.red = 0;
          nextColor.green = 0;
          nextColor.blue = 0;
          enabled = false;
        } else {
          nextColor = prevColor;
          prevColor = tempColor;     
          enabled = true;   
        }
        colorTransition();
        colGenTime = millis();
        break;
      case 0x1:               //play-pause
        paused = !paused;
        break;
      case 0x2:               //prev
        if(enabled){
          nextColor = prevColor;
          colorTransition();
          colGenTime = millis();
        }
        break;
      case 0x3:               //next
        if(enabled){
          prevColor = nextColor;
          nextColor = generateColor();
          colorTransition();
          colGenTime = millis();
        }
        break;
      case 0x5:               //Vol-
        duration -= (duration-5)<5?0:5;
        Serial.print("Duration: ");
        Serial.println(duration);
        break;
      case 0x6:               //Vol+
        duration += 5;
        Serial.print("Duration: ");
        Serial.println(duration);
        break;
      case 0x9:               //U/SD
        saveMode=true;
        break;
      case 0x7:               //0
        if(saveMode){
          savedColor = nextColor;
          saveColor(0, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(0);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0xA:               //1
        if(saveMode){
          savedColor = nextColor;
          saveColor(1, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(1);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0x1B:               //2
        if(saveMode){
          savedColor = nextColor;
          saveColor(2, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(2);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0x1F:               //3
        if(saveMode){
          savedColor = nextColor;
          saveColor(3, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(3);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0xC:               //4
        if(saveMode){
          savedColor = nextColor;
          saveColor(4, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(4);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0xD:               //5
        if(saveMode){
          savedColor = nextColor;
          saveColor(5, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(5);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0xE:               //6
        if(saveMode){
          savedColor = nextColor;
          saveColor(6, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(6);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0x0:               //7
        if(saveMode){
          savedColor = nextColor;
          saveColor(7, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(7);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0xF:               //8
        if(saveMode){
          savedColor = nextColor;
          saveColor(8, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(8);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
      case 0x19:               //9
        if(saveMode){
          savedColor = nextColor;
          saveColor(9, savedColor);
          saveMode = false;
        } else {
          savedColor = loadColor(9);
          prevColor = nextColor;
          nextColor = savedColor;
          colorTransition();
          paused = true;
        }
        colGenTime = millis();
        break;
    }
  }
}

void printDebugData(){
  String data = "R: " + String(nextColor.red, DEC);
  data += " G: " + String(nextColor.green, DEC);
  data += " B: " + String(nextColor.blue, DEC);
  Serial.println(data);
}

void setup() {
  
  //test code remove in production
  //--------- CUT HERE ---------------
  pinMode(RPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  //--------- CUT HERE ---------------

  pinMode(LEDPIN, HIGH);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  initRemote();
  transitionColor.red = 255;
  transitionColor.green = 255;
  transitionColor.blue = 255;
  colGenTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!paused && enabled && (millis()-colGenTime >= (duration * 1000))){
    prevColor = nextColor;
    nextColor = generateColor();
    colorTransition();
    colGenTime = millis();
  }
  struct remoteCommand readCode;
  readCode = readRemote(LEDPIN);
  if(readCode.command!= 0xFF){
    Serial.println(readCode.command, HEX);
    handleRemoteCode(readCode);
  }
}
