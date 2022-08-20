#include <cs50.h>
#include <stdio.h>

// Function prototype
void print_bricks(int height, int original_height);

int main(void)
{
    // Declares height
    int height;
    // Asks for height until it's between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    // Prints the bricks
    print_bricks(height, height);
    return 0;
}

void print_bricks(int height, int original_height)
{
    // If height is less than one then return (base case)
    if (height < 1)
    {
        return;
    }
    // Sets height - 1 as the height input and a constant original height until height is less than one
    print_bricks(height - 1, original_height);
    // Prints the spaces
    for (int i = 0; i < original_height - height; i++)
    {
        printf(" ");
    }
    // Prints the first set of bricks
    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    // Prints the space between the two set of bricks
    printf("  ");
    // Prints the second set of bricks
    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    printf("\n");
    return;
}