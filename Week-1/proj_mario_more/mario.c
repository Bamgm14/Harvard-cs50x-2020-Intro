#include <stdio.h>
#include <cs50.h>
//Calling so that complier doesn't lose itself
void builder(int num);

int main(void) //Main function to gather input
{
    int height = 0;
    do
    {
        height = get_int("Enter the Height between 1 to 8:"); //Input Function
    }
    while ((height < 1) || (height > 8));
    builder(height);
}
void builder(int num) //The Function that makes the Tower
{
    for (int x = 0; x < num; x++) //Layer Builder
    {
        for (int y = 0; y < num - 1 - x; y++) //Space Builder
        {
            printf(" ");
        }
        for (int y = 0; y <= x; y++) //Hash Builder
        {
            printf("#");
        }
        printf("  ");
        for (int y = 0; y <= x; y++) //Hash Builder
        {
            printf("#");
        }
        printf("\n"); //New Line
    }
}