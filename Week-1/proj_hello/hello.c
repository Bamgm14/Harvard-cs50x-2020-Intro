#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Basic Hello <name> code
    //Hopefully this is right
    //I would also have prefer to use native commands like scanf and fgets
    string name = get_string("What is your name?\n");
    printf("Hello %s!\n", name);
}