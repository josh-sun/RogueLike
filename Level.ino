#include <math.h>

#define WORLD_SIZE_X        100
#define WORLD_SIZE_Y        100
#define MAX_ROOM_SIZE_X     20
#define MAX_ROOM_SIZE_Y     20
#define MIN_ROOM_SIZE_X     10
#define MIN_ROOM_SIZE_Y     10

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

struct levelMap CreateLevel(int level) {
  struct levelMap curr_Level = {0};
  int roomCount = rand()%3+2;
  int roomGenerated = 0;
  
  curr_Level.level = level;
  curr_Level.roomCount = roomCount;
  
  
  for (int i = 0; i < WORLD_SIZE_X; i+=MAX_ROOM_SIZE_X+5) {
    for (int j = 0 ; j < WORLD_SIZE_Y; j+=MAX_ROOM_SIZE_Y+5) {
       if (roomGenerated < roomCount) {
        roomGenerated++;
        int randLength = getRandomLength();
        Serial.println(curr_Level.rooms[0][0].pos[0]);
        setRandomPosition(&curr_Level.rooms[i][j].pos[0], i+4, j+4, i, j);
        curr_Level.rooms[i][j].pos[1].x = curr_Level.rooms[i][j].pos[0].x+randLength;
        curr_Level.rooms[i][j].pos[1].y = curr_Level.rooms[i][j].pos[0].y+randLength;

        /*
        Serial.print("Room (");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");
        Serial.println(": ");
        Serial.print("x1: ");
        Serial.print(curr_Level.rooms[i][j].pos[0].x);
        Serial.print(" y1: ");
        Serial.println(curr_Level.rooms[i][j].pos[0].y);
        Serial.print("x2: ");
        Serial.print(curr_Level.rooms[i][j].pos[1].x);
        Serial.print(" y2: ");
        Serial.println(curr_Level.rooms[i][j].pos[1].y);
        Serial.print("Length: ");
        Serial.print(randLength);
        Serial.println("");
        */
       }
    }
  } 
  printLevelInfo(curr_Level);
  return curr_Level;
}

void printLevelInfo(struct levelMap curr_Level) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Serial.print("Room Count: ");
      Serial.println(curr_Level.roomCount);
      Serial.print("Room (");
      Serial.print(i+1);
      Serial.print(",");
      Serial.print(j+1);
      Serial.print(")");
      Serial.println(": ");
      Serial.print("x1: ");
      Serial.print(curr_Level.rooms[j][i].pos[0].x);
      Serial.print(" y1: ");
      Serial.println(curr_Level.rooms[j][i].pos[0].y);
      Serial.print("x2: ");
      Serial.print(curr_Level.rooms[j][i].pos[1].x);
      Serial.print(" y2: ");
      Serial.println(curr_Level.rooms[j][i].pos[1].y);
      Serial.println("");
    }
  }
}

