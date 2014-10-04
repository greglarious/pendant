class Translation {
public:  
  char hMomentum;
  char vMomentum;
  boolean flip;
  char framesShown;
  char framesPerMove;
  Position pos;
  
  Translation(char h, char v, boolean f, char fpm) {
    framesShown = 0;
    
    hMomentum = h ;
    vMomentum = v; 
    flip = f;
    framesPerMove = fpm;
  }
  
  Position* initialize() {
    pos.hOffset=0;
    pos.vOffset=0;      
    pos.flip = flip;
    
    // if moving right, start all the way left
    if (hMomentum > 0) pos.hOffset = -7;
    
    // if moving left, start all the way right
    if (hMomentum < 0) pos.hOffset = 7;
    
    // if moving right, start all the way left
    if (vMomentum > 0) pos.vOffset = -7;
    
    // if moving left, start all the way right
    if (vMomentum < 0) pos.vOffset = 7;

    return &pos;
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
