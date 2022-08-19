#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // asks for height until it's an int and is 0 < h < 9
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 0; i < height; i++)
    {
        // prints the spaces
        for (int j = 0; j < height - (i + 1); j++)
        {
            printf(" ");
        }
        // prints the first block
        for (int k = 0, length = i + 1; k < length; k++)
        {
            printf("#");
        }
        //  prints the space in between the two blocks
        printf("  ");
        // prints the second block
        for (int l = 0, length = i + 1; l < length; l++)
        {
            printf("#");
        }
        // prints a line break
        printf("\n");
    }
}