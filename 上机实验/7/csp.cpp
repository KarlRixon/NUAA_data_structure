#include<iostream>
#include<vector>
#include<utility>
#include<string.h>

using namespace std;

#define NMAX 10050
#define INF 0x3f3f3f3f

//图的最小生成树问题

int mincost[NMAX];
vector<pair<int,int> > G[NMAX];
bool visit[NMAX];
int n,m,total;

// 更新以u为起点的路径代价。
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
    // 所有代价初始化为最大值
    memset(mincost, INF, sizeof(mincost));

    // 在1节点处将一些代价更新。
    update(1);

    for(int i=1; i<n; i++)
    {
        // 在当前的路径代价中选择最小路径代价
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
