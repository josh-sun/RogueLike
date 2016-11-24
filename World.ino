//Forward Declarations
struct levelMap;
struct levelMap CreateLevel();

#define LEVELS_COUNT    9 

static struct world {
  struct levelMap   levels[LEVELS_COUNT];
  int               curr_Level;
} thisWorld;


void CreateWorld() {
  for (int i = 0; i < LEVELS_COUNT; i++)
    thisWorld.levels[i] = CreateLevel(i+1);
}

