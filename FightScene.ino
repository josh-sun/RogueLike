#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#define CHAR_PIXEL      8
#define ROOM_WIDTH     16
#define ROOM_HEIGHT     4
#define DELAY        1500

/*
void Attack(struct monster thisMonster){
  char basicAttack = "The enemy swings its arms for a punch!";
  char specialAttacks[4] = {"The enemy slashes you with its claws!", "The enemy dives in to bite you!", "The enemy whips its tail at you!", "The enemy throws a boulder at you!"}
  char abilities[2] = {"The monster spits out flames!", "The monster casts a magic spell!"}
  
  OrbitOledMoveto(0,0);
  
  if(thisMonster.level < 2) OrbitOledDrawString("%c", basicAttack);
  else if(thisMonster.level < 6) OrbitOledDrawString("%c", specialAttacks[rand() % 4]);
  else OrbitOledDrawString("%c", abilities[rand() % 2]);
  
}


void EnterFightScene(){
  OrbitOledClearBuffer;
  OrbitOledMoveto(5,5);
  OrbitOledDrawString("You have encountered monster %c!", setname());
  OrbitOledUpdate
  delay(DELAY); //delay
  //drawing
  char monster1 [ROOM_HEIGHT][ROOM_WIDTH]= 
  { {'.','.','.','.','.','^','_','_','_','^','.','.','.','.','.','.'},
    {'.','.','.','.','.','|','*',' ','*','|','.','.','.','.','.','.'},
    {'.','.','.','.','.','|',' ','^',' ','|','.','.','.','.','.','.'},
    {'.','.','.','_','_','_','-','-','-','_','_','_','.','.','.','.'}
  }; //working on doing this with pixels instead
  
  OrbitOledClearBuffer;
  
  for (int i = 0; i < ROOM_WIDTH; i++ ) {
    for (int j = 0; j < ROOM_HEIGHT; j++) {
      OrbitOledMoveTo(i*CHAR_PIXEL,j*CHAR_PIXEL);
      OrbitOledDrawChar(monster1[j][i]);
    }
  }
  OrbitOledMoveto(0,0);
  OrbitOledDrawString("Get ready to fight!");
  OrbitOledUpdate;
  delay(DELAY);

  OrbitOledClearBuffer;
}

*/
