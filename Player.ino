struct position{
  int x,y;
}

struct player{
  int health, x, y;
}

struct player CreatePlayer (int x, int y, int health){
  struct player Player1 = {x,y,health};
  return Player1;
}



