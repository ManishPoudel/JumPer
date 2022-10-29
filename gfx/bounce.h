#ifndef BOUNCE
#define BOUNCE

int inside_line(int border_1, int border_2, int point)
{
  if( ((border_1 <= point) && ( point <= border_2 )) || ((border_2 <= point)& & ( point <= border_1 )) ) {
    return 1;
  }
  return 0;
}

int inside(int x1, int y1, int x2, int y2, int a, int b) {
  if( inside_line(x1, x2, a) && inside_line(y1, y2, b) )
    return 0;
  return 1;
}
int bounce(float * vx, float * vy, float nx, float ny)
{
  float mag_nor = *vx * nx + *vy * ny;
  float norx = mag_nor * nx;
  float nory = mag_nor * ny;
  vx -= 2 * norx;
  vy -= 2 * nory;
}
#endif
