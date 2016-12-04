void f (int a) {
  int newA = a - 1;
  if (a > 0) {
    f(newA);
  }
}
int main () {
  int a = 3;
  f(a);
  return 0;
}
