#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

string substitution(string plain, string key);
string checker(string key);

int main(int argc, string argv[])
{
    string help = "Usage: ./substitution key [Key must contain only 26 unique alphabet characters.]\n";
    if (argc != 2)
    {
        printf("%s", help); //Arg test
        return 1;
    }
    string key = checker(argv[1]);
    if (strlen(key) != 26)
    {
        printf("%s", help); //Lengths
        return 1;
    }
    string plain = get_string("plaintext: ");
    string cipher = substitution(plain, key);
    printf("ciphertext: %s\n", cipher);
}

string checker(string key) //Checks for missing 
{
    char check[27];
    for (int x = 0; x < strlen(key); x++)
    {
        key[x] = toupper(key[x]);
        for (int y = 0; y < strlen(check); y++)
        {
            if ((check[y] == key[x]) || (key[x] - 65 < 0) || (key[x] - 65 > 26))
            {
                return "";
            }
        }
        check[x] = key[x];
    }
    return key;
}

string substitution(string plain, string key)
{
    for (int x = 0; x < strlen(plain); x++)
    {
        if (isupper(plain[x]))
        {
            plain[x] = toupper(key[(int)plain[x] - 65]);
        }
        else if (islower(plain[x]))
        {
            plain[x] = tolower(key[(int)plain[x] - 97]);
        }
        else
        {
            plain[x] = plain[x];
        }
    }
    return plain;
}