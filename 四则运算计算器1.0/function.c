#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
float handle(char *string)         //���崦����
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
int error_detection(char *string)  //��������ʽ���Ƿ���Ϲ���
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
float bracket(char *string)         //������Ų���ȡ���滻�ĺ���
{
    int First_bracket,Second_bracket;
    int i=0;
    char temp[N]={0};
    float temp_number,answer;
    // Ѱ�ҵ�һ�������һ�����ţ���Ϊ�������������
    while(string[i]!='('&&string[i])
        i++;
    First_bracket=i;
    i=strlen(string)-1;
    while(string[i]!=')'&&i>=0)
        i--;
    Second_bracket=i;
    //�������ڵ����ݸ��Ƶ�һ�������������ȥ���ŵĴ���
    if(First_bracket<strlen(string)){
        string[First_bracket]=0;
        string[Second_bracket]=0;
        strcpy(temp,&string[First_bracket+1]);
        temp_number=bracket(temp);
        //��ʱtemp_numberΪ�����ڵ���ֵ��
        //����Ըո������ڵ����ݽ����滻���滻Ϊtemp number���ַ���ֵ��
        strcpy(temp,&string[Second_bracket+1]);
        sprintf(&string[First_bracket],"%.0f",temp_number);
        strcat(string,temp);
    }
    //��ʱ�����Ľ��Ϊ�Ӽ��˳�������㣬�����Ѿ�������������
    muliply_divide(string);
    //��ʱ������stringΪ���Ӽ����ģ��������add subtract�м�����ֵ��
    answer=add_subtract(string);
    return answer;
}
void muliply_divide(char *string)  //�ṩ�Ӽ��˳���ʽ�Ӳ����˳����Ľ������滻
{
    int i;
    for(i=0;string[i];i++){
        if(string[i]=='*'||string[i]=='/'){
            //�ֱ���ǰ�Һ�������ҵ������������
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
                //�����ϲ�������������
                default  : exit(-1);
            }
            strcpy(temp,&string[Second_location+1]);
            sprintf(&string[First_location],"%.0f",answer);
            strcat(string,temp);
        }
    }
}
float add_subtract(char *string)   //�ṩ���Ӽ�����ʽ�Ӳ������ֱ�ӷ���
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
int arithmetic_character(char c)   //�ж��ṩ���ַ��Ƿ�Ϊ��������
{
    if(c!='+'&&c!='-'&&c!='*'&&c!='/')
        return 0;
    else
        return 1;
}
