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
  int nouvelindex = index + 1;
  if (index == size) {
    return 0;
  } else {
    // Recusive call!
    return array[index] + sum(array, size, nouvelindex);
  }
}

int main () {
  int size = 10;
  int array[10];
  int first_index = 0;

  init_array(array, size);
  printf(sum(array, size, first_index));
  return 0;
}
