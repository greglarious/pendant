class Position { 
public: 
  char hOffset;
  char vOffset;
  boolean flip;
  
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

class Translation {
public:  
  char hMomentum;
  char vMomentum;
  boolean flip;
  char framesShown;
  char framesPerMove;
  
  Translation(char h, char v, boolean f, char fpm) {
    framesShown = 0;
    
    hMomentum = h ;
    vMomentum = v; 
    flip = f;
    framesPerMove = fpm;
  }
  
  Position* initialize() {
    Position* pos = new Position(0,0, flip);      
    
    // if moving right, start all the way left
    if (hMomentum > 0) pos->hOffset = -7;
    
    // if moving left, start all the way right
    if (hMomentum < 0) pos->hOffset = 7;
    
    // if moving right, start all the way left
    if (vMomentum > 0) pos->vOffset = -7;
    
    // if moving left, start all the way right
    if (vMomentum < 0) pos->vOffset = 7;

    return pos;
  }
  
  void apply(Position* pos) {
    framesShown++;
    
    if (framesShown >= framesPerMove) {
      framesShown = 0;
      //
      // do horizontal moves
      pos->hOffset += hMomentum;
      if (pos->hOffset > 8) {
        pos->hOffset = -7;
      }
      if (pos->hOffset < -8) {
        pos->hOffset = 7;
      }
  
      //
      // do vertical moves
      pos->vOffset+= vMomentum;
      if (pos->vOffset > 8) {
        pos->vOffset = -7;
      }
      if (pos->vOffset < -8) {
        pos->vOffset = 7;
      }
    }
  }
};
