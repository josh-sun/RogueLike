//
//  Definitions.h
//  
//
//  Created by Josh Sun on 2016-11-24.
//
//

#ifndef Definitions_h
#define Definitions_h

#define NO_TILT -1
#define UP      0
#define DOWN    1
#define LEFT    2
#define RIGHT   3

struct position {
    int x;
    int y;
};


struct room {
    struct position   pos[2];
    int len;
    int wid;
};

struct player{
  int                 level;
  int                 health;
  int                 experience;
  struct position     pos;
};


struct monster{
  int               level;
  int               health;
  char              name;
  struct  position  pos;
};


struct levelMap {
    int               level;
    int               roomCount;
    int               len;
    int               wid;
    struct room       rooms[11];
    struct monster    monsters[22];
    struct player     usr;
    //struct tunnel     tunnels[30];
} ;





#endif /* Definitions_h */
