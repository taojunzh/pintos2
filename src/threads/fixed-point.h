#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H

#define f (1<<14)

int int_to_fix(int n);
int fix_to_int(int x);
int add(int x,int y);
int sub(int x,int y);
int mul(int x,int y);
int div(int x,int y);
int addn(int x, int n);
int subn(int x, int n);
int muln(int x, int n);
int divn(int x, int n);


int int_to_fix(int n){
  return n*f;
}

int fix_to_int(int x){
  return x/f;
}

int add(int x, int y){
  return x+y;
}

int sub(int x,int y){
  return x-y;
}

int mul(int x,int y){
  return ((int64_t)x)*y/f;
}

int div(int x,int y){
  return ((int64_t)x)*f/y;
}

int addn(int x, int n){
  return x+n*f;
}

int subn(int x, int n){
  return x-n*f;
}

int muln(int x, int n){
  return x*n;
}

int divn(int x, int n){
  return x/n;
}


#endif
