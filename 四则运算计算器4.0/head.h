#include <stdio.h>
#include <stdlib.h>
#define N 80
double handle(char *string);                       //���崦����
int error_detection(char *string);                //��������ʽ���Ƿ���Ϲ���
double bracket(char *string);                      //������Ų���ȡ���滻�ĺ���
void muliply_divide(char *string);                //�ṩ�Ӽ��˳���ʽ�Ӳ����˳����Ľ������滻
double add_subtract(char *string);                 //�ṩ���Ӽ�����ʽ�Ӳ������ֱ�ӷ���
int arithmetic_character(char c);                 //�ж��ṩ���ַ��Ƿ�Ϊ��������
double front_n(int *First_location,char *string);  //���������ǰ��һ������������С��
double behind_n(int *Second_location,char *string);//��������ź���һ������������С��
