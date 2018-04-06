#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max(a,b) a>b?a:b;
#define min(a,b) a>b?b:a;
int **g;
int *ind;
int *toposort;
int *ve,*vl;
int *ee,*el;

void init(int vn,int en)
{
    g = (int **)malloc(en*sizeof(int *));
    ind = (int *)malloc(vn*sizeof(int));
    toposort = (int *)malloc(vn*sizeof(int));
    ve = (int *)malloc(vn*sizeof(int));
    vl = (int *)malloc(vn*sizeof(int));
    ee = (int *)malloc(en*sizeof(int));
    el = (int *)malloc(en*sizeof(int));
    for(int i=0;i<en;++i)
    {
        g[i] = (int *)malloc(3*sizeof(int));
    }
    for(int i=0;i<vn;++i)
    {
        ind[i] = 0;
    }
}
void edge(int vn)
{
    int a,b,w;
    for(int i=0;i<vn;++i)
    {
        scanf("%d%d%d",&a,&b,&w);
        --a;
        --b;
        g[i][0] = a;
        g[i][1] = b;
        g[i][2] = w;
        ++ind[b];
    }
}
void Toposort(int vn,int en)
{
    int num = 0;
    for(int i=0;i<vn;i++)
    {
        if(ind[i]==0)
        {
            toposort[num++] = i;
        }
    }
    for(int i=0;i<num;++i)
    {
        int Head = toposort[i];
        for(int j=0;j<en;j++)
        {
            int Fail = g[j][1];
            if(g[j][0] == Head && ind[Fail]>0)
            {
                ind[Fail]--;
                if(ind[Fail]==0)
                {
                    toposort[num++] = Fail;
                }
            }
        }
    }
}
void Time(int vn,int en)
{
    int i,j;
    int from,to;
    for(i=0;i<vn;i++)
    {
        ve[i] = 0;
    }
    for(i=0;i<vn;i++)
    {
        from = toposort[i];
        for(j=0;j<en;j++)
        {
            if(g[j][0] == from)
            {
                to = g[j][1];
                ve[to] = max(ve[to] , ve[from] + g[j][2]);
            }
        }
    }

    for(i=0;i<vn;i++)
    {
        vl[i] =  ve[vn-1];
    }
    for(i=vn-1;i>=0;--i)
    {
        to = toposort[i];
        for(j=0;j<en;j++)
        {
            if(g[j][1] == to)
            {
                from = g[j][0];
                vl[from] = min(vl[from] , vl[to] - g[j][2]);
            }
        }
    }

    for(i=0;i<en;i++)
    {
        ee[i] = ve[g[i][0]];
    }

    for(i=0;i<en;i++)
    {
        el[i] = vl[g[i][1]] - g[i][2];
    }
}
void print(int en)
{
    printf("guanjianlujing£º");
    int i;
    for(i=0;i<en;++i)
    {
        if(ee[i]==el[i])
        {
            printf("%d",i+1);
            break;
        }
    }
    for(++i;i<en;++i)
    {
        if(ee[i]==el[i])
        {
            printf(",%d",i+1);
        }
    }
    printf("\n\n");
}
int main()
{
    int vn,en;
    printf("dian£º");
    scanf("%d",&vn);
    printf("bian£º");
    scanf("%d",&en);
    init(vn,en);
    edge(en);
    Toposort(vn,en);
    Time(vn,en);
    print(en);
    return 0;
}
