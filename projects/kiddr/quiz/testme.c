/* Riam Sangdoung
 * CS 362 W 2018
 * testme.c
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{

// To get a random ASCII character in the range [32, 126]
  char c = (rand() % (127 - 32)) + 32;
  return c;
}

char *inputString()
{
  int length = 6;
  char* s = malloc(length);
  int i;

// To generate a random string of length 6
// 5 characters with a null terminator
  for(i = 0; i < length - 1; i++)
  {

// To get a random ASCII character in the range [97-122]
    s[i] = (rand() % (123-97)) + 97;
  }
  s[i] = '\0';

  return s;
}

void testme()
{
  int tcCount = 0;
  char c;
  char *s;

  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();

// Will print a status of every millionth iteration
    if(tcCount % 1000000 == 0)
      printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {

// Prints error message
      printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
      printf("error \n");
      free(s);
      exit(200);
    }

    free(s);

  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
