#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "hash-map.h"
#include "math.h"

void onp(char* rownanie) {
  DoubleStack stos;
  d_init(&stos);
  const int len = strlen(rownanie);
  for(unsigned int i = 0; i < len; i++) {
    char c = rownanie[i];

    if((c == '+' || c == '/' || c == '-' || c == '*' || c == '^') && d_size(&stos) > 1) {
      double wynik;
      double snd = d_pop(&stos);
      double fst = d_pop(&stos);

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

      d_push(&stos, wynik);
    }

    else if (c >= 'a' && c <= 'z') {
      char function[64] = {' '};
      int iterator = 0;

      while(i < len && c >= 'a' && c <= 'z') {
        function[iterator++] = rownanie[i++];
        c = rownanie[i];
      }

      double wynik;
      if(strstr(function, "add") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = fst + snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "subtract") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = fst - snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "multiply") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = fst * snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "divide") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        if(snd == 0) {
          printf("Cannot divide by 0!!!\n");
          return;
        }
        wynik = fst / snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "pow") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = power(fst, snd);
        d_push(&stos, wynik);
      }

      else if(strstr(function, "neg") != 0) {
        double fst = d_pop(&stos);
        wynik = -fst;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "root") != 0) {
        double fst = d_pop(&stos);
        double snd = d_pop(&stos);
        wynik = root(fst, snd);
        d_push(&stos, wynik);
      }

      else if(strstr(function, "sqrt") != 0) {
        d_push(&stos, root(d_pop(&stos), 2));
      }

      else if(strstr(function, "factorial") != 0) { // factorial
        d_push(&stos, factorial(d_pop(&stos)));
      }

      else if(strstr(function, "sin") != 0) { // sine
        d_push(&stos, sine(d_pop(&stos)));
      }

      else if(strstr(function, "cos") != 0) { // cosine
        d_push(&stos, cosine(d_pop(&stos)));
      }

      else if(strstr(function, "rad") != 0) { // convert to radians
        d_push(&stos, to_radians(d_pop(&stos)));
      }

      else if(strstr(function, "deg") != 0) { // convert to degrees
        d_push(&stos, to_degrees(d_pop(&stos)));
      }

    }

    else if ((c >= '0' && c <= '9') || c == '.') {
      char number[256] = {' '};
      int iterator = 0;
      while((i < len && c >= '0' && c <= '9') || c == '.') {
        number[iterator++] = rownanie[i++];
        c = rownanie[i];
      }
      double val = 0;
      sscanf(number, "%lf", &val);
      d_push(&stos, val);
    }

  }

  printf("%f\n", d_pop(&stos));
}

void infix(char* wejscie) {
  CharStack stos;
  c_init(&stos);
  const unsigned int len = strlen(wejscie);
  char wyjscie[1024] = {' '};
  unsigned int iterator = 0;
  for(int i = 0; i < len; i++) {
    char c = wejscie[i];

    if(c == '(') {
        c_push(&stos, c);
    }

    else if (c == ')') {
      while(c_size(&stos) > 0) {
        char top = c_pop(&stos);
        if(top != '(') {
          wyjscie[iterator++] = top;
          wyjscie[iterator++] = ' ';
        } else break;
      }
    }

    else if (c == '+' || c == '-') {
      while(c_size(&stos) > 0) {
        char o2 = c_back(&stos);
        if(o2 == '+' || o2 == '-' || o2 == '*' || o2 == '/') {
          wyjscie[iterator++] = o2;
          wyjscie[iterator++] = ' ';
          c_pop(&stos);
        } else break;
      }
      c_push(&stos, c);
    }

    else if (c == '*' || c == '/') {
      while(c_size(&stos) > 0) {
        char o2 = c_back(&stos);
        if(o2 == '*' || o2 == '/') {
          wyjscie[iterator++] = o2;
          wyjscie[iterator++] = ' ';
          c_pop(&stos);
        } else break;
      }
      c_push(&stos, c);
    }

    else if (c >= '0' && c <= '9') {
      // TODO liczby zmienno-przecinkowe
      char number[256] = {' '};
      unsigned int ii = 0;
      do {
        number[ii++] = c;
        c = wejscie[++i];
      } while(i < len - 1 && c >= '0' && c <= '9');
      --i;
      const unsigned int ln = strlen(number);
      for(unsigned int i = 0; i < ln; i++) {
        wyjscie[iterator++] = number[i];
      }
      wyjscie[iterator++] = ' ';
    }

    else if (c >= 'a' && c <= 'z') { // funkcje
      // TODO zczytaj string
      // TODO stworz stos funckji
      // TODO wsadz string na stos
    }
  }

  while(c_size(&stos) > 0) {
    wyjscie[iterator++] = c_pop(&stos);
  }

  onp(wyjscie);
}

int main (int argc, char** argv) {
  int mode = 0; // set infix to default
  for(unsigned int i = 0; i < argc; i++) {
    char* arg = argv[i];
    if(strstr(arg, "--infix") != 0) {
      mode = 0;
      printf("Running in INFIX mode\n");
      break;
    }
    else if(strstr(arg, "--onp") != 0) {
      mode = 1;
      printf("Running in ONP mode\n");
      break;
    }
  }

  char rownanie[256] = {' '};
  printf("> ");

  while(fgets(rownanie, sizeof(rownanie), stdin) != NULL && strstr(rownanie, "exit") == 0 && strlen(rownanie) > 1) {
    switch(mode) {
    case 0: //infix
      infix(rownanie);
      break;
    case 1: // onp
      onp(rownanie);
      break;
    }
    printf("> ");
  }

  return 0;
}


