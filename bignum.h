#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 1000

typedef struct biging
{
	char *num;//指向长整数数组（序号0中保存着最高位） 
	char sign;//符号（1表示正数，-1表示负数） 
	int digit;//保存该数的位数 
} BigInt;

//加法运算 
BigInt* BigIntAdd(BigInt num1, BigInt num2);

//减法运算
//void BigIntSub(pBigInt num1, pBigInt num2, pBigInt result);
//
////乘法运算
//void BigIntMul(pBigInt num1, pBigInt num2, pBigInt result); 
//
////除法运算
//void BigIntDiv(pBigInt num1, pBigInt num2, pBigInt result);  
