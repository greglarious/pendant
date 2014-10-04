class Position { 
public: 
  char hOffset;
  char vOffset;
  boolean flip;

  Position() {
    hOffset = 0;
    vOffset = 0;
    flip = false;
  }  
  Position(char h, char v, boolean f) {
    hOffset = h;
    vOffset = v;
    flip = f;
  }
  
  uint8_t slideRow(const uint8_t rowData) {
    uint8_t rval = rowData;
    
    if (flip) {
      int temp = bitRead(rval, 0);
      bitWrite(rval, 0, bitRead(rval, 7));
      bitWrite(rval, 7, temp);
      
      temp = bitRead(rval, 1);
      bitWrite(rval, 1, bitRead(rval, 6));
      bitWrite(rval, 6, temp);
      
      temp = bitRead(rval, 2);
      bitWrite(rval, 2, bitRead(rval, 5));
      bitWrite(rval, 5, temp);
      
      temp = bitRead(rval, 3);
      bitWrite(rval, 3, bitRead(rval, 4));
      bitWrite(rval, 4, temp);
    }
    
    if (hOffset >= 0) {
      return rval >> hOffset;
    } else if (hOffset < 0) {
      return rval << abs(hOffset);
    }
  }
};
