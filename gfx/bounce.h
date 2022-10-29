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

#endif
