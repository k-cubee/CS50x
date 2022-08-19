#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // asks user for their name
    string name = get_string("Enter your name: ");
    // prints hello + the user's name
    printf("hello, %s\n", name);
}