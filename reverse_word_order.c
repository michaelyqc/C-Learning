/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>


void reverse_word_order(char* start, char* end)
{
    if (*start == '\0') {
        return;
    } else if (*start == ' ') {
        char* str = start;
        char tmp;
        
        // CONTINUE SPACE 
        do {
            ++start;
        } while (*start == ' ' && start != end);
        
        // recursive
        reverse_word_order(start, end);
        
        tmp = *start;
        *start = '\0';
        printf("%s", str);
        *start = tmp;
        
    } else {
        char* str = start;
        char tmp;
        
        // CONTINUE SPACE 
        do {
            ++start;
        } while ( *start != ' ' && *start != '\0' && start != end);
        
        // recursive
        reverse_word_order(start, end);
        
        tmp = *start;
        *start = '\0';
        printf("%s", str);
        *start = tmp;
    }
    
    return;
}

int main()
{
    const int MAX_LENGTH = 101;
    
    char input[MAX_LENGTH];
    
    // GET INPUT
    gets(input);
    
    int input_length = strlen(input);
    
    // REVERSE 
    reverse_word_order(input, input +input_length);

    return 0;
}
