#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap_char (char * a, char * b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}


size_t strlen (const char * str)
{
    size_t len = 0;
    while(*str != '\0')
    {
        ++str;
        ++len;
    }
    return len;
}


void reverse (char * str)
{
    if (str == NULL) return;
    
    size_t len = strlen(str);
    char * ptr = str;
   
    ptr = str;                           // begin
    char * right = ptr + len - 1;        // end - 1
    for (size_t i = 0; i < len / 2; ++i)
    {
        swap_char(ptr, right);
        ++ptr;
        --right;
    }
}


int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
