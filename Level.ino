#include <math.h>

#define MAX_ROOM_SIZE_X         18
#define MAX_ROOM_SIZE_Y         15
#define MIN_ROOM_SIZE_X         7
#define MIN_ROOM_SIZE_Y         7

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
  thisMap->mapSize.x_length = sum_x + 10;
  thisMap->mapSize.y_length = sum_y + 10;
}


static void setRoomPosition (struct levelMap *thisMap) {
  int dimension_x = thisMap->mapSize.x_length;
  int dimension_y = thisMap->mapSize.y_length;
  int mapLayout[dimension_x][dimension_y];
  
  for (int i = 0; i < dimension_x; i++) 
    for (int j = 0; j < dimension_y; j++)
      mapLayout[i][j] = 0;
      
  for (int i = 0; i < thisMap->roomCount; i++) {
    int x1, y1, x2, y2;

    //choose a x position that's not in another room
    do {
      x1 = rand()%(dimension_x-1);
      y1 = rand()%(dimension_y-1);
    } while (mapLayout[x1][y1]==1);

    //calculate position 2
    x2 = x1+thisMap->rooms[i].dimensions.x_length;
    y2 = y1+thisMap->rooms[i].dimensions.y_length;
    
    if (x2 >= dimension_x || y2 >= dimension_y || mapLayout[x2][y2] == 1) {
      i--;
      continue;
    }
    else {
      bool flag = false;
      for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
          if(mapLayout[x][y]==1) {
            i--;
            flag = true;
            break;
          }
        }
        if (flag) break;
      }
      if (flag) continue;
      thisMap->rooms[i].pos[0].x = x1;
      thisMap->rooms[i].pos[0].y = y1;
      thisMap->rooms[i].pos[1].x = x2;
      thisMap->rooms[i].pos[1].y = y2;
      for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
          mapLayout[x][y] = 1;
        }
      }
    }
  }
}

static void setRoomDimensions(struct levelMap *thisMap) {
  for (int i = 0; i < thisMap->roomCount; i++) {
    thisMap->rooms[i].dimensions.x_length = getRandomLength();
    thisMap->rooms[i].dimensions.y_length = getRandomLength();
  } 
}

struct levelMap CreateLevel(int level) {
  struct levelMap curr_level;
  Serial.println("swaga");
  curr_level.level = level;
  setRoomCount(&curr_level);
  setRoomDimensions(&curr_level);
  setMapSize(&curr_level);
  setRoomPosition(&curr_level);
  //printLevelInfo(curr_level);
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
}

