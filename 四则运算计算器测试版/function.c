#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
double handle(char *string)                       //总体处理部分
{
    char symbol;
    int error_number;
    double answer;
    //1.先进行错误判断，将错误的数量返回到error_number中
    error_number=error_detection(string);
    //2.如果有错误则这个式子不能执行，给出重新输入的处理
    if(error_number){
        printf("This equation have %d mistakes ! \n",error_number);
        printf("Do you want write this equation again ? ");
        fflush(stdin);
        symbol=getchar();
        fflush(stdin);
        //3.如果同意重新输入则继续按照上面的操作继续
        if(toupper(symbol)!='N'){
            gets(string);
            answer=handle(string);
        }
    }
    else{
        //4.如果没有错误则进行拆包计算
        answer=bracket(string);
    }
    return answer;
}
int error_detection(char *string)                //检测输入的式子是否符合规则
{
    int left_parenthesis=0,right_parenthesis=0;
    int error_number=0;
    int i;
    for(i=0;string[i];i++){
        //1.先寻找式子内是否存在异常字符
        if(!isdigit(string[i])&&!arithmetic_character(string[i])&& string[i]!='(' && string[i]!=')' && string[i]!='.'){
            printf("The %d character : Anomalous character ! \n",i+1);
            error_number++;
        }
        //2.判断小数点出现的位置正不正确
        if(string[i]=='.'&&(!isdigit(string[i-1])||!isdigit(string[i+1]))){
            printf("The %d character : Decimal point error display ! \n",i+1);
            error_number++;
        }
        //3.判断数学符号是不是连续重复出现
        if(arithmetic_character(string[i])&&arithmetic_character(string[i+1])){
            printf("The %d character : Arithmetic character repeated emergence ! \n",i+1);
            error_number++;
        }
        //4.左括号右边不能为数学符号
        if(string[i]=='('){
            left_parenthesis++;
            if(!string[i+1]&&(string[i+1]=='*'||string[i+1]=='/')){
                printf("The %d character : Character error after ! \n",i+1);
                error_number++;
            }
        }
        //5.右括号左边不能为数学符号
        if(string[i]==')'){
            right_parenthesis++;
            if(arithmetic_character(string[i-1])){
                printf("The %d character : Character error before ! \n",i+1);
                error_number++;
            }
        }
        //6.左括号任意时间都要大于等于右括号个数，但不彻底（判断的是多括号的情况）
        if(left_parenthesis<right_parenthesis){
            printf("The %d character : Parenthesis doesn't pairing ! \n",i+1);
            error_number++;
        }
    }
    //7.判断括号是否配对（判断的是少括号的情况）
    if(left_parenthesis!=right_parenthesis){
        printf("The %d character : A line of text is not over yet ! \n",i+1);
        error_number++;
    }
    return error_number;
}
double bracket(char *string)                      //检测括号并提取并替换的函数
{
    int First_bracket,Second_bracket;
    int i=0;
    char temp[N]={0};
    double temp_number,answer;
    //1.寻找串中第一个左括号的位置
    while(string[i]!='('&&string[i])
        i++;
    First_bracket=i;
    i=strlen(string)-1;
    //2.寻找串中最后一个右括号的位置
    while(string[i]!=')'&&i>=0)
        i--;
    Second_bracket=i;
    //3.如果左括号位置符合常理则进行抽取计算的操作
    if(First_bracket<strlen(string)){
        string[First_bracket]=0;
        string[Second_bracket]=0;
        strcpy(temp,&string[First_bracket+1]);
        //4.计算出括号内式子的数值
        temp_number=bracket(temp);
        //5.提取出括号内部的所有内容，并用计算完毕的数值进行写入
        strcpy(temp,&string[Second_bracket+1]);
        sprintf(&string[First_bracket],"%lf",temp_number);
        strcat(string,temp);
    }
    //6.此时式子内无括号，进行纯乘除法计算
    muliply_divide(string);
    //7.此时式子内无乘除法，进行纯加减法计算
    answer=add_subtract(string);
    return answer;
}
void muliply_divide(char *string)                //提供加减乘除的式子并将乘除法的结果算出替换
{
    int i;
    for(i=0;string[i];i++){
        if(string[i]=='*'||string[i]=='/'){
            double front_number,behind_number,answer;
            int First_location,Second_location;
            char temp[N]={0};
            First_location=i-1;
            Second_location=i+1;
            //1.计算符号前面的一个数的数值
            front_number=front_n(&First_location,string);
            //2.计算符号后面的一个数的数值
            behind_number=behind_n(&Second_location,string);
            First_location++;
            Second_location--;
            //3.附加的错误判断。因为在总错误检测内无法实现，所以在此检测，除数不为0的判断
            if(string[i]=='/' && behind_number==0){
                printf("%s In this formula , the divisor cannot be zero !\n",string);
                printf("Program will over !\n");
                exit(-1);
            }
            //4.对计算出来的数进行该有的处理
            switch(string[i])
            {
                case '*' : answer = front_number * behind_number; break;
                case '/' : answer = front_number / behind_number; break;
                //理论上没有这一项
                default  : exit(-1);
            }
            //5.用计算出来的结果替换原来计算的部分
            strcpy(temp,&string[Second_location+1]);
            sprintf(&string[First_location],"%lf",answer);
            strcat(string,temp);
        }
    }
}
double add_subtract(char *string)                 //提供纯加减法的式子并将结果直接返回
{
    int i,f=1;
    double answer=0;
    char temp[N]={0};
    //1.如果说第一个是数字的话那么就说明这是个正常的式子，增加一个加号表示第一个数为正数
    if(isdigit(string[0])){
        temp[0]='+';
        strcat(temp,string);
        strcpy(string,temp);
    }
    //2.如果第一个是符号，特殊情况，在这里就有体现，将这里每一个数都看为是符号后数
    for(i=0;string[i];i++){
        if(arithmetic_character(string[i])){
            double t;
            int j=i+1;
            t=behind_n(&j,string);
            answer+=string[i]=='+'?t:-t;
            if(string[i+1]&&arithmetic_character(string[i+1]))
                i++;
        }
    }
    return answer;
}
int arithmetic_character(char c)                 //判断提供的字符是否为算术符号
{
    if(c!='+'&&c!='-'&&c!='*'&&c!='/')
        return 0;
    else
        return 1;
}
double front_n(int *First_location,char *string)  //用来求符号前面一个数，可以是小数
{
    int j;
    double answer;
    //1.移动位置到此数的第一个位置
    while((isdigit(string[*First_location])||string[*First_location]=='.')&&(*First_location)>=0){
        (*First_location)--;
    }
    if((*First_location)>0&&(string[(*First_location)-1]=='+'||string[(*First_location)-1]=='-')){
        j=(*First_location);
        (*First_location)--;
    }
    else
        j=(*First_location)+1;
    //2.将其化为是求符号后一个数
    answer=behind_n(&j,string);
    return answer;
}
double behind_n(int *Second_location,char *string)//用来求符号后面一个数，可以是小数
{
    int flag=0,n=1,f=1;
    double answer=0;
    if(string[*Second_location]=='+'||string[*Second_location]=='-'){
        f=(string[*Second_location]=='+')?1:-1;
        (*Second_location)++;
    }
    //1.保证滤过的都是数字或者是小数点
    while(string[*Second_location]&&(isdigit(string[*Second_location])||string[*Second_location]=='.')){
        if(string[*Second_location]=='.'){
            (*Second_location)++;
            flag=1;
            continue;
        }
        if(!flag)
            answer=answer*10+string[*Second_location]-'0';
        else{
            answer=answer+(string[*Second_location]-'0')/pow(10,n);
            n++;
        }
        (*Second_location)++;
    }
    return f*answer;
}
