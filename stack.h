struct Stack {
  int top;
  double stack[256];
};
typedef struct Stack Stack;

void init(Stack *stos) {
  stos->top = 0;
}

int isEmpty(Stack* stos) {
  return stos->top;
}

double pop(Stack* stos) {
  stos->top -= 1;
  return stos->stack[stos->top];
}

void push(Stack* stos, double wartosc) {
  stos->stack[stos->top] = wartosc;
  stos->top += 1;
}

int size(Stack* stos) {
  return stos->top;
}
