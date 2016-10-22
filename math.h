#define PI 3.14

double to_radians(const double x) {
  return x/180 * PI;
}

double to_degrees(const double x) {
  return x * 180/PI;
}

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

double sine(double x) { // liczmy w radianach
  // sprowadzamy x do [-PI, PI];
  x = fmod(x, 2 * PI);
  if(x > PI) x -= 2 * PI;
  else if (x < -PI) x += 2 * PI;

  double sin = x;
  unsigned short isNeg = 1;

  const double n = 9;
  for(int i = 3; i <= n; i += 2) {
    if(isNeg) {
      sin -= power(x,i)/factorial(i);
      isNeg = 0;
    } else {
      sin += power(x,i)/factorial(i);
      isNeg = 1;
    }
  }

  return sin;
}

double cosine(double x) { // liczmy w radianach
  // sprowadzamy x do [-PI, PI];
  x = fmod(x, 2 * PI);
  if(x > PI) x -= 2 * PI;
  else if (x < -PI) x += 2 * PI;

  double cos = 1;
  unsigned short isNeg = 1;

  const short n = 10;
  for(int i = 2; i <= n; i += 2) {
    if(isNeg) {
      cos -= power(x, i) / factorial(i);
      isNeg = 0;
    } else {
      cos += power(x, i) / factorial(i);
      isNeg = 1;
    }
  }

  return cos;
}

double tangent(double x) {
  double c = cosine(x);
  if(c == 0) return 0;
  return sine(x)/c;
}

double cotangent(double x) {
  double s = sine(x);
  if(s == 0) return 0;
  return cosine(x)/s;
}

double root(double a, double n) {
  double result = a;
  double tmp = power(result,(n - 1));
  double precision = 0.00000001;

  while (fabs(a - tmp * result) >= precision) {
    result = 1 / n * ((n - 1) * result + (a / tmp));
    tmp = power(result, n-1);
  }

  return result;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

double absolute(double x) {
  return x < 0 ? x * -1 : x;
}
