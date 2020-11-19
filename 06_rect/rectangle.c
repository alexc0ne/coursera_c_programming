#include <stdio.h>
#include <stdlib.h>



//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b)
{
    if (a < b) return a;
    return b;
}
int max (int a, int b)
{
    if (a > b) return a;
    return b;
}



//Declare your rectangle structure here!
typedef struct rectangle_t
{
    int x, y, width, height;
}
rectangle;



rectangle canonicalize(rectangle r)
{
    if (r.width < 0)
    {
        r.x += r.width;
        r.width *= -1;
    }

    if (r.height < 0)
    {
        r.y += r.height;
        r.height *= -1;
    }

    return r;
}


typedef struct segment_t
{
    int left, right;
}
segment;



segment get_segment(int x1, int x2, int x3, int x4)
{
    segment s;
    
    if (x1 > x4 || x2 < x3)
    {
        s.left = s.right = 0;
        return s;
    }
    
    int tmp = 0;
    int arr[4] = {x1, x2, x3, x4};
    for (int i = 0; i < 3; ++i)
        for (int j = i + 1; j < 4; ++j)
            if (arr[i] > arr[j])
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
    s.left = arr[1];
    s.right = arr[2];    

    return s;
}


rectangle intersection(rectangle r1, rectangle r2)
{
    r1 = canonicalize(r1);
    r2 = canonicalize(r2);
    rectangle r;

    if (r1.x + r1.width < r2.x || r2.x + r2.width < r1.x)
    {
        r.x = r.y = r.width = r.height = 0;
        return r;
    }

    if (r1.y + r1.height < r2.y || r2.y + r2.height < r1.y)
    {
        r.x = r.y = r.width = r.height = 0;
        return r;
    }

    segment x_segment = get_segment(r1.x, r1.x + r1.width, r2.x, r2.x + r2.width);
    segment y_segment = get_segment(r1.y, r1.y + r1.height, r2.y, r2.y + r2.height);
    
    r.x = x_segment.left;
    r.y = y_segment.left;
    r.width = x_segment.right - x_segment.left;
    r.height = y_segment.right - y_segment.left;

    return r;
}


//======================================================
//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
