/*
int adr = EEPROM.length;
#DEFINE X_POS     20
#DEFINE Y_1       15
#DEFINE Y_2       30
#DEFINE Y_3       45
#DEFINE Y_SCORE   0

//in the setup make sure to do EEPROM.clear

int compare( const void* a1, const void* b1){
     int a = * ( (int*) a1 );
     int b = * ( (int*) b1 );

     if ( a == b ) return 0;
     else if ( a < b ) return -1;
     else return 1;
}


void StoreScore(int score){
  if(EEPROM.read(adr) < value) EEPROM.write(adr, score);
  if (adr) adr --;
  qsort(EEPROM, EEPROM.length, sizeof(int), compare);
}

void DisplayScore(){ //displaying top 3
  OrbitOledMoveto(X_POS, Y_SCORE);
  OrbitOledDrawString("--HIGHSCORES--");

  OrbitOledMoveto(X_POS, Y_1);
  OrbitOledDrawString("1. %d", EEPROM.read(EEPROM.length));

  OrbitOledMoveto(X_POS, Y_2);
  OrbitOledDrawString("2. %d", EEPROM.read(EEPROM.length-1));

  OrbitOledMoveto(X_POS, Y_3);
  OrbitOledDrawString("3. %d", EEPROM.read(EEPROM.length-2));
}*/
