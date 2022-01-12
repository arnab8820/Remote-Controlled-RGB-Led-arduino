#include <IRremote.h>

const int RECV_PIN = 4;

void initRemote(){
  IrReceiver.begin(RECV_PIN);
}

struct remoteCommand readRemote(int ledPin){
  if (IrReceiver.decode()){
    if(IrReceiver.decodedIRData.protocol != UNKNOWN){
      digitalWrite(ledPin, HIGH);
      struct remoteCommand newCode;
//      Serial.println(IrReceiver.decodedIRData.command, HEX);
      if (IrReceiver.decodedIRData.flags && (IRDATA_FLAGS_IS_AUTO_REPEAT || IRDATA_FLAGS_IS_REPEAT)){
        newCode.repeat = true;
        newCode.command = IrReceiver.decodedIRData.command;
      } else {
        newCode.repeat = false;
        newCode.command = IrReceiver.decodedIRData.command;
      }
      delay(200);
      IrReceiver.resume();
      digitalWrite(ledPin, LOW);
      return newCode;
    }
    
  }
  struct remoteCommand newCode;
  newCode.repeat = false;
  newCode.command = 0xFF;
  IrReceiver.resume();
  return newCode;
}

void irTestFunc(){
  if (IrReceiver.decode()){
    if(IrReceiver.decodedIRData.protocol != UNKNOWN){
      IrReceiver.printIRResultShort(&Serial);
      delay(200);
    }
    IrReceiver.resume();
  }
}
