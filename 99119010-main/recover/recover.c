#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
int main(int argc, char *argv[])
{
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    uint8_t block[BLOCK_SIZE];
    while (fread(block, sizeof(uint8_t), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        int i = 0;
        char file_name[100];
        if (i < 10)
        {
            sprintf(file_name, "00%i.jpg", i);
        }
        else if (i > 10 && i < 100)
        {
            sprintf(file_name, "0%i.jpg", i);
        }
        FILE *output = fopen(file_name, "w");
        if (output == NULL)
        {
            return 1;
        }
        do
        {
            fwrite(block, sizeof(uint8_t), BLOCK_SIZE, output);
        }
        while (block[0] != 0xff && block[1] != 0xd8 && block[2] != 0xff);
        i++;
        fclose(output);
    }
    fclose(card);
    return 0;
}