#include "alg_linearlist.h"
#include "alg_complex.h"
#include <math.h>

#define ELEM_REAL(flag) eElem##flag->elemValue.dbNum
#define ELEM_IMAG(flag) eElem##flag->dbComplex
#define RESULT_REAL eResult->elemValue.dbNum
#define RESULT_IMAG eResult->dbComplex

void complex_plus(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult) //����\xfd�ӷ�����������LArrayElem�ṹ���͵�ָ��
{
	//z=��a+bi)+��c+di��=��a+c��+��b+d��i
	RESULT_REAL = ELEM_REAL(1) + ELEM_REAL(2);
	RESULT_IMAG = ELEM_IMAG(1) + ELEM_IMAG(2);
}

void complex_subtract(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult) //����\xfd��������������LArrayElem�ṹ���͵�ָ��
{
	//z=��a+bi��-��c+di��=��a-c��+��b-d��i
	RESULT_REAL = ELEM_REAL(1) - ELEM_REAL(2);
	RESULT_IMAG = ELEM_IMAG(1) - ELEM_IMAG(2);
}

void complex_multiply(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult)//����\xfd�˷�����������LArrayElem�ṹ���͵�ָ��
{
	//z=��a+bi��*��c+di��= ( ac-bd )+( ad+bc ) i
	RESULT_REAL = (ELEM_REAL(1))*(ELEM_REAL(2)) - (ELEM_IMAG(1)) * (ELEM_IMAG(2));
	RESULT_IMAG = (ELEM_REAL(1))*(ELEM_IMAG(2)) + (ELEM_IMAG(1)) * (ELEM_REAL(2));
}

void complex_divide(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult)//����\xfd��������������LArrayElem�ṹ���͵�ָ��
{
	//z=(a+jb)/(c+jd)=( (ac+bd)+(bc-ad)i )/( c*c+d*d )
	RESULT_REAL= ( (ELEM_REAL(1))*(ELEM_REAL(2)) + (ELEM_IMAG(1))*(ELEM_IMAG(2)) ) 
	/ ( (ELEM_REAL(2))* (ELEM_REAL(2)) + (ELEM_IMAG(2))* (ELEM_IMAG(2)) );
	RESULT_IMAG= ( (ELEM_IMAG(1))*(ELEM_REAL(2)) - (ELEM_REAL(1))*(ELEM_IMAG(2)) ) 
	/ ( (ELEM_REAL(2))* (ELEM_REAL(2)) + (ELEM_IMAG(2))* (ELEM_IMAG(2)) );
}

uchar complex_power(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult)//����\xfd�˷�����������LArrayElem�ṹ���͵�ָ��
{
	uint i;
	LArrayElem eBuf;
	
	if(ELEM_IMAG(2) != 0.0 || ELEM_REAL(2) != (uint)ELEM_REAL(2))
	{
		return LArray_FALSE;		//�˷�����ֻ��Ϊ��ʵ��\xfd
	}
	if(ELEM_REAL(2) > 0)
	{
		*eResult = *eElem1;									//��ȡeElem��ֵ
		for(i = 1;i < ELEM_REAL(2);i++)					//ѭ��ʣ��n-1��
		{
			complex_multiply(eElem1, eResult, &eBuf);
			*eResult = eBuf;
		}
	}
	else
	{
		if(0 == complex_mod(eElem1))
			return LArray_FALSE;	//0���ݵ���\xfd����Ϊ0
		else
		{
			RESULT_REAL = 1;
			RESULT_IMAG = 0;
		}
	}
	
	return LArray_TRUE;
	
}

double complex_mod(LArrayElem *eElem1)//����\xfd��ģ������һ��LArrayElem�ṹ���͵�ָ�룬����ģ��ֵ
{
	double length;
	length = sqrt ( (ELEM_REAL(1))* (ELEM_REAL(1)) + (ELEM_IMAG(1))* (ELEM_IMAG(1)) );
	return length;
}