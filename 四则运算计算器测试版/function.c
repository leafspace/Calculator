#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
double handle(char *string)                       //���崦����
{
    char symbol;
    int error_number;
    double answer;
    //1.�Ƚ��д����жϣ���������������ص�error_number��
    error_number=error_detection(string);
    //2.����д��������ʽ�Ӳ���ִ�У�������������Ĵ���
    if(error_number){
        printf("This equation have %d mistakes ! \n",error_number);
        printf("Do you want write this equation again ? ");
        fflush(stdin);
        symbol=getchar();
        fflush(stdin);
        //3.���ͬ�����������������������Ĳ�������
        if(toupper(symbol)!='N'){
            gets(string);
            answer=handle(string);
        }
    }
    else{
        //4.���û�д�������в������
        answer=bracket(string);
    }
    return answer;
}
int error_detection(char *string)                //��������ʽ���Ƿ���Ϲ���
{
    int left_parenthesis=0,right_parenthesis=0;
    int error_number=0;
    int i;
    for(i=0;string[i];i++){
        //1.��Ѱ��ʽ�����Ƿ�����쳣�ַ�
        if(!isdigit(string[i])&&!arithmetic_character(string[i])&& string[i]!='(' && string[i]!=')' && string[i]!='.'){
            printf("The %d character : Anomalous character ! \n",i+1);
            error_number++;
        }
        //2.�ж�С������ֵ�λ��������ȷ
        if(string[i]=='.'&&(!isdigit(string[i-1])||!isdigit(string[i+1]))){
            printf("The %d character : Decimal point error display ! \n",i+1);
            error_number++;
        }
        //3.�ж���ѧ�����ǲ��������ظ�����
        if(arithmetic_character(string[i])&&arithmetic_character(string[i+1])){
            printf("The %d character : Arithmetic character repeated emergence ! \n",i+1);
            error_number++;
        }
        //4.�������ұ߲���Ϊ��ѧ����
        if(string[i]=='('){
            left_parenthesis++;
            if(!string[i+1]&&(string[i+1]=='*'||string[i+1]=='/')){
                printf("The %d character : Character error after ! \n",i+1);
                error_number++;
            }
        }
        //5.��������߲���Ϊ��ѧ����
        if(string[i]==')'){
            right_parenthesis++;
            if(arithmetic_character(string[i-1])){
                printf("The %d character : Character error before ! \n",i+1);
                error_number++;
            }
        }
        //6.����������ʱ�䶼Ҫ���ڵ��������Ÿ������������ף��жϵ��Ƕ����ŵ������
        if(left_parenthesis<right_parenthesis){
            printf("The %d character : Parenthesis doesn't pairing ! \n",i+1);
            error_number++;
        }
    }
    //7.�ж������Ƿ���ԣ��жϵ��������ŵ������
    if(left_parenthesis!=right_parenthesis){
        printf("The %d character : A line of text is not over yet ! \n",i+1);
        error_number++;
    }
    return error_number;
}
double bracket(char *string)                      //������Ų���ȡ���滻�ĺ���
{
    int First_bracket,Second_bracket;
    int i=0;
    char temp[N]={0};
    double temp_number,answer;
    //1.Ѱ�Ҵ��е�һ�������ŵ�λ��
    while(string[i]!='('&&string[i])
        i++;
    First_bracket=i;
    i=strlen(string)-1;
    //2.Ѱ�Ҵ������һ�������ŵ�λ��
    while(string[i]!=')'&&i>=0)
        i--;
    Second_bracket=i;
    //3.���������λ�÷��ϳ�������г�ȡ����Ĳ���
    if(First_bracket<strlen(string)){
        string[First_bracket]=0;
        string[Second_bracket]=0;
        strcpy(temp,&string[First_bracket+1]);
        //4.�����������ʽ�ӵ���ֵ
        temp_number=bracket(temp);
        //5.��ȡ�������ڲ����������ݣ����ü�����ϵ���ֵ����д��
        strcpy(temp,&string[Second_bracket+1]);
        sprintf(&string[First_bracket],"%lf",temp_number);
        strcat(string,temp);
    }
    //6.��ʱʽ���������ţ����д��˳�������
    muliply_divide(string);
    //7.��ʱʽ�����޳˳��������д��Ӽ�������
    answer=add_subtract(string);
    return answer;
}
void muliply_divide(char *string)                //�ṩ�Ӽ��˳���ʽ�Ӳ����˳����Ľ������滻
{
    int i;
    for(i=0;string[i];i++){
        if(string[i]=='*'||string[i]=='/'){
            double front_number,behind_number,answer;
            int First_location,Second_location;
            char temp[N]={0};
            First_location=i-1;
            Second_location=i+1;
            //1.�������ǰ���һ��������ֵ
            front_number=front_n(&First_location,string);
            //2.������ź����һ��������ֵ
            behind_number=behind_n(&Second_location,string);
            First_location++;
            Second_location--;
            //3.���ӵĴ����жϡ���Ϊ���ܴ��������޷�ʵ�֣������ڴ˼�⣬������Ϊ0���ж�
            if(string[i]=='/' && behind_number==0){
                printf("%s In this formula , the divisor cannot be zero !\n",string);
                printf("Program will over !\n");
                exit(-1);
            }
            //4.�Լ�������������и��еĴ���
            switch(string[i])
            {
                case '*' : answer = front_number * behind_number; break;
                case '/' : answer = front_number / behind_number; break;
                //������û����һ��
                default  : exit(-1);
            }
            //5.�ü�������Ľ���滻ԭ������Ĳ���
            strcpy(temp,&string[Second_location+1]);
            sprintf(&string[First_location],"%lf",answer);
            strcat(string,temp);
        }
    }
}
double add_subtract(char *string)                 //�ṩ���Ӽ�����ʽ�Ӳ������ֱ�ӷ���
{
    int i,f=1;
    double answer=0;
    char temp[N]={0};
    //1.���˵��һ�������ֵĻ���ô��˵�����Ǹ�������ʽ�ӣ�����һ���Ӻű�ʾ��һ����Ϊ����
    if(isdigit(string[0])){
        temp[0]='+';
        strcat(temp,string);
        strcpy(string,temp);
    }
    //2.�����һ���Ƿ��ţ����������������������֣�������ÿһ��������Ϊ�Ƿ��ź���
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
int arithmetic_character(char c)                 //�ж��ṩ���ַ��Ƿ�Ϊ��������
{
    if(c!='+'&&c!='-'&&c!='*'&&c!='/')
        return 0;
    else
        return 1;
}
double front_n(int *First_location,char *string)  //���������ǰ��һ������������С��
{
    int j;
    double answer;
    //1.�ƶ�λ�õ������ĵ�һ��λ��
    while((isdigit(string[*First_location])||string[*First_location]=='.')&&(*First_location)>=0){
        (*First_location)--;
    }
    if((*First_location)>0&&(string[(*First_location)-1]=='+'||string[(*First_location)-1]=='-')){
        j=(*First_location);
        (*First_location)--;
    }
    else
        j=(*First_location)+1;
    //2.���仯Ϊ������ź�һ����
    answer=behind_n(&j,string);
    return answer;
}
double behind_n(int *Second_location,char *string)//��������ź���һ������������С��
{
    int flag=0,n=1,f=1;
    double answer=0;
    if(string[*Second_location]=='+'||string[*Second_location]=='-'){
        f=(string[*Second_location]=='+')?1:-1;
        (*Second_location)++;
    }
    //1.��֤�˹��Ķ������ֻ�����С����
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
