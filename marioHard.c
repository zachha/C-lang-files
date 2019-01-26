#include <cs50.h>
#include <stdio.h>

// declares my functions 
void build(int n); 
void align(int m); 
void hashtags(int o);
    
int main(void)
{
    int height = get_int("Please enter a height from 1-10 for the pyramid: \n");
    // validates input to make sure it is from 1-10
    while(height < 1 || height > 10)
    {
        height = get_int("Error! Please enter a height greater than 0 and less than 11: \n");
    }
    printf("\nHeight: %i\n\n", height);
    
    // loops through the height and the build function builds each level then stops
    for( int i=0; i < height; i++) 
    {
        align(height-(i+1));
        build(i); 
    }
    printf("\n");
}

// build function builds the pyramid after it is aligned with spaces using the hashtag function
void build(int n) 
{
    hashtags(n);
    hashtags(n);
    printf("\n"); // starts a new line after so the next level can be built if there is one
}

// align function figures out how many spaces are needed to right align each level
void align(int m)
{
    for(int y=0; y < m; y++)
    {
        printf(" ");
    }
}

// hashtag function creates the hashtag layers of each level
void hashtags(int o)
{
    for( int x=0; x < o+1; x++)
    {
        printf("#");
    }
    printf("  ");
}