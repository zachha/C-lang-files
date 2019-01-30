#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// declaring functions
void validateKeyword(string keyword);
string getShiftValues(string rawKeyword);
void getMessage(string validKeyword);
int relateShiftValues(string validKeyword, string message, int x);
void encryptMessage(int length, string message, string validKeyword);
int convertLowercase(int encryptedLetter);
int convertUppercase(int encryptedLetter);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./vigenere keyword\n");
    } else {
        validateKeyword(argv[1]);
        string validKeyword = getShiftValues(argv[1]);
        getMessage(validKeyword);   
    }
}

// validates the key input by user by checking every char to make sure its a digit from 0-9 
void validateKeyword(string keyword) {
    int length = strlen(keyword);
        for (int i=0; i<length; i++) {
            if (!isalpha(keyword[i])) {
                printf("Usage: ./vigenere keyword\n");
                exit(0);
            }
        }
}

// converts each char in the user's keyword to the value that it will shift the plaintext to encrypt it into ciphertext 
string getShiftValues(string rawKeyword) {
    int rawLength = strlen(rawKeyword);
    string validKeyword = rawKeyword;
    for(int o=0; o<rawLength; o++) {
        if(islower(validKeyword[o])) {
            // these values are one int MORE than they should be because if a is 0, it isn't counted as a value in the string array and can mess up later functions, so 1 will be subtracted in the encryptMessage function to revert it to the 'real' shift value
            validKeyword[o] -= 96;
        } else {
            validKeyword[o] -= 64;
        }
    }
    return validKeyword;
}

// Asks the user for input then 'encrypts' the message by adding the key to the ASCII value and prints it back out to user as a string
void getMessage(string validKeyword) {
    string message = get_string("plaintext: ");
    int messageLength = strlen(message);
    encryptMessage(messageLength, message, validKeyword);
}

// this should relate every char in the plain text to it's appropriate char in the keyword
int relateShiftValues(string validKeyword, string message, int x) {
    int keywordLength = strlen(validKeyword);
    if (keywordLength > 1) {
        int keywordIndex = x % strlen(validKeyword);
        return keywordIndex;
    } else {
        int keywordIndex = 0;
        return keywordIndex;
    }
}
 
    
void encryptMessage(int length, string message, string validKeyword) {
    // counter keeps track of the alphabetic message chars to make sure the keyword continues to shift in order through the message even if the message has spaces or non alphabetic characters
    int counter = 0;
    for (int x=0; x<length; x++) {
        char letter = message[x];
        // checks each char to make sure it's alphabetic before converting it
        if(isalpha(letter)) {
            int letterRelation = relateShiftValues(validKeyword, message, counter);
            // 1 is subtracted from each char in validKeyword b/c 1 was added in the getShiftValues function
            int encryptedLetter = ((int) letter) + (validKeyword[letterRelation] - 1);
            counter ++;
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
// these two functions start over from 'a' in the alphabet if the ascii number goes past 'z'
int convertLowercase(int encryptedLetter) {
    if(encryptedLetter > 122) {
        encryptedLetter = 96 + (encryptedLetter - 122);
        return encryptedLetter;
    } else {
        return encryptedLetter;
    }
}

int convertUppercase(int encryptedLetter) {
    if(encryptedLetter > 90) {
        encryptedLetter = 64 + (encryptedLetter - 90);
        return encryptedLetter;
    } else {
        return encryptedLetter;
    }
}
