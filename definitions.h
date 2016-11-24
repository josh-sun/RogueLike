//
//  Definitions.h
//  
//
//  Created by Josh Sun on 2016-11-24.
//
//

#ifndef Definitions_h
#define Definitions_h

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

#endif /* Definitions_h */
