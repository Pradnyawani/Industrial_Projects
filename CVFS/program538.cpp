#include<stdio.h>



int main()
{
    char str[80];
    char Command[4][20];

    int iRet=0;
    int No1=0,No2=0;

    printf("Enter 2 numbers-");

    iRet=scanf("%d%d",&No1,&No2); 

    printf("first number %d :\n",No1);
    printf("second number %d :\n",No1);

    printf("Return value scanf is :%d\n",iRet);

    printf("%d\n",iRet);
    return 0;
}