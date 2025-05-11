#include <math.h>
#include <stdio.h>

void decimal_to_binary(int num, int *binary, int size) {
  for (int i = 0; i < size; i++) {
    binary[i] = 0;
  }
  while (num >= 1) {
    binary[--size] = num % 2;
    num /= 2;
  }
}

int binary_to_decimal(int *binary, int start, int end) {
  int num = 0;
  int power = end - start - 1;
  for (int i = start; i < end; i++) {
    num += binary[i] * pow(2, power--);
  }
  return num;
}

int main() {
  int binary[800]; // stream to store binary form of line
  char line[100];  // to store input from user via stdin
  char map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678"
                 "9+/"; // base64 characters
  char output[1000];    // to store output

  printf("Enter a string to encode: ");
  // get users input
  fgets(line, sizeof(line), stdin);

  // convert input in binary
  int i = 0;
  int j = 0;
  while (line[i] != '\0' && line[i] != '\n') {
    int bit = (unsigned char)line[i]; // convert char to ascii
    int temp[8];
    decimal_to_binary(bit, temp, 8);
    for (int i = 0; i < 8; i++) {
      binary[j++] = temp[i];
    }
    i++;
  }

  binary[j] = 999; // j is binary length
  int k = 0;       // current index of output array
  int z = 0;       // current index of binary stream
  int binary_len = j;
  while (z < j) {
    int buffer_24[24] = {0};
    int j = 0;
    int i = 0;
    // read input in chunks of 8 bit blocks in buffer_24 3 times
    while (i < 3) {
      int loop_done = 0;
      for (int k = 0; k < 8; k++) {
        if (binary[z] != 999) {
          buffer_24[j++] = binary[z++];
        } else {
          loop_done = 1;
          break;
        }
      }
      if (loop_done == 0) {
        i++;
      } else {
        break;
      }
    }

    // if 'i' <= 2 then we need to do padding
    int padding = 0;
    if (i <= 2) {
      padding = 3 - i;
    }
    int padd = padding;
    while (padding > 0) {
      buffer_24[j++] = 0;
      buffer_24[j++] = 0;
      padding--;
    }

    // now convert 24 bit blocks to 6 bit blocks
    // covert those 6 bit blocks to decimal
    // convert decimal to bsse64 chars
    int start = 0;
    int end = 6;

    for (int i = 0; i < 4 - padd; i++) {
      int decimal = binary_to_decimal(buffer_24, start, end);
      start += 6;
      end += 6;
      output[k++] = map[decimal];
    }

    // now add = for padd
    while (padd > 0) {
      output[k++] = '=';
      padd--;
    }
  }
  output[k] = '\0';
  printf("Encoded string: %s \n", output);
  return 0;
}
