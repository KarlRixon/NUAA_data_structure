
#include<stdio.h>
#define MAXSIZE 10
char op[MAXSIZE], num[MAXSIZE];//ȫ�ֱ���
int opTop, numTop;
void calculate(){

    char op1, op2;
    int opf;
    op2 = num[numTop-1];
    numTop--;
    op1 = num[numTop-1];
    numTop--;
    opf = op[opTop-1];
    opTop--;

    int tmpResult = 0;
    switch(opf){
        case '+':
            tmpResult = op1 + op2;
            break;
        case '-':
            tmpResult = op1 - op2;
            break;
        case '*':
            tmpResult = op1 * op2;
            break;
        case '/':
            tmpResult = op1 / op2;
            break;
    }
    num[numTop] = tmpResult;
    numTop++;
}
//����򵥱��ʽ
void dealExpression(){
    //��ʼ������ջ
    opTop = 0, numTop = 0;

    printf("��������ʽ(��#�Ž���)��");
    char currentChar;
    scanf("%c", &currentChar);
    while(currentChar!='#'){
        switch(currentChar){
            case '+':
            case '-':
                while(opTop&&op[opTop-1]!='('){
                    calculate();
                }

                op[opTop] = currentChar;
                opTop++;
                scanf("%c", &currentChar);
                break;
            case '*':
            case '/':
                if(opTop&&(op[opTop-1]=='*'||op[opTop-1]=='/')){
                    calculate();
                }
                op[opTop] = currentChar;
                opTop++;
                scanf("%c", &currentChar);
                break;
            case '(':
                op[opTop] = currentChar;
                opTop++;
                scanf("%c", &currentChar);
                break;
            case ')':
                while(op[opTop-1]!='('){//��ǰ��'('����opջһ������'('ƥ�䵽,��opջһ����Ϊ��
                    calculate();
                }
                opTop--;//��ջ������������
                scanf("%c",&currentChar);
                break;
            default://currentCharΪ���֣�����numջ
                int opNum = 0;
                do{
                    opNum = opNum*10 + currentChar-'0';
                    scanf("%c", &currentChar);
                }while(currentChar>='0'&&currentChar<='9');
                num[numTop] = opNum;
                numTop++;
                break;
        }//end switch
    }
    while(opTop){
        calculate();
    }
    int result = num[numTop-1];
    printf("��������%d\n", result);
}
int main(){
    dealExpression();
}
