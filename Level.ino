#include <math.h>

#define MAX_WORLD_SIZE_X        100
#define MAX_WORLD_SIZE_Y        100
#define MAX_ROOM_SIZE_X         25
#define MAX_ROOM_SIZE_Y         25
#define MIN_ROOM_SIZE_X         10
#define MIN_ROOM_SIZE_Y         10

struct position {
    int x;
    int y;
};

struct room {
    struct position   pos[2];
};

struct levelMap {
    int               level;
    int               roomCount;
    int               mapSize[2];
    struct room       rooms[4][4];
    //add struct monster
} ;

static void setRandomPosition (struct position *pos, int max_x, int max_y, int min_x, int min_y) {
  pos->x = rand()%(max_x-min_x)+min_x;
  pos->y = rand()%(max_y-min_y)+min_y;
}

static int getRandomLength() {
  return rand()%(MAX_ROOM_SIZE_X-MIN_ROOM_SIZE_X)+MIN_ROOM_SIZE_X;
}

static int getRandomRoomCount(int level) {
  int maximum = level+1;
  int minimum;
  if (level > 5)
    minimum = level-2;
  else 
    minimum = 3;
  return rand()%(maximum-minimum)+minimum;
}

struct levelMap CreateLevel(int level) {
  struct levelMap curr_level;
  int roomGenerated = 0;
  curr_level.level = level;
  curr_level.roomCount = getRandomRoomCount();
 
  for (int i = 0; i < 4; i++) {
    for (int j = 0 ; j < 4; j++) {
       if (roomGenerated < roomCount) {
        roomGenerated++;
        int randLength = getRandomLength();
        setRandomPosition(&curr_level.rooms[i][j].pos[0], i*25+4, j*25+4, i*25, j*25);
        curr_level.rooms[i][j].pos[1].x = curr_level.rooms[i][j].pos[0].x+randLength;
        curr_level.rooms[i][j].pos[1].y = curr_level.rooms[i][j].pos[0].y+randLength;

        /*
        Serial.print("Room (");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");
        Serial.println(": ");
        Serial.print("x1: ");
        Serial.print(curr_level.rooms[i][j].pos[0].x);
        Serial.print(" y1: ");
        Serial.println(curr_level.rooms[i][j].pos[0].y);
        Serial.print("x2: ");
        Serial.print(curr_level.rooms[i][j].pos[1].x);
        Serial.print(" y2: ");
        Serial.println(curr_level.rooms[i][j].pos[1].y);
        Serial.print("Length: ");
        Serial.print(randLength);
        Serial.println("");
        */
       }
    }
    
  } 
  printLevelInfo(curr_level);
  return curr_level;
}

void printLevelInfo(struct levelMap curr_level) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Serial.print("Room Count: ");
      Serial.println(curr_level.roomCount);
      Serial.print("Room (");
      Serial.print(i+1);
      Serial.print(",");
      Serial.print(j+1);
      Serial.print(")");
      Serial.println(": ");
      Serial.print("x1: ");
      Serial.print(curr_level.rooms[j][i].pos[0].x);
      Serial.print(" y1: ");
      Serial.println(curr_level.rooms[j][i].pos[0].y);
      Serial.print("x2: ");
      Serial.print(curr_level.rooms[j][i].pos[1].x);
      Serial.print(" y2: ");
      Serial.println(curr_level.rooms[j][i].pos[1].y);
      Serial.println("");
    }
  }
}

