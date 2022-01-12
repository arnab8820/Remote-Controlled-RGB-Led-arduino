#include <EEPROM.h>

void saveColor(int pos, color newColor){
  uint16_t address = pos * sizeof(newColor);
  EEPROM.put(address, newColor);
}

struct color loadColor(int pos){
  color arr;
  uint16_t address = pos * sizeof(arr);
  EEPROM.get(address, arr);
  arr.red = abs(arr.red);
  arr.green = abs(arr.green);
  arr.blue = abs(arr.blue);
  return arr;
}
