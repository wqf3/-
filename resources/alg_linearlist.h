#ifndef _ALG_LINEARLIST_H_
#define _ALG_LINEARLIST_H_

#define uchar unsigned char
#define uint unsigned int

/************************************************************************/
/* ���Ա�ṹ����                                                       */
/************************************************************************/
#define LArray_FALSE 0
#define LArray_TRUE  1

//ջ�Ĵ�С����
#define STACK_SIZE 30

typedef unsigned char LArray_BOOL;

/*Ԫ������*/
typedef enum
{
	NUMBER,						//��\xfd��Ԫ��Ϊ������\xfd
	OPERATOR,					//��\xfd��Ԫ��Ϊ���
	CONST_NUM,                  //��\xfd��Ϊ����\xfd����
	FUNCTION,                   //Ϊ����\xfd
	INVALID_TYPE				//��\xfd��Ԫ����Ч
}TYPE_FLAG;

/*���������\xfd��Ԫ��*/
typedef union
{
	double	dbNum;				//���������\xfd����
	char	cOperator;			//�����������
}TYPE;

/*���Ա�Ԫ��*/
typedef struct
{
	TYPE_FLAG	elemType;		//��\xfd��Ԫ������
	TYPE		elemValue;		//��\xfd��Ԫ��ʵ��ֵ�����
	double		dbComplex;		//�洢Ԫ���鲿ֵ
}LArrayElem;

/*���Ա�*/
typedef struct
{
	LArrayElem	*pElem;			//��\xfd��Ԫ�ش洢����
	uchar		nLength;		//��ǰ��\xfd��Ԫ�س���
	uchar		nTotalSize;		//��ǰ���Ա���
}LArray;


/************************************************************************/
/* �������Ա���\xfd����                                                           */
/************************************************************************/
LArray* ll_arry_create(const uchar nSelect);
void ll_arry_clr(LArray *pArray );

LArray_BOOL ll_arry_is_empty(LArray *pArray);
LArray_BOOL ll_arry_is_full(LArray *pArray);
uchar ll_arry_get_len(LArray *pArray);


/************************************************************************/
/* ջ��������\xfd����															*/
/************************************************************************/
LArray_BOOL stack_get_top(LArray *pArray, LArrayElem *pElem);
LArray_BOOL stack_push(LArray *pArray, const LArrayElem elem);
LArray_BOOL stack_pop(LArray *pArray, LArrayElem *pElem);

#endif
