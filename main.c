#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "hash-map.h"

double power(double x, double n) {
  if(n == 0.0) {
    return 1.0;
  } else if((int)n % 2 == 1) {
    return x * power(x, n - 1);
  } else {
    double a = power(x, n/2.0);
    return a * a;
  }
}

double factorial(double x) {
  double result = 1;
  for(int i = 1; i <= x; i++) {
    result *= i;
  }
  return result;
}

double sine(double x) {
  x = fmod(x, 2 * 3.14);
  double sin = x;
  const short n = 7;

  for(int i = 3; i <= n; i += 4)
    sin -= power(x, i) / factorial(i);

  for(int i = 3; i <= n; i += 4)
    sin += power(x, i) / factorial(i);

  return sin;
}

double cosine(double x) {
  x = fmod(x, 2 * 3.14);
  double cos = 1;
  const short n = 8;

  for(int i = 2; i <= n; i += 4)
    cos -= power(x, i) / factorial(i);

  for(int i = 4; i <= n; i += 4)
    cos += power(x, i) / factorial(i);

  return cos;
}

double root(double a, double n) {
  double result = a;
  double tmp = power(result,(n-1));
  double precision = 0.00000001;

  while (fabs(a - tmp * result) >= precision) {
    result = 1/n*((n-1)*result + (a/tmp));
    tmp = power(result, n-1);
  }

  return result;
}

void onp(char* rownanie) {
  Stack stos;
  init(&stos);
  int len = sizeof(rownanie);
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
          printf("Cannot divide by 0!!!");
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
      } else if(strstr(function, "factorial") != 0) {
        push(&stos, factorial(pop(&stos)));
      } else if(strstr(function, "sin") != 0) {
        push(&stos, sine(pop(&stos)));
      } else if(strstr(function, "cos") != 0) {
        push(&stos, cosine(pop(&stos)));
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
  printf("> ");

  while(fgets(rownanie, sizeof(rownanie), stdin) != NULL && strstr(rownanie, "exit") == 0 && strlen(rownanie) > 1) {
    onp(rownanie);
    printf("> ");
  }

  return 0;
}


