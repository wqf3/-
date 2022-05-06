#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "alg_linearlist.h"
#include "alg_caculate.h"
#include "alg_atof.h"
#include "alg_complex.h"


#define E 2.718282
#define PI 3.141593
#define PI_FONT 'p'                 //PI��12864����
#define DEGREE_FONT 'd'                //���12864����

#define check_if(function,value) if(0 == strcmp(strTemp,#function)) return value
#define CASE break;case
#define STACK_PUSH(pTarget,eElem) if(LArray_FALSE == stack_push(pTarget,eElem)){bResult = LArray_FALSE; break;}

//extern uchar g_chCalcStatus;
//extern double x,y,z;
//extern double g_ans; 
int BackFi = 0;
uchar g_chCalcStatus = CALC_NORMAL;
double x, y, z;
double g_ans;
uchar alg_const_handle(char c);

/***********************************************************************************
	���ܣ��Ƚϲ����������ȼ�˳��
	�βΣ�operator1:������1 operator2:������ 2
	���أ�������1���ȼ����ڲ�����2	--LEVEL_BIGGER
		  ������1���ȼ�С�ڲ�����2	--LEVEL_SMALLER
		  ������1���ȼ����ڲ�����2	--LEVEL_SAME
		  ������1������2�ԱȲ��Ϸ�	--LEVEL_INVALID
	��⣺������\xfd�Ĺ����ǱȽ����������������ȼ���ʵ�������ȳ˳���Ӽ��Ĺ���
		  ��ת������ʽ�Ĺ�������Ҫ�Ƚϵ�ǰ��������ջ�����������ȼ�˳��
***********************************************************************************/
LEVEL_TYPE alg_compare_level(char operator1, char operator2)
{
	char operator1_level, operator2_level;

	//�ж��������������������ȼ����е�λ��
	switch(operator1)
	{
		case '+' :
		case '-' : operator1_level = 1;	break;

		case '*' :
		case '/' : operator1_level = 2;	break;

		case '^' :		
		case 'i' :									//����\xfd��ʶ
		case '!' :
        case DEGREE_FONT : operator1_level = 3;	break;

        case 'f' : operator1_level = 4; break;        //����\xfd��ʶ

		case '(' :
		case ')' : operator1_level = 5; break;
        default  : return LEVEL_INVALID;
	}
	switch(operator2)
	{
		case '+' :
		case '-' : operator2_level = 1;	break;

		case '*' :
		case '/' : operator2_level = 2;	break;

		case '^' :
		case 'i' :									//����\xfd��ʶ
		case '!' :
        case DEGREE_FONT : operator2_level = 3;	break;

        case 'f' : operator2_level = 4; break;        //����\xfd��ʶ

		case '(' :
		case ')' : operator2_level = 5; break;
        default  : return LEVEL_INVALID;
	}

	//�ж����������������ȼ���ϵ
	if((operator1_level - operator2_level) > 0)
	{
		return LEVEL_BIGGER;
	}
	else if((operator1_level - operator2_level) < 0)
	{
		return LEVEL_SMALLER;
	}
	else
	{
		return LEVEL_SAME;
	}
}

/***********************************************************************************
	���ܣ��ж��ַ�������
	�βΣ�c:�����ַ�
	���أ����	--OPERATOR
		  ��\xfd��	--NUMBER
		  �Ƿ�	--INVALID_TYPE
	��⣺�ж��ַ�����ǰ��ֵΪ���֡����š����ǷǷ�����
***********************************************************************************/
TYPE_FLAG alg_judge_type(char c)
{	
	//��ͨ����ģʽ
	if(g_chCalcStatus == CALC_NORMAL)
	{
		if (c == '+' ||
			c == '-' ||
			c == '*' ||
			c == '/' ||
			c == '^' ||
			c == '(' ||
			c == ')' ||
			c == '!' ||
	        c == DEGREE_FONT	       //�����
	        )
		{
			return OPERATOR;
		}
		else if((c>='0' && c<='9') || c=='.')
		{
			return NUMBER;
		}
		else if(alg_const_handle(c) != NO_CONST)    //��Ϊ����
	    {
	        return CONST_NUM;
	    }
		else if(c == 'l' || c == 's' || c == 'c' || c == 't' || c == 'a')       //����ĸ��s,c,t,l,a�����ж�Ϊ����
		{
		    return FUNCTION;
		}
		else
		{
			return INVALID_TYPE;
		}
	}
	
	//��������ģʽ
	else if(g_chCalcStatus == CALC_COMPLEX)
	{
		if (c == '+' ||
			c == '-' ||
			c == '*' ||
			c == '/' ||
			c == '^' ||
			c == '(' ||
			c == ')' ||
			c == 'i'					//������ʶ
	        )
		{
			return OPERATOR;
		}
		else if((c>='0' && c<='9') || c=='.')
		{
			return NUMBER;
		}
		else if(alg_const_handle(c) != NO_CONST)    //��Ϊ����
	    {
	        return CONST_NUM;
	    }
		else
		{
			return INVALID_TYPE;
		}
	}

	return INVALID_TYPE;
}


/***********************************************************************************
	���ܣ�����\xfd����
	�βΣ�c:�����ַ�
	���أ�����\xfd������
	��⣺����\xfd��δ֪��\xfd���жϣ�����жϽ��Ϊ����\xfd��δ֪��\xfd������ת������ʽ�������滻
***********************************************************************************/
uchar alg_const_handle(char c)
{
    switch(c)
    {
        case 'e'     : return E_FLAG;
        case PI_FONT : return PI_FLAG;
		case 'x'	 : return X_FLAG;
		case 'y'	 : return Y_FLAG;
		case 'z'	 : return Z_FLAG;
		case 'A'	 : return ANS_FLAG;
    }

    return NO_CONST;
}


/***********************************************************************************
	���ܣ�����\xfd����
	�βΣ�c:�����ַ�
	���أ�����\xfd������
	��⣺ʶ����\xfd��������sin��cos�ȣ�����ת�������ʽ�У����չ���Ժ���\xfd������ת��
***********************************************************************************/
uchar alg_func_handle(char *c)
{
    char strTemp[5] = {0,0,0,0,0};      //��������ʼ��һ�����ڴ洢����\xfd������ʱ��\xfd��

    strTemp[0] = c[0];
    strTemp[1] = c[1];                  //��ȡǰ�����ַ�
    check_if(ln,LN_FLAG);                //����Ƿ�Ϊ˫�ַ��ĺ���\xfd

    strTemp[2] = c[2];                  //��ȡǰ�����ַ�
    if('h' != c[3])                     //��ֹ˫�����Ǻ���\xfd����
    {
        check_if(log,LOG_FLAG);             //����Ƿ�Ϊ���ַ��ĺ���\xfd
        check_if(sin,SIN_FLAG);
        check_if(cos,COS_FLAG);
        check_if(tan,TAN_FLAG);
		check_if(abs,ABS_FLAG);
    }

    strTemp[3] = c[3];                  //��ȡǰ�ĸ��ַ�
    //����Ƿ�Ϊ�ĸ��ַ��ĺ���\xfd
    check_if(sinh,SINH_FLAG);
    check_if(cosh,COSH_FLAG);
    check_if(tanh,TANH_FLAG);
	check_if(asin,ASIN_FLAG);
    check_if(acos,ACOS_FLAG);
    check_if(atan,ATAN_FLAG);

    return FUNC_INVALID;
}


/***********************************************************************************
	���ܣ�����������\xfd�ֺͲ�����\xfd������
	�βΣ�eElem1,eElem2	����LArrayElem�ṹ
		  nOperator		���
		  eResult		��������LArrayElemָ��
	���أ�����ɹ�	--1
		  ����ʧ��	--0
	��⣺���ڼ��������ʽ����������������\xfd�֣������ѹ�غ������ʽ
***********************************************************************************/
LArray_BOOL alg_calc(LArrayElem *eElem1, char nOperator, LArrayElem *eElem2, LArrayElem *eResult)
{
	uchar i;
	if(g_chCalcStatus == CALC_NORMAL)
	{
		switch (nOperator)
		{
	        case '+' :
	            eResult->elemValue.dbNum = eElem1->elemValue.dbNum + eElem2->elemValue.dbNum;
	            break;
	
	        case '-' :
	            eResult->elemValue.dbNum = eElem1->elemValue.dbNum - eElem2->elemValue.dbNum;
	            break;
	
	        case '*' :
	            eResult->elemValue.dbNum = eElem1->elemValue.dbNum * eElem2->elemValue.dbNum;
	            break;
	
	        case '/' :
	            if (0 == eElem2->elemValue.dbNum)
	            {
	                return LArray_FALSE;
	            }
	
	            eResult->elemValue.dbNum = eElem1->elemValue.dbNum / eElem2->elemValue.dbNum;
	            break;
				
	        case '^' :
	            if (0 > eElem1->elemValue.dbNum && eElem2->elemValue.dbNum != (uchar)eElem2->elemValue.dbNum)
	            {
	                return LArray_FALSE;
	            }
	            eResult->elemValue.dbNum = pow(eElem1->elemValue.dbNum,eElem2->elemValue.dbNum);
	            break;
	
	        case DEGREE_FONT :
	            eResult->elemValue.dbNum = eElem1->elemValue.dbNum * PI / 180;
	            break;
			
			case '!' :
				if (((int)eElem1->elemValue.dbNum != eElem1->elemValue.dbNum) 
					|| eElem1->elemValue.dbNum > 60 || eElem1->elemValue.dbNum < 0 )	//������������\xfd
	            {
	                return LArray_FALSE;
	            }
				if(eElem1->elemValue.dbNum == 1 ||eElem1->elemValue.dbNum == 0)
				{
					eResult->elemValue.dbNum = 1;
					break;
				}
				eResult->elemValue.dbNum = 1;
				for(i=1;i<eElem1->elemValue.dbNum+1;i++)
				{
	            	eResult->elemValue.dbNum = eResult->elemValue.dbNum  * i;
				}
	            break;
				
	        case 'f' :
	            switch((uchar)eElem1->elemValue.dbNum)
	            {
	                case LN_FLAG    :   eResult->elemValue.dbNum = log(eElem2->elemValue.dbNum);
	                CASE LOG_FLAG   :   eResult->elemValue.dbNum = log10(eElem2->elemValue.dbNum);
	                CASE SIN_FLAG   :   eResult->elemValue.dbNum = sin(eElem2->elemValue.dbNum);
	                CASE COS_FLAG   :   eResult->elemValue.dbNum = cos(eElem2->elemValue.dbNum);
	                CASE TAN_FLAG   :   eResult->elemValue.dbNum = tan(eElem2->elemValue.dbNum);
	                CASE SINH_FLAG  :   eResult->elemValue.dbNum = sinh(eElem2->elemValue.dbNum);
	                CASE COSH_FLAG  :   eResult->elemValue.dbNum = cosh(eElem2->elemValue.dbNum);
	                CASE TANH_FLAG  :   eResult->elemValue.dbNum = tanh(eElem2->elemValue.dbNum);
					CASE ASIN_FLAG  :	eResult->elemValue.dbNum = asin(eElem2->elemValue.dbNum);
            		CASE ACOS_FLAG  :	eResult->elemValue.dbNum = acos(eElem2->elemValue.dbNum);
            		CASE ATAN_FLAG  :	eResult->elemValue.dbNum = atan(eElem2->elemValue.dbNum);
					CASE ABS_FLAG	:	eResult->elemValue.dbNum = fabs(eElem2->elemValue.dbNum);
	
	                break;
	            }
	            break;
		}
	}
	
	else if(g_chCalcStatus == CALC_COMPLEX)
	{
		switch (nOperator)
		{
			case '+' :
	            OPERATOR_COMPLEX(plus,eElem1,eElem2,eResult);
	            break;
	
	        case '-' :
	            OPERATOR_COMPLEX(subtract,eElem1,eElem2,eResult);
	            break;
	
	        case '*' :
	            OPERATOR_COMPLEX(multiply,eElem1,eElem2,eResult);
	            break;
	
	        case '/' :
	            if (0 == complex_mod(eElem2))	//������\xfd��ģ����Ϊ0
	            {
	                return LArray_FALSE;
	            }
				OPERATOR_COMPLEX(divide,eElem1,eElem2,eResult);
				break;
			
			case '^' :
				if(LArray_FALSE == complex_power(eElem1,eElem2,eResult))
				{
					return LArray_FALSE;
				}
				break;
			
			case 'i' :					//����\xfd����
				eResult->elemValue.dbNum = -(eElem1->dbComplex);
				eResult->dbComplex = eElem1->elemValue.dbNum;		//������ʵ���������鲿����
				break;
		}
	}
	
	return LArray_TRUE;
}


/***********************************************************************************
    ���ܣ��ƶ����ʽ�ĵ�ǰָ�뵽��һ��Ԫ��
    �βΣ���
    ���أ���
    ��⣺������\xfd������ת������ʽ�У��ж�ǰһ����\xfd�ֵ�λ�ã����ƶ�ָ�뵽��һ����Ҫ�жϵ�λ��
***********************************************************************************/
void alg_pmove(char **ppCur)
{
	if(OPERATOR == alg_judge_type((*ppCur)[0]))
	{
		*ppCur +=1;
	}
	else if(CONST_NUM == alg_judge_type((*ppCur)[0]))
	{
		if(ANS_FLAG == alg_const_handle((*ppCur)[0]))
			*ppCur +=3;			//Ans������
		else 
			*ppCur +=1;
	}
	else if(FUNCTION == alg_judge_type((*ppCur)[0]))
    {
        switch(alg_func_handle(*ppCur))
        {
            case LN_FLAG  : *ppCur +=2; break;    //���ֺ���\xfd

            case LOG_FLAG :
            case SIN_FLAG :
            case COS_FLAG :
            case TAN_FLAG :
			case ABS_FLAG : *ppCur +=3; break;    //���ֺ���\xfd

            case SINH_FLAG:
            case COSH_FLAG:
            case TANH_FLAG: 
			case ASIN_FLAG :
            case ACOS_FLAG :
            case ATAN_FLAG : *ppCur +=4; break;    //���ֺ���\xfd
        }
    }
	else
	{
		while(NUMBER == alg_judge_type((*ppCur)[0]) && '\0' != (*ppCur)[0])
		{
			*ppCur +=1;
		}
	}
}

/***********************************************************************************
    ���ܣ���������ʽת��Ϊ������ʽ
    �βΣ�pExpression:�ַ����ͱ��ʽ pPostArray:���������ʽ�����Ա�
    ���أ�1:ת���ɹ� 2:ת��ʧ��
    ��⣺ת�������ʽ�ĺ���\xfd��ת��˵�����£�
	��1������һ��ջ��һ�����Ա�stack������ʱ�洢��������������ջ��������ʱ�洢��������������ջ����ѭ��������ԭ�����Ա�ll���ڴ洢ת����ɺ�ĺ�����ʽ��
	��2����������ʽ�������ʽ�ַ�����˿�ʼ�����ȡ�ַ�c��
			A.��c����\xfd�֣������������\xfd�֣�ת���ɸ�����\xfd�����llĩ��
			B.��c�Ƿ��ţ�
				����c��'('����ֱ��ѹ��stack��
				����c��')'���򽫾���stack�������һ��'('֮ǰ��������������ջ���������Ա�llĩ�ˣ���ʱ'()'��������
				����c�������:x
					a.��x��'-'��
					�ж��Ƿ����ַ�����һ��ֵ���ǣ��򽫺������\xfd�ַ��ţ�ͬʱ�����������
					�ж�ջ���ǲ���'('���ǣ��򽫺�����\xfd�ַ��ţ�ͬʱ�����������
				����x�ǳ�����ʶ��(e,��,...)ת������\xfd�ֲ���llĩ��
				�����Ǻ���\xfd��������������\xfd����ƥ�䡣ƥ��������\xfd����ʽ�������Ա��ٲ���һ��'f'������\xfd��ʶ
				������'��'����\xfd�������ѹ��0��ѹ��'d'
				��.��ջ����'('��ֱ��ѹջ
				��.��ջ������'('��Ƚ����ȼ���x���ȼ��߾�ѹ�룬����stack�������������������Ա�ĩ�ˣ�ֱ��x���ȼ����ߣ���ѹ��
	��������ȼ���
	    ����>����\xfd>�˷�>�˳�>�Ӽ���ע�⺯��\xfd��'��'�ǵ�Ŀ����ġ�������ת������ʽʱ�ʹ����ˣ�����\xfd������\xfd��Ҫ����ֵ�����ٴ���������
	������ʽ��ֵ��ʱ����Ҫ���ǡ�
***********************************************************************************/
LArray_BOOL alg_mid_to_post(char *pExpression, LArray *pPostArray)
{
    uchar minus_flag = 1;                 //��һ���ַ���־
    uchar function_temp;                   //��ǰ����\xfd״ָ̬��
	char *pCur;
	LArrayElem eTop;
	LArray_BOOL bResult;
	LArray laStackOperator;
	
	//�������ջ
	LArray						*pStackOperator = &laStackOperator;
	LArrayElem					pElem_StackOperator[STACK_SIZE/2];
	//��ʼ�����ջ
	pStackOperator->pElem 		= pElem_StackOperator;
	pStackOperator->nLength		= 0;
	pStackOperator->nTotalSize	= STACK_SIZE/2;
	
	pCur = pExpression;
	eTop.elemValue.dbNum = 0;
	eTop.dbComplex 		= 0;
	
	bResult	= LArray_TRUE;
	
	//�����������ʽ�ַ���
	while(pCur[0] != '\0')
	{
        if (INVALID_TYPE == alg_judge_type(pCur[0]))//���벻�Ϸ�
		{
			bResult	= LArray_FALSE;
			break;
		}

        else if(CONST_NUM == alg_judge_type(pCur[0]))//����Ϊ����
        {
            eTop.elemType = NUMBER;
            switch(alg_const_handle(pCur[0]))
            {
                case E_FLAG  :  eTop.elemValue.dbNum = E;   break;
                case PI_FLAG :  eTop.elemValue.dbNum = PI;  break;
				case X_FLAG  :  eTop.elemValue.dbNum = x;  break;
				case Y_FLAG  :  eTop.elemValue.dbNum = y;  break;
				case Z_FLAG  :  eTop.elemValue.dbNum = z;  break;
				case ANS_FLAG:	eTop.elemValue.dbNum = g_ans;  break;
            }
			STACK_PUSH(pPostArray, eTop);
        }

		else if(NUMBER == alg_judge_type(pCur[0]))//������ֱ�����뵽���Ա�
		{
			eTop.elemType			= NUMBER;
			eTop.elemValue.dbNum	= alg_atof(pCur);//strtod(pCur,(char **)NULL);
			STACK_PUSH(pPostArray, eTop);
		}

		else//�����������
		{
		    if(minus_flag == 1)  //����ջΪ���һ�ǰһ�����Ϊ��(��,˵����������
            {
                if(pCur[0] == '-' || pCur[0] == '+')
                {
                    eTop.elemType			= NUMBER;       //ѹ��0
                    eTop.elemValue.dbNum	= 0;
                    STACK_PUSH(pPostArray, eTop);
                }
            }
            if(pCur[0] == DEGREE_FONT || pCur[0] == '!') //�������ǡ��!������Ҫ�ڴ���ǰ��0
            {
                eTop.elemType			= NUMBER;       //ѹ��0
                eTop.elemValue.dbNum	= 0;
                STACK_PUSH(pPostArray, eTop);
            }			
			if(pCur[0] == 'i')
			{
				if(minus_flag == 1 || OPERATOR == alg_judge_type(pCur[-1]))			//��������㸺����������һ����Ҫ��1����������һ���ǲ��Ƿ���
				{																	//�˴������漼���ɣ�Ҫ�����ַ�����ʼ��������㸺����������\xfd��Խ����ʲ���ִ�С���������ַ�����ʼ����[-1]���ᵼ��Խ��
					eTop.elemType			= NUMBER;       //ѹ��1
					eTop.elemValue.dbNum	= 1;			//���ڽ�� a+i������
					STACK_PUSH(pPostArray, eTop);
				}
				
                eTop.elemType			= NUMBER;       //ѹ��0
                eTop.elemValue.dbNum	= 0;
                STACK_PUSH(pPostArray, eTop);
			}
			
            else if(FUNCTION == alg_judge_type(pCur[0]))         //����\xfd����
            {
                eTop.elemType			= NUMBER;
                eTop.elemValue.dbNum    = alg_func_handle(pCur);       //ѹ�뺯��\xfd����
                if(FUNC_INVALID == alg_func_handle(pCur))               //����\xfd��������ʽ����
                {
                    bResult	= LArray_FALSE;
                    break;
                }

                STACK_PUSH(pPostArray, eTop);
                function_temp = pCur[0];
                pCur[0] = 'f';              //��Ӻ���\xfd��ʶ

            }

			if(pCur[0] == '(')//����'('
			{
				eTop.elemType				= OPERATOR;
				eTop.elemValue.cOperator	= pCur[0];
				STACK_PUSH(pStackOperator, eTop);
				minus_flag = 1;                 //����������
			}
			else if (pCur[0] == ')')//����')'
			{
				//һֱ��ջѹ�����Ա�ֱ��'('
				while (LArray_TRUE == stack_get_top(pStackOperator, &eTop) &&
					   eTop.elemValue.cOperator != '(')
				{
					stack_pop(pStackOperator, &eTop);
                    STACK_PUSH(pPostArray, eTop);
				}

				if (LArray_TRUE == stack_get_top(pStackOperator, &eTop) &&
					eTop.elemValue.cOperator == '(')
				{
					stack_pop(pStackOperator, NULL);//ֱ�ӵ���'('
				}
				else
				{
					bResult	= LArray_FALSE;
					break;
				}
			}
			else if (LArray_TRUE == stack_get_top(pStackOperator, &eTop) &&
					 eTop.elemValue.cOperator == '(')//ջ��Ԫ��Ϊ'('��ǰ�����ѹ�����ջ
			{
				eTop.elemType				= OPERATOR;
				eTop.elemValue.cOperator	= pCur[0];
				STACK_PUSH(pStackOperator,eTop);
			}
			else if (LArray_FALSE == stack_get_top(pStackOperator, &eTop) ||
					 LEVEL_SMALLER == alg_compare_level(eTop.elemValue.cOperator, pCur[0]))
			{
				//ջΪ�ջ�ջ����������ȼ�С�ڵ�ǰ��������(��ʱ��ǰ���������())���򽫵�ǰ�����ѹ�����ջ
				eTop.elemType				= OPERATOR;
				eTop.elemValue.cOperator	= pCur[0];
				STACK_PUSH(pStackOperator, eTop);
			}
			else
			{

				//����ջ��Ϊ����ջ����������ȼ����ڵ��ڵ�ǰ��������(��ʱ��ǰ���������()),
				//һֱ��ջѹ�����Ա�ֱ���������������

				while(LArray_TRUE  == stack_get_top(pStackOperator, &eTop) &&
					  eTop.elemValue.cOperator != '(' &&
					  LEVEL_SMALLER != alg_compare_level(eTop.elemValue.cOperator, pCur[0]))
				{
					stack_pop(pStackOperator, &eTop);
                    STACK_PUSH(pPostArray, eTop);
				}

				//��ǰ�����ջ
				eTop.elemType				= OPERATOR;
				eTop.elemValue.cOperator	= pCur[0];
				STACK_PUSH(pStackOperator, eTop);
			}
		}
        if(pCur[0] != '(')
            minus_flag = 0;                     //��յ�һ���ַ���־
        if(pCur[0] == 'f')
            pCur[0] = function_temp;            //�������\xfd��ʶ
		alg_pmove(&pCur);
	}

	//��ʣ�µ����ջ��ȫ����ջ���뵽���Ա���
	if (bResult	== LArray_TRUE)
	{
		while (LArray_FALSE == ll_arry_is_empty(pStackOperator))
		{
			stack_pop(pStackOperator, &eTop);
            stack_push(pPostArray, eTop);
		}
	}

	return bResult;
}


/***********************************************************************************
	���ܣ������ʽ��������
	�βΣ�pExpression:�ַ����ͱ��ʽ pRealResult:ʵ������ pImaginaryResult����������
	���أ�����ɹ�	--1
		  ����ʧ��	--0
	��⣺���Ա������������ã�����һ���ַ���������"1+1"��ֱ�Ӵ�result�ж�ȡ����������Ϊʵ�����鲿
		  ��������ֻ��ʵ�����㣬������鲿ֱ�Ӵ�NULL��������Ҫ����g_chCalcStatus��ֵ�����ú�������
		  ģʽ
***********************************************************************************/
LArray_BOOL alg_calc_expression(char *pExpression, double *pRealResult, double *pImaginaryResult)
{
	LArrayElem eNum1, eNum2, eResult;
	LArray_BOOL	bResult;
	uchar i;
	LArray laPostArray, laStackNum;

	//�������Ա�
	LArray					  *pPostArray = &laPostArray;
	LArrayElem				  pElem_PostArry[STACK_SIZE];
	//�������������ջ
	LArray					  *pStackNum = &laStackNum;
	LArrayElem				  pElem_StackNum[(STACK_SIZE-6)/4+3];		//��Ϊֻ��5������ȼ������������ջ����5����

	//���Ա��ʼ��
	pPostArray->pElem			= pElem_PostArry;
	pPostArray->nLength			= 0;
	pPostArray->nTotalSize		= STACK_SIZE;	
	//��ʼ�����������ջ
	pStackNum->pElem 			= pElem_StackNum;
	pStackNum->nLength			= 0;
	pStackNum->nTotalSize		= (STACK_SIZE-6)/4+3;

	//Ԫ�س�ʼ��
	eResult.elemValue.dbNum = 0;
	eResult.dbComplex 		= 0;
	
	bResult	= LArray_TRUE;
	
	//�õ�������ʽ
	if(LArray_TRUE == alg_mid_to_post(pExpression, pPostArray))
	{
		//�������Ա�
		for (i = 0; i < pPostArray->nLength; i++)
		{
			if (pPostArray->pElem[i].elemType == NUMBER)
			{
				stack_push(pStackNum, pPostArray->pElem[i]);
			}
			else
			{
				if (LArray_FALSE == stack_pop(pStackNum, &eNum2) ||
					LArray_FALSE == stack_pop(pStackNum, &eNum1))
				{
					//��ջ����(���벻�Ϸ�ʱ)
					bResult	= LArray_FALSE;
					break;
				}
				else
				{
					if (LArray_FALSE == alg_calc(&eNum1,
											     pPostArray->pElem[i].elemValue.cOperator,
											     &eNum2,
											     &eResult))
					{
						//�������(���벻�Ϸ�ʱ)
						bResult	= LArray_FALSE;
						break;
					}
					else
					{
						eResult.elemType = NUMBER;
						stack_push(pStackNum, eResult);
					}
				}
			}
		}
	}
	else
	{
		bResult	= LArray_FALSE;
	}

	if (bResult	== LArray_TRUE)
	{
		//���������ջ���Ȳ�����1��������ʽ���Ϸ�
		if (ll_arry_get_len(pStackNum) != 1)
		{
			bResult	= LArray_FALSE;
		}
		else
		{
			stack_get_top(pStackNum, &eResult);
			*pRealResult = eResult.elemValue.dbNum;
			*pImaginaryResult = eResult.dbComplex;
		}
	}
	
	return bResult;
}

