#include "alg_atof.h"

char is_digit(char ch)
{
    if(ch>='0'&&ch<='9')
        return 1;
    else
        return 0;
}
uchar is_space(char ch)
{
    if(ch==' ')
        return 1;
    else
        return 0;
}
double alg_atof(char *s)
{
    double power,value;
    int i,sign;
    for(i=0;is_space(s[i]);i++);//��ȥ�ַ���ǰ�Ŀո�
		sign=(s[i]=='-')?-1:1;
    if(s[i]=='-'||s[i]=='+')//Ҫ���з���λ��ǰ��һλ
        i++;
    for(value=0.0;is_digit(s[i]);i++)//����С����ǰ������
        value=value*10.0+(s[i]-'0');
    if(s[i]=='.')
        i++;
    for(power=1.0;is_digit(s[i]);i++)//����С����������
    {
        value=value*10.0+(s[i]-'0');
        power*=10.0;
    }
    return sign*value/power;
}