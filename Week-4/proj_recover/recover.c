#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if ((argc > 2) || (argc == 1))
    {
        printf("./recover card.raw");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("File is not openable. Please give more permissions to code"); //Check if files are openable
        return 1;
    }
    int count = 0;
    char name[128];
    uint8_t bytes[512];// Stores bytes
    FILE *f1 = fopen("000.jpg", "w"); //Opens file to make sure error happen
    while (fread(bytes, sizeof(uint8_t), 512, f))
    {
        if ((bytes[0] == 0xff) && (bytes[1] == 0xd8) && (bytes[2] == 0xff) && ((bytes[3] & 0xf0) == 0xe0)) //Looking for beats
        {
            fclose(f1);
            sprintf(name, "%03i.jpg", count); //Naming
            f1 = fopen(name, "w");
            if (f1 == NULL)
            {
                printf("File is not openable. Please give more permissions to code"); //Check if files are openable
                return 1;
            }
            count++;
        }
        if (count != 0)
        {
            fwrite(bytes, sizeof(uint8_t), 512, f1);//Writing
        }
    }
    fclose(f1);
    return 0;
}
