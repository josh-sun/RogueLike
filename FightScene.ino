#include <stdbool.h>
#include <string.h>

#include <FillPat.h>
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
  OrbitOledMoveTo(5,5);
  OrbitOledDrawString("You have encountered monster %c!", setname());
  OrbitOledUpdate
  delay(DELAY); //delay

  
  //drawing

  OrbitOledClearBuffer;

  OrbitOledMoveTo(45,5);    //head
  OrbitOledDrawRect(83,25); 
  OrbitOledMoveto(46,6);
  OrbitOledDrawRect(82,24);
  
  OrbitOledMoveTo(45,2);    //ears
  OrbitOledLineTo(45,5);
  OrbitOledMoveTo(45,2);
  OrbitOledLineTo(52,5);

  OrbitOledMoveTo(83,2);
  OrbitOledLineTo(83,5);
  OrbitOledMoveTo(83,2);
  OrbitOledLineTo(76,5);

  OrbitOledMoveTo(59,12);   //eyes
  OrbitOledDrawRect(55,16);
  OrbitOledMoveTo(69,12);
  OrbitOledDrawRect(73,16);

  OrbitOledMoveTo(64,17);   //mouth
  OrbitOledLineTo(59,23);
  OrbitOledMoveTo(64,17);
  OrbitOledLineTo(69,23);

  OrbitOledMoveTo(55,8);    //eyebrows
  OrbitOledLineTo(61,12);
  OrbitOledMoveTo(73,8);
  OrbitOledLineTo(67,12);

  OrbitOledMoveTo(34,32);   //arms
  OrbitOledLineTo(28,17);
  OrbitOledMoveTo(37,32);
  OrbitOledLineTo(31,17);
  OrbitOledMoveTo(91,32);
  OrbitOledLineTo(97,17);
  OrbitOledMoveTo(94,32);
  OrbitOledLineTo(100,17);

  OrbitOledMoveTo(28,17);
  OrbitOledLineTo(22,11);
  OrbitOledMoveTo(22,11);
  OrbitOledLineTo(28,13);
  OrbitOledMoveto(28,13);
  OrbitOledLineTo(27,6);
  OrbitOledMoveTo(27,6);
  OrbitOledLineTo(29,11);
  OrbitOledMoveTo(29,11);
  OrbitOledLineTo(31,8);
  OrbitOledMoveTo(31,8);
  OrbitOledLineTo(31,17);

  OrbitOledMoveTo(100,17);
  OrbitOledLineTo(106,11);
  OrbitOledMoveTo(106,11);
  OrbitOledLineTo(100,13);
  OrbitOledMoveTo(100,13);
  OrbitOledLineTo(101,6);
  OrbitOledMoveTo(101,6,);
  OrbitOledLineTo(99,11);
  OrbitOledMoveTo(99,11);
  OrbitOledLineTo(97,8);
  OrbitOledMoveTo(97,8);
  OrbitOledMoveTo(97,17);
  
  

  OrbitOledMoveto(0,0);
  OrbitOledDrawString("Get ready to fight!");
  OrbitOledUpdate;
  delay(DELAY);

  OrbitOledClearBuffer;
}

*/
