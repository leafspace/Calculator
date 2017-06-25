#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
float handle(char *string)         //总体处理部分
{
    char symbol;
    int error_number;
    float answer;
    error_number=error_detection(string);
    if(error_number){
        printf("This equation have %d mistakes ! \n",error_number);
        printf("Do you want write this equation again ? \n");
        symbol=getchar();
        fflush(stdin);
        if(toupper(symbol)!='N'){
            fgets(string,80,stdin);
            answer=handle(string);
        }
    }
    else{
        answer=bracket(string);
    }
    return answer;
}
int error_detection(char *string)  //检测输入的式子是否符合规则
{
    int left_parenthesis=0,right_parenthesis=0;
    int error_number=0;
    int i;
    for(i=0;string[i];i++){
        if(!isdigit(string[i])&&!arithmetic_character(string[i])&& string[i]!='(' && string[i]!=')' ){
            printf("The %d character : Anomalous character ! \n",i+1);
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
        if(arithmetic_character(string[i])&&arithmetic_character(string[i+1])){
            printf("The %d character : Arithmetic character repeated emergence ! \n",i+1);
            error_number++;
        }
    }
    if(left_parenthesis!=right_parenthesis){
        printf("The %d character : A line of text is not over yet ! \n",i+1);
        error_number++;
    }
    return error_number;
}
float bracket(char *string)         //检测括号并提取并替换的函数
{
    int First_bracket,Second_bracket;
    int i=0;
    char temp[N]={0};
    float temp_number,answer;
    // 寻找第一个和最后一个括号，因为这两个括号配对
    while(string[i]!='('&&string[i])
        i++;
    First_bracket=i;
    i=strlen(string)-1;
    while(string[i]!=')'&&i>=0)
        i--;
    Second_bracket=i;
    //将括号内的内容复制到一个数组里面进行去括号的处理
    if(First_bracket<strlen(string)){
        string[First_bracket]=0;
        string[Second_bracket]=0;
        strcpy(temp,&string[First_bracket+1]);
        temp_number=bracket(temp);
        //此时temp_number为括号内的数值；
        //下面对刚刚括号内的内容进行替换，替换为temp number的字符数值；
        strcpy(temp,&string[Second_bracket+1]);
        sprintf(&string[First_bracket],"%.0f",temp_number);
        strcat(string,temp);
    }
    //此时出来的结果为加减乘除混合运算，但是已经消除了括号了
    muliply_divide(string);
    //此时出来的string为纯加减法的，将其放入add subtract中计算数值；
    answer=add_subtract(string);
    return answer;
}
void muliply_divide(char *string)  //提供加减乘除的式子并将乘除法的结果算出替换
{
    int i;
    for(i=0;string[i];i++){
        if(string[i]=='*'||string[i]=='/'){
            //分别向前找和向后找找到运算的两个数
            float front_number=0,behind_number=0,answer;
            int First_location,Second_location;
            char temp[N]={0};
            First_location=i-1;
            Second_location=i+1;
            while(First_location>=0&&isdigit(string[First_location])){
                front_number=front_number+(string[First_location]-'0')*pow(10,i-First_location-1);
                First_location--;
            }
            while(Second_location<strlen(string)&&isdigit(string[Second_location])){
                behind_number=behind_number*10+string[Second_location]-'0';
                Second_location++;
            }
            First_location++;
            Second_location--;
            switch(string[i])
            {
                case '*' : answer = front_number * behind_number; break;
                case '/' : answer = front_number / behind_number; break;
                //理论上不会出现这种情况
                default  : exit(-1);
            }
            strcpy(temp,&string[Second_location+1]);
            sprintf(&string[First_location],"%.0f",answer);
            strcat(string,temp);
        }
    }
}
float add_subtract(char *string)   //提供纯加减法的式子并将结果直接返回
{
    int f=1;
    float mx=0,sum=0;
    while(*string){
        if(isdigit(*string))
            mx=mx*10+*string-'0';
        else
            {
                sum=sum+f*mx;
                mx=0;
                if(*string=='-')
                    f=-1;
                else
                    f=1;
            }
        if(*(string+1)==0)
            sum=sum+f*mx;
        string++;
    }
    return sum;
}
int arithmetic_character(char c)   //判断提供的字符是否为算术符号
{
    if(c!='+'&&c!='-'&&c!='*'&&c!='/')
        return 0;
    else
        return 1;
}
