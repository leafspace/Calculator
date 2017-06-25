#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
int main()
{
    int n=1;
    char symbol;
    char string[N]={0};
    float answer;
    printf("                                  calculator\n");
    printf("                                                                         by dack");
    printf("================================================================================\n");
    while(1)
    {
        printf("Please enter the %d formula : ",n++);
        gets(string);
        answer=handle(string);
        printf("Answer = %.2f .\n",answer);
        printf("Do you want calculate once again ? ");
        symbol=getchar();
        fflush(stdin);
        if(toupper(symbol)!='Y')
            break;
    }
}
