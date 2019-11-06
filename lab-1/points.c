#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

typedef struct
{
    double x,y;
}Point;

Point *points;
int my_cmp_x (const void *a, const void *b);//排成递增
int my_cmp_y (const void *a, const void *b);//排成递减
void closet_points (int i, int j, Point *a, Point *b, double *minum_distance);// [i,j) in index_x
double Distance (const Point a, const Point b);
double my_min (const double a, const double b);

int main (void)
{
    int n;
    scanf("%d", &n);
    points = (Point *)malloc(n*sizeof(Point));
    for (int i=0; i<n; ++i)
    {
        scanf("%lf%lf", &(points[i].x), &(points[i].y));
    }
    qsort(points, n, sizeof(Point), my_cmp_x);

    Point a,b;
    double min_distance;

    closet_points(0, n, &a, &b, &min_distance);

    printf("a: (%lf, %lf) , b: (%lf, %lf) , min= %lf\n", a.x, a.y, b.x, b.y, min_distance);
    // after qsort
    free(points);
    return 0;
}
int my_cmp_x (const void *a, const void *b)
{
    return ((((Point *)a)->x) > (((Point *)b)->x)) ? 1 : -1;
}
int my_cmp_y (const void *a, const void *b)
{
    return ((((Point *)b)->y) > (((Point *)a)->y)) ? 1 : -1;
}
void closet_points(int i, int j, Point *a, Point *b, double *minum_distance)
{
    if (j-i <= 3)
    {
        *a = points[i];
        *b = points[j-1];
        *minum_distance = Distance(*a, *b);

        if (j-i == 3)
        {
            for (int k=i; k<j-1; ++k)
            {
                double tmp = Distance(points[k], points[k+1]);
                if (tmp < (*minum_distance))
                {
                    *minum_distance = tmp;
                    *a = points[k];
                    *b = points[k+1];
                }
            }
        }
        qsort ((points+i), (j-i), sizeof(Point), my_cmp_y);
        return ;
    }

    int divide = (i + j)/2;
    double x_middle = points[divide].x;
    Point l_a, l_b;
    double l_min;
    closet_points(i, divide, &l_a, &l_b, &l_min);

    Point r_a, r_b;
    double r_min;
    closet_points(divide, j, &r_a, &r_b, &r_min);

    //begin merge
    Point *tmp = (Point *)malloc(sizeof(Point)*(j-i));
    int lcount = 0, lsize = divide-i;
    int rcount = 0, rsize = j-divide;
    int t = 0;
    while ((lcount < lsize) && (rcount < rsize))
    {
        if (points[i+lcount].y > points[divide+rcount].y)
        {
            tmp[t] = points[i+lcount];
            lcount++;
        }
        else
        {
            tmp[t] = points[divide+rcount];
            rcount++;
        }
        t++;
    }
    while (lcount < lsize)
    {
        tmp[t] = points[i+lcount];
        lcount++;
        t++;
    }
    while (rcount < rsize)
    {
        tmp[t] = points[divide+rcount];
        rcount++;
        t++;
    }

    for (int k=0; k<j-i;++k)
    {
        points[i+k] = tmp[k];
    }

    double h = my_min(l_min, r_min);
    *a = (l_min<r_min)?l_a:r_a;
    *b = (l_min<r_min)?l_b:r_b;
    *minum_distance = h;
    
    int cnt = 0;
     
    for (int k=0; k<j-i; ++k)
    {
        if (fabs(x_middle-tmp[k].x)>h)
        {
            continue;
        }
        tmp[cnt] = tmp[k];
        cnt++;
    }

    
    
    if (cnt>1)
    {
        Point m_a, m_b;
        m_a = tmp[0];
        m_b = tmp[1];
        double m_min=Distance(tmp[0], tmp[1]);
        for (int k=0; k<cnt-1; ++k)
        {
            for (int k1=k+1; k1<cnt; k1++)
            {
                if (tmp[k].y-tmp[k1].y>=h)
                {
                    break;
                }
                if (m_min>Distance(tmp[k], tmp[k1]))
                {
                    m_a = tmp[k];
                    m_b = tmp[k1];
                    m_min = Distance(tmp[k], tmp[k1]);
                }
            }
        }
        
        *minum_distance = my_min(m_min, h);
        *a = (m_min<h)?m_a:(*a);
        *b = (m_min<h)?m_b:(*b);
    }
    return ;
}
double Distance (const Point a, const Point b)
{
    double result = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    return sqrt(result);
}
double my_min (const double a, const double b)
{
    return (a<b)?a:b; 
}