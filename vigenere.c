#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// declaring functions
void validateKey(string key);
int modKey(int rawKey);
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
        int validKey = modKey(atoi(argv[1]));
        getMessage(validKey);   
    }
}

// validates the key input by user by checking every char to make sure its a digit from 0-9 
void validateKey(string key) {
    int length = strlen(key);
        for (int i=0; i<length; i++) {
            if (!isdigit(key[i])) {
                printf("Usage: ./caesar key\n");
                exit(0);
            } 
        }
}

// since there are 26 letters in the alphabet, if user inputs a key over 25 (26 would just give the same string back) we find the mod and make that remainder the new key. 
int modKey(int rawKey) {
    if(rawKey > 25) {
        return rawKey %= 25;
    } else {
        return rawKey;
    }
}

// Asks the user for input then 'encrypts' the message by adding the key to the ASCII value and prints it back out to user as a string
void getMessage(int validKey) {
    string message = get_string("plaintext: ");
    int messageLength = strlen(message);
    encryptMessage(messageLength, message, validKey);
}

void encryptMessage(int length, string message, int validKey) {
    for (int x=0; x<length; x++) {
        char letter = message[x];
        // checks each char to make sure it's alphabetic before converting it
        if(isalpha(letter)) {
            int encryptedLetter = ((int) letter) + validKey;
            if(islower(letter)) {
                message[x] = convertLowercase(encryptedLetter);
            } else {
                message[x] = convertUppercase(encryptedLetter);
            }
        }    
    }
    printf("ciphertext: %s\n", message);
}

// ASCII:  lowercase a = 097 z = 122 uppercase A = 065 Z = 090
// these two functions start from a in the alphabet if the ascii number goes past z
int convertLowercase(int encryptedLetter) {
    if(encryptedLetter > 122) {
        encryptedLetter = 96 + (encryptedLetter - 122);
        //printf("checking: %i %c\n", encryptedLetter, encryptedLetter);
        return encryptedLetter;
    } else {
        return encryptedLetter;
    }
}

int convertUppercase(int encryptedLetter) {
    if(encryptedLetter > 90) {
        encryptedLetter = 64 + (encryptedLetter - 90);
        //printf("checking: %i %c\n", encryptedLetter, encryptedLetter);
        return encryptedLetter;
    } else {
        return encryptedLetter;
    }
}
