// C program to ReverseSentence a string
#include <stdio.h>

// Algorithm:
// Initially, reverse the individual words of the given string one by one, 
// for example, after reversing individual words in the string 
// "I love science very much", 
// the string should be 
// “I evol ecneics yrev hcum”.
// Reverse the whole string from start to end to get the desired output “much very science this love I”.

// This function reverses any sequence starting with pointer begin and ending with pointer end
void ReverseSequence(char* begin, char* end)
{
    char temp;

    while (begin < end)
    {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

// This function reverses words in a character string
void ReverseWords(char* s)
{
    char* word_begin = s;
    char* word_end = s;

    // Reverse individual words
    while (*word_end)
    {
        word_end++;
        if (*word_end == '\0')
        {
            ReverseSequence(word_begin, word_end - 1);
        }
        else if (*word_end == ' ')
        {
            ReverseSequence(word_begin, word_end - 1);
            word_begin = word_end + 1;
        }
    }

    // Reverse the entire string
    ReverseSequence(s, word_end - 1);
}

int main()
{
    char s[] = "I love science very much\0";
    char* temp = s;
    printf("%s\n", s);
    ReverseWords(s);
    printf("%s", s);
    return 0;
}