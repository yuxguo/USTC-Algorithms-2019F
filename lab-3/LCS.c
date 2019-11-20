#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define UP 0
#define LEFT 1
#define LEFTUP 2

typedef struct 
{
    int dir;
    int len;
}ELE;

ELE c[1000][1000];
void LCS(char *a, char *b);
int main(void)
{
    char a[1000], b[1000];
    scanf("%s",a);
    scanf("%s",b);
    for (int i=0;i<1000;++i)
    {
        for (int j=0;j<1000;++j)
        {
            c[i][j].len=0;
            c[i][j].dir = LEFT;
        }
    }
    LCS(a,b);
    return 0;
}
void LCS(char *a, char *b)
{
    int m = strlen(a);
    int n = strlen(b);
    for (int i=1;i<m+1;++i)
    {
        for (int j=1;j<n+1;++j)
        {
            if (a[i-1] == b[j-1])
            {
                c[i][j].len = c[i-1][j-1].len+1;
                c[i][j].dir = LEFTUP;
            }
            else
            {
                if (c[i-1][j].len > c[i][j-1].len)
                {
                    c[i][j].len = c[i-1][j].len;
                    c[i][j].dir = UP;
                }
                else
                {
                    c[i][j].len = c[i][j-1].len;
                    c[i][j].dir = LEFT;
                }
            }
        }
    }
    printf("%d\n", c[m][n].len);
    char *buf = (char *)malloc(sizeof(char)*(c[m][n].len+1));
    buf[c[m][n].len] = '\0';
    int i=m,j=n,k=c[m][n].len -1;
    while (i != 0 && j!= 0)
    {
        if (c[i][j].dir == LEFTUP)
        {
            buf[k] = a[i-1];
            i--;
            j--;
            k--;
        }
        else if (c[i][j].dir == LEFT)
        {
            j--;
        }
        else if (c[i][j].dir == UP)
        {
            i--;
        }
    }
    printf("%s",buf);
    free(buf);
}