#include <stdio.h>
#include <unistd.h>
#include <cs50.h>
#include <math.h>
int money(int cash);

int main(void) //Main Function to Run
{
    float cash = 0.0;
    do
    {
        cash = get_float("Please Enter Cash to be converted:"); //Asks for money required
    }
    while (cash <= 0.0);
    int coins = money(round(cash * 100));
    printf("%d\n", coins); //Prints the answer
}
//Seperate Counting Function
int money(int cash)
{
    int regi[] = {25, 10, 5, 1};
    int coins = 0;
    for (int x = 0; x < 4; x++) //Goes through list
    {
        for (int y = 0; cash >= regi[x]; y++) //Checks money and counts
        {
            coins += 1;
//            printf("Coins:%d\n", coins); //Debugger
//            printf("Cash:%d\n", cash); //Debugger
            cash -= regi[x];
//            sleep(3); //Debugger
        }
//        printf("%d\n", x); //Debugger
//        printf("Dimes:%d\n", regi[x]); //Debugger
//        printf("Cash:%d\n", cash); //Debugger
    }
//    printf("Coins:%d\n", coins); //Debugger
//    printf("Cash:%d\n", cash); //Debugger
    return coins; //Truns money
}