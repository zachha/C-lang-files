#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// declaring functions
void validateKey(string key);
void getMessage(void);
void encryptMessage(string message);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
    } else {
        validateKey(argv[1]);
        get_string("plaintext: ");
        printf("Success\nKey: %i\n", atoi(argv[1]));    
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
void getMessage(void) {
    string message = get_string("plaintext: ");
    messageLength = strlen(message);
    for (int x=0; x<messageLength; x++) {
        encryptMessage(message chars)
            // lowercase a = 097 uppercase A = 065
    }
}