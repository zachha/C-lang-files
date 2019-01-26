#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// declaring functions
void validateKey(string key);
void getMessage(int validKey);
void encryptMessage(int length, string message, int validKey);
int convertLowercase(int encryptedLetter);
int convertUppercase(int encryptedLetter);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
    } else {
        validateKey(argv[1]);
        int validKey = atoi(argv[1]);
        getMessage(validKey);
        //printf("Success\nKey: %i\n", atoi(argv[1]));    
    }
}

// validates the key input by user by checking every char to make sure its a digit from 0-9 
void validateKey(string key) {
    int length = strlen(key);
        for (int i=0; i<length; i++) {
            // printf("%i\n", (int) argv[1][i])
            if (!isdigit(key[i])) {
                printf("Usage: ./caesar key\n");
                exit(0);
            }
        }
}

// Asks the user for input then 'encrypts' the message by adding the key to the ASCII value and prints it back out to user as a string
void getMessage(int validKey) {
    string message = get_string("plaintext: ");
    int messageLength = strlen(message);
    printf("ciphertext: %s\n", message);
    encryptMessage(messageLength, message, validKey);
}

void encryptMessage(int length, string message, int validKey) {
    for (int x=0; x<length; x++) {
        char letter = message[x];
        // checks each char to make sure it's alphabetic before converting it
        if(isalpha(letter)) {
            int encryptedLetter = ((int) letter) + validKey;
            printf("%i\n", encryptedLetter);
            if(islower(letter)) {
                convertLowercase(encryptedLetter);
            } else {
                convertUppercase(encryptedLetter);
            }
            printf("Encrypted letter: %c\n", (char) encryptedLetter);
        }    
        //encryptMessage(message chars)
        // lowercase a = 097 z = 122 uppercase A = 065 Z = 090
    }
}

int convertLowercase(int encryptedLetter) {
    if(encryptedLetter > 122) {
        encryptedLetter = 96 + (encryptedLetter - 122);
        printf("checking: %i\n", encryptedLetter);
        return encryptedLetter;
    } else {
        return encryptedLetter;
    }
}

int convertUppercase(int encryptedLetter) {
    if(encryptedLetter > 90) {
        encryptedLetter = 64 + (encryptedLetter - 90);
        printf("checking: %i\n", encryptedLetter);
        return encryptedLetter;
    } else {
        return encryptedLetter;
    }
}
