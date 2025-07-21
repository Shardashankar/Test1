#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive function to convert decimal to binary
void decimalToBinary(int num, char *binary, int index) {
    if (index < 0) return;
    binary[index] = (num % 2) + '0';
    decimalToBinary(num / 2, binary, index - 1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *inputFile = argv[2];
    char *outputFile = argv[3];

    FILE *in = fopen(inputFile, "r");
    if (!in) {
        perror("Error opening input file");
        return 1;
    }

    FILE *out = fopen(outputFile, "w");
    if (!out) {
        perror("Error opening output file");
        fclose(in);
        return 1;
    }

    int count = 0, num;
    while (count < n && fscanf(in, "%d", &num) == 1) {
        char binary[17];
        binary[16] = '\0'; // Null-terminate
        decimalToBinary(num, binary, 15); // Fill binary from right to left

        fprintf(out, "The binary equivalent of %d is %s\n", num, binary);
        count++;
    }

    fclose(in);
    fclose(out);

    // Display the output file content
    FILE *result = fopen(outputFile, "r");
    if (!result) {
        perror("Error opening output file for reading");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), result)) {
        printf("%s", line);
    }

    fclose(result);
    return 0;
}
