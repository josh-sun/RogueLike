#include <math.h>

#define MAX_ROOM_SIZE_X         15
#define MAX_ROOM_SIZE_Y         15
#define MIN_ROOM_SIZE_X         8
#define MIN_ROOM_SIZE_Y         8

struct position {
    int x;
    int y;
};

struct dimension {
  int x_length;
  int y_length;
};

struct room {
    struct position   pos[2];
    struct dimension  dimensions;
};

struct levelMap {
    int               level;
    int               roomCount;
    struct dimension  mapSize;
    struct room       rooms[11];
} ;

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
    sum_x+=thisMap->rooms[i].dimensions.x_length;
    sum_y+=thisMap->rooms[i].dimensions.y_length;
  }
  thisMap->mapSize.x_length = sum_x;
  thisMap->mapSize.y_length = sum_y;
  Serial.println(thisMap->roomCount);
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
      expandMap(thisMap, i);
      loopCount = 0;
    }

    int x1, y1, x2, y2;
    x1 = rand()%(thisMap->mapSize.x_length-MAX_ROOM_SIZE_X-1);
    y1 = rand()%(thisMap->mapSize.y_length-MAX_ROOM_SIZE_Y-1);
    x2 = x1+thisMap->rooms[i].dimensions.x_length;
    y2 = y1+thisMap->rooms[i].dimensions.y_length;
    

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

static void setRoomDimensions(struct levelMap *thisMap) {
  for (int i = 0; i < thisMap->roomCount; i++) {
    thisMap->rooms[i].dimensions.x_length = getRandomLength();
    thisMap->rooms[i].dimensions.y_length = getRandomLength();
  } 
}

static void expandMap (struct levelMap *thisMap, int currentRoom) {
  thisMap->mapSize.x_length += MAX_ROOM_SIZE_X;
  thisMap->mapSize.y_length += MAX_ROOM_SIZE_Y;
}

struct levelMap CreateLevel(int level) {
  struct levelMap curr_level;
  curr_level.level = level;
  setRoomCount(&curr_level);
  setRoomDimensions(&curr_level);  
  setMapSize(&curr_level);
  setRoomPosition(&curr_level);
  printLevelInfo(curr_level);
  return curr_level;
}

void printLevelInfo(struct levelMap curr_level) {
  Serial.print("Level: ");
  Serial.println(curr_level.level);
  Serial.print("Room Count: ");
  Serial.println(curr_level.roomCount);
  Serial.print("Map Size: ");
  Serial.print(curr_level.mapSize.x_length);
  Serial.print(" X ");
  Serial.println(curr_level.mapSize.y_length);
  for (int i = 0; i < curr_level.roomCount; i++) {
    Serial.print("Room ");
    Serial.print(i+1);
    Serial.println(": ");
    Serial.print("Dimensions: ");
    Serial.print(curr_level.rooms[i].dimensions.x_length);
    Serial.print(" X ");
    Serial.println(curr_level.rooms[i].dimensions.y_length);
    Serial.print("(");
    Serial.print(curr_level.rooms[i].pos[0].x);
    Serial.print(",");
    Serial.print(curr_level.rooms[i].pos[0].y);
    Serial.print(") (");
    Serial.print(curr_level.rooms[i].pos[1].x);
    Serial.print(",");
    Serial.print(curr_level.rooms[i].pos[1].y);
    Serial.print(")");
    Serial.println("");
  }
  Serial.println("");
  Serial.flush();
}

