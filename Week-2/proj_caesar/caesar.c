#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

string caeser(string plain, int key);
int strtoint(string number);

int main(int argc, string argv[])
{
//    printf("%d\n", key); //Debugger
    if (argc != 2)
    {
        printf("Usage: ./caesar key [Must Be Whole Number]\n"); //Arg test
        return 1;
    }
    int key = strtoint(argv[1]); 
//    printf("%i\n",key); //Debugger
    if (key < 0)
    {
        printf("Usage: ./caesar key [Must Be Whole Number]\n"); //Key test
        return 1;
    }
    string plain = get_string("plaintext: ");
    string cipher = caeser(plain, key);
    printf("ciphertext: %s\n", cipher);
}

int strtoint(string number) //Converts str to int
{
    int key = 0;
    int check;
//    printf("%s\n", number); //Debugger
//    printf("%lu\n", strlen(number)); //Debugger
    for (int x = strlen(number) - 1; x >= 0; x--)
    {
        check = number[x] - '0';
//        printf("%i\n", x); //Debugger
        if (check < 0 || check > 9)
        {
            return -1;
        }
        check *= pow(10, strlen(number) - x - 1);
        key += check;
    }
    return key;
}

string caeser(string plain, int key) //Converts to Cipher
{
    int check;
    for (int x = 0; x < strlen(plain); x++)
    {
        if (isalpha(plain[x]))
        {
//            printf("%c\n", plain[x]); //Debugger
            if (isupper(plain[x])) 
            {
                check = 65;
            }
            else
            {
                check = 97;
            }
            plain[x] = ((plain[x] - check + key) % 26) + check; //Adding
//            printf("%i\n", check + key); //Debugger
        }
    }
//    printf("%s\n", plain); //Debugger
    return plain;
}