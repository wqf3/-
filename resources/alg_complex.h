#ifndef _ALG_COMPLEX_H_
#define _ALG_COMPLEX_H_

#define uchar unsigned char
#define uint unsigned int

#define OPERATOR_COMPLEX(operator,eElemX,eElemY,eResult) complex_##operator(eElemX, eElemY, eResult)

double complex_mod(LArrayElem *eElem1);



void complex_plus(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult); 	//�����ӷ�����������LArrayElem�ṹ���͵�ָ��
void complex_subtract(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult); //������������������LArrayElem�ṹ���͵�ָ��
void complex_multiply(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult);	//�����˷�����������LArrayElem�ṹ���͵�ָ��
void complex_divide(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult);	//������������������LArrayElem�ṹ���͵�ָ��
uchar complex_power(LArrayElem *eElem1 ,LArrayElem *eElem2, LArrayElem *eResult);	//�����˷�����������LArrayElem�ṹ���͵�ָ��

#endif