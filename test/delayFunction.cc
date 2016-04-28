int delay(uint run, const uint ls) {
  int delay=-9999;
  if (run==271056) {
    if (ls<58)  { delay=37; return delay; }
    if (ls<81)  { delay=12; return delay; }
    if (ls<110) { delay=-25; return delay;} // Get back to this point
    if (ls<223) { delay=49; return delay; }
    if (ls<263) { delay=37; return delay; }
    if (ls<306) { delay=25; return delay; }
  } 
  if (run==271084) { 
    delay=12; return delay; 
  } 
  if (run==271188) { 
    delay=49; return delay; 
  } 
  if (run==271191) {
    if (ls<16)  { delay=49; return delay; }
    if (ls<55)  { delay=63; return delay; }
    if (ls<110) { delay=74; return delay; }
    else 	{ delay=87; return delay; }
  } 
  if (run==271192) { 
    delay=87; return delay; 
  } 
  if (run==271193) {
    if (ls<44)  { delay=47; return delay; }
    if (ls<92)  { delay=45; return delay; }
    else        { delay=43; return delay; }
  } 
  if (run==271195) {
    if (ls<47)  { delay=43; return delay; }
    if (ls<95)  { delay=41; return delay; }
    if (ls<134) { delay=39; return delay; }
    if (ls<186) { delay=85; return delay; }
    else 	{ delay=83; return delay; }
  }
  if (run==271196) {
    if (ls<3)	{ delay=83; return delay; }
    if (ls<37)	{ delay=79; return delay; }
    if (ls<88)  { delay=77; return delay; }
    if (ls<127) { delay=70; return delay; }
    if (ls<168) { delay=68; return delay; }
    if (ls<204) { delay=66; return delay; }
    else 	{ delay=64; return delay; }
  }
  if (run==271197) {
    if (ls<5)	{ delay=64; return delay; } // this is not the same as in the log from Aurelejus
    else 	{ delay=60; return delay; }
  }
  if (run==271214) {
    if (ls<18)  { delay=60; return delay; } // Aurelejus doesn't have this
    if (ls<51)	{ delay=58; return delay; }
    else 	{ delay=56; return delay; }
  }
  if (run==271304) {
    if (ls<72) {
      delay=56; // this was not recorded!! should be the original setting or the one before this run
      return delay;
    }
    else {
      delay=54;
      return delay;
    }
  }
  if (run==271306) {
    if (ls<98)  { delay=54; return delay; }
    if (ls<118) { delay=52; return delay; }
    else        { delay=49; return delay; }
  }
  if (run==271307) {
    delay=49;
    return delay;
  }
  if (run==271310) {
    if (ls<12) {
      delay=49; // this was not recorded!! should be the original setting or the one before this run
      return delay;
    }
    else {
      delay=49;
      return delay;
    }
  }
  return delay;
}
