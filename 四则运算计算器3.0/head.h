#include <stdio.h>
#include <stdlib.h>
#define N 80
float handle(char *string);                       //总体处理部分
int error_detection(char *string);                //检测输入的式子是否符合规则
float bracket(char *string);                      //检测括号并提取并替换的函数
void muliply_divide(char *string);                //提供加减乘除的式子并将乘除法的结果算出替换
float add_subtract(char *string);                 //提供纯加减法的式子并将结果直接返回
int arithmetic_character(char c);                 //判断提供的字符是否为算术符号
float front_n(int *First_location,char *string);  //用来求符号前面一个数，可以是小数
float behind_n(int *Second_location,char *string);//用来求符号后面一个数，可以是小数
