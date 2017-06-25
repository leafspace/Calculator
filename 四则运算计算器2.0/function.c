#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
float handle(char *string)
{
    char symbol;
    int error_number;
    float answer;
    error_number=error_detection(string);
    if(error_number){
        printf("This equation have %d mistakes ! \n",error_number);
        printf("Do you want write this equation again ? ");
        fflush(stdin);
        symbol=getchar();
        fflush(stdin);
        if(toupper(symbol)!='N'){
            gets(string);
            answer=handle(string);
        }
    }
    else{
        answer=bracket(string);
    }
    return answer;
}
int error_detection(char *string)
{
    int left_parenthesis=0,right_parenthesis=0;
    int error_number=0;
    int i;
    for(i=0;string[i];i++){
        if(!isdigit(string[i])&&!arithmetic_character(string[i])&& string[i]!='(' && string[i]!=')' && string[i]!='.'){
            printf("The %d character : Anomalous character ! \n",i+1);
            error_number++;
        }
        if(string[i]=='.'&&(!isdigit(string[i-1])||!isdigit(string[i+1]))){
            printf("The %d character : Decimal point error display ! \n",i+1);
            error_number++;
        }
        if(arithmetic_character(string[i])&&arithmetic_character(string[i+1])){
            printf("The %d character : Arithmetic character repeated emergence ! \n",i+1);
            error_number++;
        }
        if(string[i]=='('){
            left_parenthesis++;
            if(!string[i+1]||arithmetic_character(string[i+1])){
                printf("The %d character : Character error after ! \n",i+1);
                error_number++;
            }
        }
        if(string[i]==')'){
            right_parenthesis++;
            if(arithmetic_character(string[i-1])){
                printf("The %d character : Character error before ! \n",i+1);
                error_number++;
            }
        }
        if(left_parenthesis<right_parenthesis){
            printf("The %d character : Parenthesis doesn't pairing ! \n",i+1);
            error_number++;
        }
    }
    if(left_parenthesis!=right_parenthesis){
        printf("The %d character : A line of text is not over yet ! \n",i+1);
        error_number++;
    }
    return error_number;
}
float bracket(char *string)
{
    int First_bracket,Second_bracket;
    int i=0;
    char temp[N]={0};
    float temp_number,answer;
    while(string[i]!='('&&string[i])
        i++;
    First_bracket=i;
    i=strlen(string)-1;
    while(string[i]!=')'&&i>=0)
        i--;
    Second_bracket=i;
    if(First_bracket<strlen(string)){
        string[First_bracket]=0;
        string[Second_bracket]=0;
        strcpy(temp,&string[First_bracket+1]);
        temp_number=bracket(temp);
        strcpy(temp,&string[Second_bracket+1]);
        sprintf(&string[First_bracket],"%f",temp_number);
        strcat(string,temp);
    }
    muliply_divide(string);
    answer=add_subtract(string);
    return answer;
}
void muliply_divide(char *string)
{
    int i;
    for(i=0;string[i];i++){
        if(string[i]=='*'||string[i]=='/'){
            float front_number,behind_number,answer;
            int First_location,Second_location;
            char temp[N]={0};
            First_location=i-1;
            Second_location=i+1;
            front_number=front_n(&First_location,string);
            behind_number=behind_n(&Second_location,string);
            First_location++;
            Second_location--;
            if(string[i]=='/' && behind_number==0){
                printf("%s In this formula , the divisor cannot be zero !\n",string);
                printf("Program will over !\n");
                exit(-1);
            }
            switch(string[i])
            {
                case '*' : answer = front_number * behind_number; break;
                case '/' : answer = front_number / behind_number; break;
                default  : exit(-1);
            }
            strcpy(temp,&string[Second_location+1]);
            sprintf(&string[First_location],"%f",answer);
            strcat(string,temp);
        }
    }
}
float add_subtract(char *string)
{
    int i,f=1;
    float answer=0;
    if(isdigit(string[0])){
        int j;
        j=0;
        answer=behind_n(&j,string);
    }
    for(i=0;string[i];i++){
        if(arithmetic_character(string[i])){
            int j;
            float temp;
            j=i+1;
            temp=behind_n(&j,string);
            if(string[i]=='+')
                answer=answer+temp;
            else
                answer=answer-temp;
        }
    }
    return answer;
}
int arithmetic_character(char c)
{
    if(c!='+'&&c!='-'&&c!='*'&&c!='/')
        return 0;
    else
        return 1;
}
float front_n(int *First_location,char *string)
{
    int j;
    float answer;
    while((isdigit(string[*First_location])||string[*First_location]=='.')&&(*First_location)>=0){
        (*First_location)--;
    }
    j=(*First_location)+1;
    answer=behind_n(&j,string);
    return answer;
}
float behind_n(int *Second_location,char *string)
{
    int flag=0,n=-1;
    float answer=0;
    while(string[*Second_location]&&(isdigit(string[*Second_location])||string[*Second_location]=='.')){
        if(string[*Second_location]=='.'){
            (*Second_location)++;
            flag=1;
            continue;
        }
        if(!flag)
            answer=answer*10+string[*Second_location]-'0';
        else{
            answer=answer+(string[*Second_location]-'0')*pow(10,n);
            n--;
        }
        (*Second_location)++;
    }
    return answer;
}
