#include <stdio.h>
#include <stdlib.h>
#define N 80
float handle(char *string);                       //���崦����
int error_detection(char *string);                //��������ʽ���Ƿ���Ϲ���
float bracket(char *string);                      //������Ų���ȡ���滻�ĺ���
void muliply_divide(char *string);                //�ṩ�Ӽ��˳���ʽ�Ӳ����˳����Ľ������滻
float add_subtract(char *string);                 //�ṩ���Ӽ�����ʽ�Ӳ������ֱ�ӷ���
int arithmetic_character(char c);                 //�ж��ṩ���ַ��Ƿ�Ϊ��������
float front_n(int *First_location,char *string);  //���������ǰ��һ������������С��
float behind_n(int *Second_location,char *string);//��������ź���һ������������С��
