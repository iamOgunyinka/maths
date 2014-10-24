#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void main()
{
int n,r,col[20],k;
permset()
{
	clrscr();
	printf("enter the value of n and r \n");
	scanf("%d%d",&n,&r);
	printf("\n\n");
	for(k=1;k<=n;k++)
		col[k]=k;
	k=1;
	perm(k);
}
perm(k)
{
	int i,j,temp;
	for(j=k;j<=n;j++)
	{
		temp=col[k];
		col[k]=col[j];
		col[j]=temp;
		if (k<r)
		{
			perm(k+);
		}
		else
		{
			for(i=r;i<=r;i++)
			{
				printf("%d\t",col[i]);
				if(i==r)
					printf("\n");
			}
		}
		temp=col[k];
		col[k]=col[j];
		col[j]=temp;
	}
}
}
