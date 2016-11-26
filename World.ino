//Forward Declarations
struct levelMap;
struct levelMap CreateLevel();

#define LEVELS_COUNT    6

static struct world {
  struct levelMap   levels[LEVELS_COUNT];
} thisWorld;


void CreateWorld() {

thisWorld.levels[0] = CreateLevel(1);
thisWorld.levels[1] = CreateLevel(2);
thisWorld.levels[2] = CreateLevel(3);
thisWorld.levels[3] = CreateLevel(4);
thisWorld.levels[4] = CreateLevel(5);
thisWorld.levels[5] = CreateLevel(6);

   
  /*
  for (int i = 0; i < LEVELS_COUNT; i++) {
    thisWorld.levels[i] = CreateLevel(i+1);

  }
  */
  
}

