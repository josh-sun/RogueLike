#include <math.h>
#include "definitions.h"

#define MAX_ROOM_SIZE_X         15
#define MAX_ROOM_SIZE_Y         15
#define MIN_ROOM_SIZE_X         8
#define MIN_ROOM_SIZE_Y         8

//forward declarations
struct monster CreateMonster(int level, int x, int y);
struct player  CreatePlayer (int x, int y);

/*
struct tunnel {
  struct position     endPos[2];
};
*/


static int getRandomLength() {
  return rand()%(MAX_ROOM_SIZE_X-MIN_ROOM_SIZE_X)+MIN_ROOM_SIZE_X;
}

static void setRoomCount(struct levelMap *thisMap) {

  int maximum = thisMap->level+2;
  int minimum;
  if (thisMap->level < 5) {
    minimum = 3;
  } else {
    minimum = thisMap->level-1;
  }
  if (maximum==minimum)
    thisMap->roomCount = maximum;
  else 
    thisMap->roomCount = rand()%(maximum-minimum)+minimum;
}

static void setMapSize(struct levelMap *thisMap) {
  int sum_x, sum_y;
  for (int i = 0; i < thisMap->roomCount; i++) {
    sum_x+=thisMap->rooms[i].len;
    sum_y+=thisMap->rooms[i].wid;
  }
  thisMap->len = sum_x;
  thisMap->wid = sum_y;
  //Serial.println(thisMap->roomCount);
}


static bool roomOverlaps (struct position pos[], int x1, int y1, int x2, int y2) {
if (pos[0].x > x2 || x1 > pos[1].x ||
    pos[0].y > y2 || y1 > pos[1].y) 
      return false;  
  return true;
}

static bool satisfiesMinSeparation (struct position pos[], int x1, int y1, int x2, int y2) {
  if (abs(pos[0].x-x2)>5&&abs(x1-pos[1].x)>5 &&
      abs(pos[0].y-y2)>5&&abs(y1-pos[1].y)>5)
      return true;
  return false;
}

static void setRoomPosition (struct levelMap *thisMap) {  
  int loopCount = 0;
  const int loopThreshold = 1000;

     
  for (int i = 0; i < thisMap->roomCount; i++) {
    if (loopCount++==loopThreshold) {
      expandMap(thisMap);
      loopCount = 0;
    }

    int x1, y1, x2, y2;
    x1 = rand()%(thisMap->len-MAX_ROOM_SIZE_X-1);
    y1 = rand()%(thisMap->wid-MAX_ROOM_SIZE_Y-1);
    x2 = x1+thisMap->rooms[i].len;
    y2 = y1+thisMap->rooms[i].wid;
    

    bool flag = false;
    for (int j = 0; j < i; j++) {
      if (roomOverlaps(thisMap->rooms[j].pos, x1, y1, x2, y2) ||
          !satisfiesMinSeparation(thisMap->rooms[j].pos, x1, y1, x2, y2)) {
        --i;
        flag = true;
        break;
      }
    }
    if (flag) continue;

    
    thisMap->rooms[i].pos[0].x = x1;
    thisMap->rooms[i].pos[0].y = y1;
    thisMap->rooms[i].pos[1].x = x2;
    thisMap->rooms[i].pos[1].y = y2;
  }
}

static int equOfLine(int x, int y, int x1, int y1, int x2, int y2) {
  return (y2-y1)*x + (x1-x2)*y + (x2*y1-x1*y2);
}

static bool intersectWithRoom (struct position pos[], int x1, int y1, int x2, int y2) {
  for (int x = x1; x<=x2;x++) {
    for (int y = y1; y<=y2; y++) {
      if (equOfLine(x,y,x1,y1,x2,y2)==0) return true;
    }
  }
  return false;
}

static void setRoomDimensions(struct levelMap *thisMap) {
  for (int i = 0; i < thisMap->roomCount; i++) {
    thisMap->rooms[i].len = getRandomLength();
    thisMap->rooms[i].wid = getRandomLength();
  } 
}

static void expandMap (struct levelMap *thisMap) {
  thisMap->len += MAX_ROOM_SIZE_X;
  thisMap->wid += MAX_ROOM_SIZE_Y;
}

/*
static void generateTunnels(struct levelMap *thisMap) {
  int currRoom1 = 0;
  int currRoom2 = 1; 
  
  for (int i = 0; i < thisMap->roomCount-1; i++) {
    for (int z = i+1; z < thisMap->roomCount; z++) { 
      currRoom1 = i;
      
      int x1,y1,x2,y2; //tunnel endpoints
      
      //room 1 coordinates
      int r1lx = thisMap->rooms[i].pos[0].x;
      int r1rx = thisMap->rooms[i].pos[1].x;
      int r1ly = thisMap->rooms[i].pos[0].y;
      int r1ry = thisMap->rooms[i].pos[1].y;
  
      //rooms2 coordinates
      int r2lx = thisMap->rooms[z].pos[0].x;
      int r2rx = thisMap->rooms[z].pos[1].x;
      int r2ly = thisMap->rooms[z].pos[0].y;
      int r2ry = thisMap->rooms[z].pos[1].y;
  
     
      if (r1lx > r2rx) { //r1 to the right of r2
        x1 = r2rx;
        y1 = rand()%(r2ry-r2ly-2)+r2ly+1;
        x2 = r1lx;
        y2 = rand()%(r1ry-r1ly-2)+r1ly+1;
      } else if (r2lx > r1rx) { //r2 to the right of r1
        x1 = r1rx;
        y1 = rand()%(r1ry-r1ly-2)+r1ly+1;
        x2 = r2lx;
        y2 = rand()%(r2ry-r2ly-2)+r2ly+1;
      } else if (r1ly > r2ry) { //r1 above r2
        x1 = rand()%(r2rx-r2lx-2)+r2lx+1;
        y1 = r2ly
        x2 = rand()%(r1rx-r1lx-2)+r1lx+1;
        y2 = r1ry;
      } else {  //r2 above r1
        x1 = rand()%(r1rx-r1lx-2)+r1lx+1;
        y1 = r1ly
        x2 = rand()%(r2rx-r2lx-2)+r2lx+1;
        y2 = r2ry;
      }
  
      bool isValidTunnel = true;
      for (int j = 0; j < thisMap->roomCount; j++) {
        if (j==currRoom1 || currRoom2) ++j;
        if (intersectWithRoom(thisMap->rooms[j]->pos, x1, y1, x2, y2)) {
          currRoom2++;
          --i;
          isValidTunnel = false;
          break;
        }
      }
      
      if(isValidTunnel) {
        thisMap->tunnels[i]->pos[0].x = x1;
        thisMap->tunnels[i]->pos[0].y = y1;
        thisMap->tunnels[i]->pos[1].x = x2;
        thisMap->tunnels[i]->pos[1].y = y2;
        struct room tempRoom = thisMap->rooms[i+1];
        thisMap->rooms[i+1] = thisMap->rooms[z];
        thisMap->rooms[z] = tempRoom;
      }
    }
  }
}
*/

static void generateRandMonsters(struct levelMap *thisMap) {
  for (int i = 0 ; i < thisMap->roomCount; i++) {
    int x = rand()%(thisMap->rooms[i].pos[1].x-thisMap->rooms[i].pos[0].x-2)+thisMap->rooms[i].pos[0].x+1;
    int y = rand()%(thisMap->rooms[i].pos[1].y-thisMap->rooms[i].pos[0].y-2)+thisMap->rooms[i].pos[0].y+1;
    thisMap->monsters[i] = CreateMonster(thisMap->level, x,y);
  }
}

struct levelMap CreateLevel(int level) {
  struct levelMap curr_level;
  curr_level.level = level;
  setRoomCount(&curr_level);
  setRoomDimensions(&curr_level);  
  setMapSize(&curr_level);
  setRoomPosition(&curr_level);
  generateRandMonsters(&curr_level);
  curr_level.usr = CreatePlayer(curr_level.rooms[0].pos[0].x+3, curr_level.rooms[0].pos[0].y+3);
  printLevelInfo(curr_level);
  return curr_level;
}

void printLevelInfo(struct levelMap curr_level) {
  Serial.print("Level: ");
  Serial.println(curr_level.level);
  Serial.print("Room Count: ");
  Serial.println(curr_level.roomCount);
  Serial.print("Map Size: ");
  Serial.print(curr_level.len);
  Serial.print(" X ");
  Serial.println(curr_level.wid);
  Serial.print("Player: (");
  Serial.print(curr_level.usr.pos.x);
  Serial.print(",");
  Serial.print(curr_level.usr.pos.y);
  Serial.println(")");
  for (int i = 0; i < curr_level.roomCount; i++) {
    Serial.print("Room ");
    Serial.print(i+1);
    Serial.println(": ");
    Serial.print("Dimensions: ");
    Serial.print(curr_level.rooms[i].len);
    Serial.print(" X ");
    Serial.println(curr_level.rooms[i].wid);
    Serial.print("(");
    Serial.print(curr_level.rooms[i].pos[0].x);
    Serial.print(",");
    Serial.print(curr_level.rooms[i].pos[0].y);
    Serial.print(") (");
    Serial.print(curr_level.rooms[i].pos[1].x);
    Serial.print(",");
    Serial.print(curr_level.rooms[i].pos[1].y);
    Serial.println(")");
    Serial.print("Monster: (");
    Serial.print(curr_level.monsters[i].pos.x);
    Serial.print(",");
    Serial.print(curr_level.monsters[i].pos.y);
    Serial.println(")");
    Serial.println("");
  }
  Serial.println("");
}

