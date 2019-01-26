#include <cs50.h>
#include <stdio.h>

void build(int n); // declares the build function
void align(int m); // declares the align function
    
int main(void)
{
    int height = get_int("Please enter a height from 1-8 for the pyramid: \n");
    // validates input to make sure it is from 1-8
    if(height < 1 || height > 8)
    {
        height = get_int("Error! Please enter a height greater than 0 and less than 8: \n");
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

// build function figures out how many hashtags are needed to build each level
void build(int n) 
{
    for( int x=0; x < n+1; x++)
    {
        printf("#");
    }
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