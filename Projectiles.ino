struct position{
  int x,y;
};

struct projectile{
  struct position;
  int direction; //0 is left, 1 is right 2 is up and 3 is down
  int damage;
}

struct projectile CreateProjectile(int x, int y, int dir, int dmg){
  struct projectile shot = {x, y, dir, dmg};
  return shot;
}

void UpdateProjectilePosition(struct projectile *shot){
  switch(shot.direction){
    case 0: shot.x--;
    case 1: shot.x++;
    case 2: shot.y++;
    case 3: shot.y--;
   }
}

struct position ReturnPosition(struct projectile *shot){
  return shot.position;
}



