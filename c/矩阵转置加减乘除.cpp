#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
const int MAXSIZE=100;    // �������Ԫ�صĶԶ����
const int MAXROW=10; // ������������������ֵ
typedef struct {          // ������Ԫ���Ԫ��
 int i,j;
 int e;
}Triple;
typedef struct {         // ������ͨ��Ԫ�����
 Triple data[MAXSIZE+1];
 int mu,nu,tu;
}TSMatrix;
typedef struct {       // �����������Ϣ����Ԫ�����
 Triple data[MAXSIZE+2];
 int rpos[MAXROW+1];
 int mu,nu,tu;
}RLSMatrix;
template <class P>
bool InPutTSMatrix(P & T,int y){     //������󣬰���Ԫ���ʽ����
 cout<<"���������У��кͷ���Ԫ�ظ���:"<<endl;
 cin>>T.mu>>T.nu>>T.tu;
 cout<<"���������Ԫ�ص�λ�ú�ֵ:"<<endl;
 int k=1;
 for(;k<=T.tu;k++)
  cin>>T.data[k].i>>T.data[k].j>>T.data[k].e;
 
 return true;
}
template <class P>
bool OutPutSMatrix(P T){       // ������󣬰���׼��ʽ���
 int m,n,k=1;
 for(m=0;m<T.mu;m++){
  for(n=0;n<T.nu;n++){
   if((T.data[k].i-1)==m&&(T.data[k].j-1)==n){
                cout.width(4);
    cout<<T.data[k++].e;}
   else{
    cout.width(4);  cout<<"0"; }
  }
  cout<<endl;
 }
 return true;
}
// ������ת�þ���
bool TransposeSMatrix( ){     
 TSMatrix M,T;    //����Ԥת�õľ���
 InPutTSMatrix(M, 0);    //�������
 int num[MAXROW+1];
 int cpot[MAXROW+1];      //   ������������
 int q,p,t;   
 T.tu=M.tu;   T.mu=M.nu;   T.nu=M.mu;
 if(T.tu){
  for(int col=1;col<=M.nu;col++)    num[col]=0;
  for(t=1;t<=M.tu;t++)    ++num[M.data[t].j];
  cpot[1]=1;
  for(int i=2;i<=M.nu;i++)    cpot[i]=cpot[i-1]+num[i-1];    //   ���ÿһ���з���Ԫ������Ԫ���г��ֵ�λ��
  for(p=1;p<=M.tu;p++){
   int col=M.data[p].j;     q=cpot[col];
   T.data[q].i=col;     T.data[q].j=M.data[p].i;
   T.data[q].e=M.data[p].e;    ++cpot[col];
  }
 }
 cout<<"��������ת�þ���Ϊ"<<endl;
 OutPutSMatrix(T);
 return true;
}

bool Count(RLSMatrix &T)
{
 int num[MAXROW+1];
 for(int col=1;col<=T.mu;col++)    num[col]=0;               
 for(int col=1;col<=T.tu;col++)    ++num[T.data[col].i];
 T.rpos[1]=1;
 for(int i=2;i<=T.mu;i++)    T.rpos[i]=T.rpos[i-1]+num[i-1];    // ��ȡÿһ���з���Ԫ������Ԫ���г��ֵ�λ��
 
 return true;
}
// �����������
bool MultSMatrix ( ){   
 RLSMatrix M,N,Q;  // ������������������Ϣ������Ԫ���ʾ������
 InPutTSMatrix(M,1);  //  ����ͨ��Ԫ����ʽ��������
 InPutTSMatrix(N,1);
 Count(M);   Count(N);
 if(M.nu!=N.mu)    return false;
 Q.mu=M.mu;    Q.nu=N.nu;   Q.tu=0;   //     Q��ʼ��
 int ctemp[MAXROW+1];            //    ��������
 int arow,tp,p,brow,t,q,ccol;
 if(M.tu*N.tu){            //  Q�Ƿ������
  for( arow=1;arow<=M.mu;arow++){
   ///memset(ctemp,0,N.nu);
   for(int x=1;x<=N.nu;x++)      // ��ǰ�и�Ԫ���ۼ�������
    ctemp[x]=0;
   Q.rpos[arow]=Q.tu+1;         //  ��ǰ�е��׸�����Ԫ������Ԫ���е�λ��Ϊ����ǰ���з���Ԫ��+1
   if(arow<M.mu)    tp=M.rpos[arow+1];
   else   tp=M.tu+1;
   for(p=M.rpos[arow];p<tp;p++){     //   �Ե�ǰ��ÿ������Ԫ�ؽ��в���
    
    brow=M.data[p].j;            //  ��N���ҵ�iֵҲ����Ԫ�ص�jֵ��ȵ���
    if(brow<N.mu)    t=N.rpos[brow+1];
    else    t=N.tu+1;
    for(q=N.rpos[brow];q<t;q++){      //  ���ҳ����е�ÿ������Ԫ�ؽ��в���
     
     ccol=N.data[q].j;
     ctemp[ccol] += M.data[p].e*N.data[q].e;    //    ���˵õ���Ӧֵ������Ӧ��Ԫ���ۼ�������
    }
   }
   for(ccol=1;ccol<=Q.nu;ccol++)        //   ���Ѿ�������ۼ����е�ֵѹ����Q��
    if(ctemp[ccol]){
     if(++Q.tu>MAXSIZE)   return false;
     Q.data[Q.tu].e=ctemp[ccol];
     Q.data[Q.tu].i=arow;
     Q.data[Q.tu].j=ccol;
    }
  }
 }
 OutPutSMatrix(Q);
 return true;
}
typedef struct OLNode{   // ����ʮ������Ԫ��
 int i,j;
 int e;
 struct OLNode *right,*down;  //  �÷���Ԫ�����б���б�ĺ��Ԫ��
}OLNode,*OLink;
typedef struct{            //   ����ʮ���������ṹ��
 OLink *rhead,*chead;        
 int mu,nu,tu;          //   ϵ��������������������ͷ���Ԫ�ظ���
}CrossList;
bool CreateSMatrix_OL(CrossList & M){          //   ����ʮ������
 int x,y,m;
 
 cout<<"�����������У��У�������Ԫ�ظ���"<<endl;
 cin>>M.mu>>M.nu>>M.tu;
 if(!(M.rhead=(OLink*)malloc((M.mu+1)*sizeof(OLink))))    exit(0);
 if(!(M.chead=(OLink*)malloc((M.nu+1)*sizeof(OLink))))    exit(0);
 for(x=0;x<=M.mu;x++)
  M.rhead[x]=NULL;       // ��ʼ�����У���ͷָ�룬�ֱ�ΪNULL
 for(x=0;x<=M.nu;x++)
  M.chead[x]=NULL;
 cout<<"�밴��Ԫ��ĸ�ʽ�������飺"<<endl;
 for(int i=1;i<=M.tu;i++){
  cin>>x>>y>>m;      //  ������˳���������Ԫ������ͨ��Ԫ����ʽ���룩
  OLink p,q;
  if(!(p=(OLink)malloc(sizeof(OLNode))))      exit(0);    // �����½ڵ㣬�����洢�������Ԫ��
  p->i=x;   p->j=y;    p->e=m;
  if(M.rhead[x]==NULL||M.rhead[x]->j>y){
   p->right=M.rhead[x];     M.rhead[x]=p;                  
  }
  else{                                
   for(q=M.rhead[x];(q->right)&&(q->right->j<y);q=q->right);        //   ���ҽڵ����б��еĲ���λ��
   p->right=q->right;      q->right=p;     //   ����в���
  }
  if(M.chead[y]==NULL||M.chead[y]->i>x){
   p->down=M.chead[y];       M.chead[y]=p;
  }
  else{
   for(q=M.chead[y];(q->down)&&(q->down->i<x);q=q->down);    //       ���ҽڵ����б��еĲ���λ��
   p->down=q->down;        q->down=p;                      //  ����в���
   
  }
 }
 return true;
}
bool OutPutSMatrix_OL(CrossList T){                //  ���ʮ����������ͨ������ʽ���
 for(int i=1;i<=T.mu;i++){
  OLink p=T.rhead[i];
  for(int j=1;j<=T.nu;j++){
   if((p)&&(j==p->j)){
    cout<<setw(3)<<p->e;     p=p->right;
   }
   else
    cout<<setw(3)<<"0";
  }
  cout<<endl;
 }
 return true;
}

//����ļӷ�
bool AddSMatrix(){
 CrossList M,N;          //  ��������ʮ��������󣬲���ʼ��
 CreateSMatrix_OL(M);
 CreateSMatrix_OL(N);
 cout<<"�����������ĺ;���Ϊ��"<<endl;
 OLink pa,pb,pre ,hl[MAXROW+1];            //���帨��ָ�룬pa��pb�ֱ�ΪM,N��ǰ�Ƚϵ�Ԫ�أ�preΪpa��ǰ��Ԫ��
 for(int x=1;x<=M.nu;x++)    hl[x]=M.chead[x];
 for(int k=1;k<=M.mu;k++){              // ��M��ÿһ�н��в���
  pa=M.rhead[k];   pb=N.rhead[k];    pre=NULL;
  while(pb){                        // ��N�д��е�ÿ��Ԫ��ȡ����
   OLink p;
   if(!(p=(OLink)malloc(sizeof(OLNode))))   exit(0);       //  �����½ڵ㣬�洢N��ȡ����Ԫ��
   p->e=pb->e;    p->i=pb->i;     p->j=pb->j;
   if(NULL==pa||pa->j>pb->j){            //  ��M�����Ѿ���������pb��÷���paǰ��
    
    if(NULL==pre)
     M.rhead[p->i]=p;
    else
     pre->right=p;
    p->right=pa;     pre=p;
    if(NULL==M.chead[p->j]){          // �����в���
     M.chead[p->j]=p;   p->down=NULL;
    }
    else{
     p->down=hl[p->j]->down;   hl[p->j]->down=p;
    }
    hl[p->j]=p;
    pb=pb->right;
   }
   else
    if((NULL!=pa)&&pa->j<pb->j){           //  �����ʱ��pbԪ����÷���pa���棬��ȡ�Ժ��pa�����Ƚ�
     pre=pa;        pa=pa->right;
    }
    else
     if(pa->j==pb->j){           // ���pa��pbλ��ͬһ��λ���ϣ���ֵ���
      pa->e += pb->e;
         if(!pa->e){                   // �����Ӻ�ĺ�Ϊ0����ɾ���˽ڵ㣬ͬʱ�ı��Ԫ�������У��е�ǰ��Ԫ�ص���Ӧֵ    
       if(NULL==pre)               // �޸���ǰ��Ԫ��ֵ
        M.rhead[pa->i]=pa->right;
       else
        pre->right=pa->right;
       p=pa;    pa=pa->right;
       if(M.chead[p->j]==p)   M.chead[p->j]=hl[p->j]=p->down;    // �޸���ǰ��Ԫ��ֵ
       else
        hl[p->j]->down=p->down;
       free(p);    pb=pb->right;
      }
      else{
       pa=pa->right;   pb=pb->right;
      }
     }
     
  }
 }
 OutPutSMatrix_OL(M);
 return true;
}
int main(){
    cout.fill('*');
 cout<<setw(80)<<'*';
 cout.fill(' ');
  system("color 0C");
 cout<<setw(50)<<"***��ӭʹ�þ����������***"<<endl;                    //���ͷ�˵�
 cout.fill('*');
 cout<<setw(80)<<'*';
 cout.fill(' ');   
 cout<<"��ѡ��Ҫ���еĲ�����"<<endl;
 cout<<"1:�����ת�á�"<<endl;
 cout<<"2:����ļӣ���������"<<endl;
 cout<<"3:����ĳ˷���"<<endl;
 cout<<"4:�Ƴ�����"<<endl;
 char c=getchar();
 if(c=='1')
  TransposeSMatrix( );     //���þ���ת�ú���
 else
  if(c=='2')
   AddSMatrix();        //���þ�����Ӻ���
  else
   if(c=='3')
    MultSMatrix ();  //���þ�����˺���
   else
    exit(0);         //�˳�
   return 0;
}
