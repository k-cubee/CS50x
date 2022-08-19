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
    int i = -1;
    int found_jpg = -1;
    char file_name[8];
    FILE *output;
    while (fread(block, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Closes the file when new signatures are found
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] >= 0xe0 && block[3] <= 0xef) && i >= 0)
        {
            fclose(output);
        }
        // Looks for JPEG signatures
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] >= 0xe0 && block[3] <= 0xef))
        {
            i++;
            // If they are found, gets the filename, opens the file and starts writing inside the file
            if (i < 10)
            {
                sprintf(file_name, "00%i.jpg", i);
            }
            else if (i >= 10 && i < 100)
            {
                sprintf(file_name, "0%i.jpg", i);
            }
            output = fopen(file_name, "w");
            if (output == NULL)
            {
                return 1;
            }
            fwrite(block, 1, BLOCK_SIZE, output);
        }
        // If no signature is found, but one has already been found, then write into the file
        else if (i >= 0)
        {
            fwrite(block, 1, BLOCK_SIZE, output);
        }
    }
    // Closes the final output
    fclose(output);
    // Closes the card after everything is done
    fclose(card);
    return 0;
}