#include<stdio.h>
#include<stdlib.h>

typedef struct {
	float realpart;
	float imagpart;
}Complex;

void Init(Complex &a) {
	float imag = 0, real = 0;
	printf("�����鲿��");
	scanf("%f", &a.imagpart);
	printf("����ʵ����");
	scanf("%f", &a.realpart);
	return;
}
void Destroy(Complex &a) {
	a.imagpart = 0;
	a.realpart = 0;
	return;
}
float Getreal(Complex &a) {
	return a.realpart;
}
float Getimag(Complex &a) {
	return a.imagpart;
}
void Sum(Complex a, Complex b, Complex &sum) {
	sum.imagpart = a.imagpart + b.imagpart;
	sum.realpart = a.realpart + b.realpart;
	return;
}
void Tosum(Complex a){
	Complex b,sum;
	b.imagpart=sum.imagpart=0;
	b.realpart=sum.realpart=0;
	printf("������һ���������鲿��");
	scanf("%f",&b.imagpart);
	printf("������һ��������ʵ����");
	scanf("%f",&b.realpart);
	Sum(a,b,sum);
	printf("(%f+%fi)+(%f+%fi)=(%f+%fi)\n",a.realpart,a.imagpart,b.realpart,b.imagpart,sum.realpart,sum.realpart);
	return;
}

int main() {
	while(1){
		printf("���ܣ�\n");
		printf("----1.��ʼ������\n");
		printf("----2.����\n");
		printf("----3.��ӡֵ\n");
		printf("----4.�������\n");
		printf("----5.����\n");
		int n = 0;
		Complex a;
		scanf("%d", &n);
		//	printf("%d",n);
		//  Printimag(a);
		switch (n) {
		case 1:Init(a);break;
		case 2:Destroy(a);break;
		case 3:printf("%f + %fi\n",Getreal(a),Getimag(a));break;
		case 4:Tosum(a);break;
		case 5:system("cls");break;
		}
	}
}
