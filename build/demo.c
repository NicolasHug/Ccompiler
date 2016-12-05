/* Demo file: compute the sum of the elements of an array with a recursive
 * function.
 */


// Initialize an array of int.
void init_array (int * array, int size) {
  int i;
  int val = 0;
  for (i = 0; i < size; i++) {
      *(array + i) = i + 1;
  }
}

/*
 * Return the sum of the elements in array.
 */
int sum (int * array , int size, int index) {
  int new_index = index + 1;
  if (index == size) {
    return 0;
  } else {
    // Recusive call!
    return array[index] + sum(array, size, new_index);
  }
}

int main () {
  int size = 10;
  int array[10];

  init_array(array, size);
  printf(sum(array, size, 0));
  return 0;
}
