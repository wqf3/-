#ifndef _ALG_CACULATE_H_
#define _ALG_CACULATE_H_

#define uchar unsigned char
#define uint unsigned int

typedef enum
{
	LEVEL_BIGGER,		//���ȼ���
	LEVEL_SMALLER,		//���ȼ���
	LEVEL_SAME,			//���ȼ����
	LEVEL_INVALID		//������Ϸ�
}LEVEL_TYPE;

typedef enum
{
	E_FLAG,             //��Ȼ������־
	PI_FLAG,            //�б�־
	X_FLAG,
	Y_FLAG,
	Z_FLAG,
	ANS_FLAG,
	NO_CONST            //�ǳ���
}CONST_FLAG;

typedef enum
{
	LN_FLAG,
	LOG_FLAG,
	SIN_FLAG,
	COS_FLAG,
	TAN_FLAG,
	ABS_FLAG,
	SINH_FLAG,
	COSH_FLAG,
	TANH_FLAG,
	ASIN_FLAG,
	ACOS_FLAG,
	ATAN_FLAG,
	FUNC_INVALID		//�������Ϸ�
}FUNC_FLAG;


typedef enum
{
	CALC_NORMAL,		//��ͨ����
	CALC_COMPLEX,		//�������㣨֧�ּӼ��˳�����֧�ֺ�����
}CALC_STATUS;

uchar alg_calc_expression(char *pExpression, double *pRealResult, double *pImaginaryResult);

#endif
