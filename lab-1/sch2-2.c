#include <stdio.h>

int time[1000]; //每台机器耗时
int tmp[1000][1000], result[1000][1000]; //solution
int cost[1000]; //每个任务的用时
int best = 100000; //全局最优解
int n, k; //n任务，k个机器
void assign (int n, int current); //dfs
int kmax (void);//所有机器的最大耗时
int main (void)
{
    scanf("%d%d", &n, &k);
    for (int i=0; i<n; ++i)
    {
        scanf("%d", &cost[i]);
    }

    for (int i=0; i<k; ++i)
    {
        time[i] = 0;
        for (int j=0; j<n; ++j)
        {
            tmp[i][j] = -1;
            result[i][j] = -1;
        }
    }
    assign(0, 0);

    for (int i=0; i<k ;++i)
    {
        printf("machine %d:", i);
        for (int j=0 ; j<n; ++j)
        {
            if(result[i][j] == -1)
            {
                break;
            }
            printf(" %d", result[i][j]);
        }
        printf("\n");
    }

    printf("%d\n", best);
    
}
void assign (int m, int current)
{
    if (m == n)
    {
        if (best > current)
        {
            best = current;
            for (int i=0; i<k; ++i)
            {
                int flag = 0;
                for (int j=0; j<n ; ++j)
                {
                    if (tmp[i][j] == -1)
                    {
                        flag = 1;
                    }
                    if (flag==0)
                    {
                        result[i][j] = tmp[i][j];
                    }
                    else
                    {
                        result[i][j] = -1;
                    }
                    
                    
                }
            }
        }
        return ;
    }
    if (current >= best)
    {
        return ;
    }

    for (int i=0; i<k; ++i)
    {
        int j;
        for (j=0; j<n; ++j)
        {
            if (tmp[i][j] == -1)
            {
                break;
            }
        }
        tmp[i][j] = m;
        time[i] += cost[m];

        assign(m+1, kmax());

        tmp[i][j] = -1;
        time[i] -= cost[m];
    }
}


int kmax (void)
{
    int max = 0;
    for (int i=0;i<k;++i)
    {
        max = (time[i]>max) ? time[i]: max;
    }
    return max;
}