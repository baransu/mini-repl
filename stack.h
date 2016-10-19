// DOUBLE STACK

struct DoubleStack {
  int top;
  double stack[256];
};
typedef struct DoubleStack DoubleStack;

void d_init(DoubleStack *stos) {
  stos->top = 0;
}

int d_isEmpty(DoubleStack* stos) {
  return stos->top;
}

double d_pop(DoubleStack* stos) {
  const double last = stos->stack[stos->top];
  stos->top -= 1;
  return last;
}

void d_push(DoubleStack* stos, double wartosc) {
  stos->top += 1;
  stos->stack[stos->top] = wartosc;
}

int d_size(DoubleStack* stos) {
  return stos->top;
}


// CHAR* STACK

struct CharStack {
  int top;
  char stack[1024];
};
typedef struct CharStack CharStack;

void c_init(CharStack *stos) {
  stos->top = 0;
  for(unsigned short i = 0; i < 1024; i++) {
    stos->stack[i] = ' ';
  }
}

int c_isEmpty(CharStack* stos) {
  return stos->top;
}

char c_pop(CharStack* stos) {
  const char last = stos->stack[stos->top];
  stos->top -= 1;
  return last;
}

char c_back(CharStack* stos) {
  return stos->stack[stos->top];
}


void c_push(CharStack* stos, char wartosc) {
  stos->top += 1;
  stos->stack[stos->top] = wartosc;
}

int c_size(CharStack* stos) {
  return stos->top;
}
