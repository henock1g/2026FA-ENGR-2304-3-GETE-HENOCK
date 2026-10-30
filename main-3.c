/* 2026-ENGR-2304-3-GETE-HENOCK-P02 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Function prototypes
void decimalToBinary(int decimal);
int binaryToDecimal(const char *binStr);
void binaryToHex(const char *binStr);
void hexToBinary(const char *hexStr);
int isBinary(const char *str);
int isHex(const char *str);
void printMenu();

int main() {
    char input[100];
    int choice;

    while (1) {
        printMenu();
        printf("Enter your choice (1-2) or 'exit' to quit: ");
        scanf("%s", input);

        if (strcasecmp(input, "exit") == 0) {
            break;
        }

        choice = atoi(input);
        if (choice == 1) {
            // Decimal to binary or binary to decimal
            printf("Enter a decimal number (-127 to 127) or a binary number: ");
            scanf("%s", input);
            if (isBinary(input)) {
                int decimal = binaryToDecimal(input);
                printf("Binary %s is decimal %d\n", input, decimal);
            } else {
                int decimal = atoi(input);
                if (decimal < -127 || decimal > 127) {
                    printf("Number out of range.\n");
                } else {
                    decimalToBinary(decimal);
                }
            }
        } else if (choice == 2) {
            // Hex to binary or binary to hex
            printf("Enter a binary number or a hex number starting with 0x: ");
            scanf("%s", input);
            if (isHex(input)) {
                hexToBinary(input);
            } else {
                // treat input as binary
                binaryToHex(input);
            }
        } else {
            printf("Invalid choice. Please select 1 or 2.\n");
        }
    }
    return 0;
}

void printMenu() {
    printf("\n--- Conversion Menu ---\n");
    printf("1. Decimal to binary / Binary to decimal\n");
    printf("2. Hex to binary / Binary to hex\n");
    printf("Type 'exit' to quit\n");
}

void decimalToBinary(int decimal) {
    unsigned char magnitude;
    int sign = 0;
    if (decimal < 0) {
        sign = 1;
        magnitude = -decimal;
    } else {
        magnitude = decimal;
    }

    char binary[9];
    binary[8] = '\0';

    // Convert magnitude to binary
    for (int i = 7; i >= 0; i--) {
        binary[i] = (magnitude & 1) ? '1' : '0';
        magnitude >>= 1;
    }

    // Sign bit
    printf("Decimal %d as 8-bit signed magnitude binary: %c%s\n", decimal, (sign ? '1' : '0'), binary + 1);
}

int binaryToDecimal(const char *binStr) {
    int sign = 0;
    int value = 0;
    if (binStr[0] == '1') {
        sign = 1;
    }
    // Convert binary string (excluding sign bit) to decimal
    for (int i = 1; i < 8; i++) {
        value <<= 1;
        if (binStr[i] == '1') {
            value += 1;
        } else if (binStr[i] != '0') {
            printf("Invalid binary number.\n");
            return 0;
        }
    }
    if (sign) {
        value = -value;
    }
    return value;
}

void binaryToHex(const char *binStr) {
    // Convert binary string to decimal first
    int decimal = 0;
    int sign = 0;
    if (binStr[0] == '1') {
        sign = 1;
    }
    for (int i = 1; i < 8; i++) {
        decimal <<= 1;
        if (binStr[i] == '1') {
            decimal += 1;
        } else if (binStr[i] != '0') {
            printf("Invalid binary number.\n");
            return;
        }
    }
    if (sign) {
        decimal = -decimal;
    }
    printf("Binary %s is hexadecimal: 0x%X\n", binStr, decimal & 0xFF);
}

void hexToBinary(const char *hexStr) {
    unsigned int hexValue = 0;
    sscanf(hexStr, "%x", &hexValue);
    printf("Hexadecimal %s as 16-bit binary: ", hexStr);
    for (int i = 15; i >= 0; i--) {
        printf("%d", (hexValue >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

int isBinary(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }
    }
    return len == 8; // ensure 8 bits for signed magnitude
}

int isHex(const char *str) {
    return (strlen(str) > 2 && str[0] == '0' && str[1] == 'x');
}