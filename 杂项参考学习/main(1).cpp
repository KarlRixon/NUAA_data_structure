
#include<stdio.h>
#define MAXSIZE 10
char op[MAXSIZE], num[MAXSIZE];//全局变量
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
//处理简单表达式
void dealExpression(){
    //初始化两个栈
    opTop = 0, numTop = 0;

    printf("请输入表达式(以#号结束)：");
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
                while(op[opTop-1]!='('){//当前是'('，则op栈一定能有'('匹配到,即op栈一定不为空
                    calculate();
                }
                opTop--;//出栈，弹出左括号
                scanf("%c",&currentChar);
                break;
            default://currentChar为数字，则入num栈
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
    printf("计算结果是%d\n", result);
}
int main(){
    dealExpression();
}
