#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "hash-map.h"
#include "math.h"

void onp(char* rownanie) {
  Stack stos;
  init(&stos);
  const int len = strlen(rownanie);
  for(unsigned int i = 0; i < len; i++) {
    char c = rownanie[i];
    if((c == '+' || c == '/' || c == '-' || c == '*' || c == '^') && size(&stos) > 1) {
      double wynik;
      double snd = pop(&stos);
      double fst = pop(&stos);
      switch(c) {
      case '+':
        wynik = fst + snd;
        break;
      case '-':
        wynik = fst - snd;
        break;
      case '/':
        if(snd == 0) {
          printf("Cannot divide by 0!!!");
          break;
        }
        wynik = fst / snd;
        break;
      case '*':
        wynik = fst * snd;
        break;
      case '^':
        wynik = power(fst, snd);
        break;
      }

      push(&stos, wynik);
    } else if (c >= 'a' && c <= 'z') {
      char function[64] = {' '};
      int iterator = 0;
      
      while(i < len && c >= 'a' && c <= 'z') {
        function[iterator++] = rownanie[i++];
        c = rownanie[i];
      }

      double wynik;
      if(strstr(function, "add") != 0) {
        double snd = pop(&stos);
        double fst = pop(&stos);
        wynik = fst + snd;
        push(&stos, wynik);
      } else if(strstr(function, "subtract") != 0) {
        double snd = pop(&stos);
        double fst = pop(&stos);
        wynik = fst - snd;
        push(&stos, wynik);
      } else if(strstr(function, "multiply") != 0) {
        double snd = pop(&stos);
        double fst = pop(&stos);
        wynik = fst * snd;
        push(&stos, wynik);
      } else if(strstr(function, "divide") != 0) {
        double snd = pop(&stos);
        double fst = pop(&stos);
        if(snd == 0) {
          printf("Cannot divide by 0!!!\n");
          return;
        }
        wynik = fst / snd;
        push(&stos, wynik);
      } else if(strstr(function, "pow") != 0) {
        double snd = pop(&stos);
        double fst = pop(&stos);
        wynik = power(fst, snd);
        push(&stos, wynik);
      } else if(strstr(function, "neg") != 0) {
        double fst = pop(&stos);
        wynik = -fst;
        push(&stos, wynik);
      } else if(strstr(function, "root") != 0) {
        double fst = pop(&stos);
        double snd = pop(&stos);
        wynik = root(fst, snd);
        push(&stos, wynik);
      } else if(strstr(function, "sqrt") != 0) {
        push(&stos, root(pop(&stos), 2));
      } else if(strstr(function, "factorial") != 0) { // factorial
        push(&stos, factorial(pop(&stos)));
      } else if(strstr(function, "sin") != 0) { // sine
        push(&stos, sine(pop(&stos)));
      } else if(strstr(function, "cos") != 0) { // cosine
        push(&stos, cosine(pop(&stos)));
      } else if(strstr(function, "rad") != 0) { // convert to radians
        push(&stos, to_radians(pop(&stos)));
      } else if(strstr(function, "deg") != 0) { // convert to degrees
        push(&stos, to_degrees(pop(&stos)));
      }

    } else if ((c >= '0' && c <= '9') || c == '.') {
      char number[256] = {' '};
      int iterator = 0;
      while((i < len && c >= '0' && c <= '9') || c == '.') {
        number[iterator++] = rownanie[i++];
        c = rownanie[i];
      }
      double val = 0;
      sscanf(number, "%lf", &val);
      push(&stos, val);
    }
  }
  printf("%f\n", pop(&stos));
}

int main () {
  char rownanie[256] = {' '};
  // TODO some command about entering REPL mode or something
  printf("> ");

  while(fgets(rownanie, sizeof(rownanie), stdin) != NULL && strstr(rownanie, "exit") == 0 && strlen(rownanie) > 1) {
    onp(rownanie);
    printf("> ");
  }

  return 0;
}


