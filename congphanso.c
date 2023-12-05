#include<stdio.h>
int a,b,c,d,ts,ms;
void nhapheso(){
	printf("Nhap a = ");
	scanf("%d",&a);
	printf("Nhap b = ");
	scanf("%d",&b);
	printf("Nhap c = ");
	scanf("%d",&c);
	printf("Nhap d = ");
	scanf("%d",&d);
}
void inphanso(){
	printf("%d/%d+%d/%d=?",a,b,c,d);
}
int ucln(int n1, int n2){
	int ucln;
	while(n1!=n2){
		if(n1>n2){
			n1=n2-n1;
		}
		else{
			n2=n2-n1;
		}
	}
	ucln=n1;
	return ucln;
}
int quydongmau(){
	int msc;
	msc=(b*d)/ucln(b,d);	
	return msc;
}
void tinhtong(){
ms=quydongmau();
ts=quydongmau()/b*a+quydongmau()/d*c;
printf("\ntong cua %d/%d + %d/%d = %d/%d ",a,b,c,d,ts,ms);
}
void toigian(){
	printf("\nphan so sau khi toi gian la:%d/%d",ts/ucln(ts,ms),ms/ucln(ts,ms));
	//printf("%d/%d",ts/ucln(ts,ms),ms/ucln(ts,ms));
}
int main(){
	nhapheso();
	inphanso();
    tinhtong();
	toigian();
	return 0;
}
