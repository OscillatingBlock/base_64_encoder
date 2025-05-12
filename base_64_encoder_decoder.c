#include <math.h>
#include <stdio.h>

// Converts a decimal number 'num' into its binary representation
// and stores the result in 'binary' array of given 'size' bits (usually 8)
void decimal_to_binary(int num, int *binary, int size) {
  for (int i = 0; i < size; i++) {
    binary[i] = 0;
  }
  while (num >= 1) {
    binary[--size] = num % 2;
    num /= 2;
  }
}

// Converts a subarray of binary bits into decimal
// The subarray goes from index 'start' to 'end' (non-inclusive)
int binary_to_decimal(int *binary, int start, int end) {
  int num = 0;
  int power = end - start - 1;
  for (int i = start; i < end; i++) {
    num += binary[i] * pow(2, power--);
  }
  return num;
}

int main() {
  int binary[800]; // stores the full binary stream of the input string
  char line[100];  // buffer to read user input from stdin
  char map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678"
                 "9+/"; // base64 encoding table
  char output[1000];    // stores the final base64 encoded string

  printf("Enter a string to encode: ");
  fgets(line, sizeof(line), stdin); // read input string including newline

  // Convert input characters to binary
  int i = 0;
  int j = 0; // binary array index
  while (line[i] != '\0' && line[i] != '\n') {
    int bit = (unsigned char)line[i]; // convert character to ASCII code
    int temp[8];
    decimal_to_binary(bit, temp, 8); // get 8-bit binary representation
    for (int i = 0; i < 8; i++) {
      binary[j++] = temp[i]; // append to main binary stream
    }
    i++;
  }

  int k = 0; // output array index
  int z = 0; // current position in binary stream
  int binary_len = j;

  // Process binary stream in 24-bit chunks
  while (z < binary_len) {
    int buffer_24[24] = {0}; // buffer for 24 bits (3 bytes)
    int bits_in_chunk = 0;

    // Fill buffer with up to 24 bits
    for (int i = 0; i < 24 && z < binary_len; i++) {
      buffer_24[i] = binary[z++];
      bits_in_chunk++;
    }

    // Determine how many base64 characters this chunk will produce
    int num_output_chars =
        (bits_in_chunk + 5) / 6; // ceiling of bits_in_chunk / 6
    int padding =
        4 - num_output_chars; // base64 output should always be 4 characters

    // Convert each group of 6 bits to a base64 character
    int start = 0;
    int end = 6;
    for (int i = 0; i < num_output_chars; i++) {
      int decimal =
          binary_to_decimal(buffer_24, start, end); // 6-bit group to decimal
      output[k++] = map[decimal]; // map decimal to base64 character
      start += 6;
      end += 6;
    }

    // Add '=' padding characters if needed
    while (padding-- > 0) {
      output[k++] = '=';
    }
  }

  output[k] = '\0'; // null-terminate the output string
  printf("Encoded string: %s \n", output);
  return 0;
}
