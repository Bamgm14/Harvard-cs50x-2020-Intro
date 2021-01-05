#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int grader(string para);

int main(void)
{
    string para = get_string("Enter Your Sentence:"); //Accepts String
    int grade = grader(para);
//    printf("%d\n", grade); //Debugger
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %d\n", grade);
        return 0;
    }
}

int grader(string para) //Grades your English SKILLZ
{
    float word_count = 1; //Dual Purpose 1) Stops 0 Division 2) Counting ' ' is word_count - 1
    float sentence_count = 0;
    float letter_count = 0;

    for (int x = 0; x < strlen(para); x++)
    {
        if (para[x] == ' ') //Counts Words
        {
            word_count += 1;
        }
        if ((para[x] == '!') || (para[x] == '?') || (para[x] == '.')) //Checks for sentence end
        {
            sentence_count += 1;
        }
        if (isalpha(para[x])) //Checks if letter
        {
            letter_count += 1;
        }
    }
    int grade = round((0.0588 * (letter_count / word_count) - 0.296 * (sentence_count / word_count)) * 100 - 15.8);
    return grade;
}