#include<iostream>
#include<vector>
#include<utility>
#include<string.h>

using namespace std;

#define NMAX 10050
#define INF 0x3f3f3f3f

//ͼ����С����������

int mincost[NMAX];
vector<pair<int,int> > G[NMAX];
bool visit[NMAX];
int n,m,total;

// ������uΪ����·�����ۡ�
void update(int u){
    int len = G[u].size();
    for(int i=0; i<len; i++){
        pair<int,int> line = G[u][i];
        if(!visit[line.first] && mincost[line.first]>line.second){
            mincost[line.first] = line.second;
        }
    }
}

void prime(int u)
{

    visit[u]=1;
    // ���д��۳�ʼ��Ϊ���ֵ
    memset(mincost, INF, sizeof(mincost));

    // ��1�ڵ㴦��һЩ���۸��¡�
    update(1);

    for(int i=1; i<n; i++)
    {
        // �ڵ�ǰ��·��������ѡ����С·������
        int pos,cost=INF;
        for(int j=1; j<=n; j++){
            if(!visit[j] && mincost[j]<cost){
                cost = mincost[j];
                pos = j;
            }
        }
        total += cost;
        visit[pos] = 1;
        update(pos);
    }

}
int main()
{
    cin>>n>>m;

    int u,v,c;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v>>c;
        G[u].push_back(make_pair(v,c));
        G[v].push_back(make_pair(u,c));
    }
    prime(1);
    cout<<total;

    return 0;
}
