#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int min(int,int);
int min2(int,int,int);
int max(int *,int,int);
int max1(int *,int, int, int);
int max2(int *,int, int, int);

int main()
{
	int row=0,chart=0,column=0;
	int num,i=0,j=0,count=1,k;
	int check = -1;
	int **image,**label,*p;
	FILE *fp,*fp1,*fp2;
	char ch,f_name[50];
	double time_spent,t1,t2;
	struct timespec tp,tp1;
	printf("Input file name: ");
	scanf("%s",f_name);
	fp = fopen(f_name,"r");
//	fp1 = fopen("Test_Output.txt","w");
//	fp2 = fopen("Test_Results_2.txt","a+");
//	fp3 = fopen("Comp.txt","a+");
	while(fscanf(fp,"%d",&num) != EOF )
	{
		chart++;
	}
	fseek(fp,0,SEEK_SET);
	while((ch = fgetc(fp)) != EOF )
	{
		if(ch == '\n')
			row++;
	}
	column = chart/row ;
	row = row + 2;
	column = column +2;
	image = (int **)calloc(row, sizeof(int *));
	label = (int **)calloc(row, sizeof(int *));
	p = (int *)calloc(chart, sizeof(int));
	if(image == NULL)
	{
		fprintf(stderr, "out of memory\n");
		return(0);
	}
	if(label == NULL)
	{
		fprintf(stderr, "out of memory\n");
		return(0);
	}
	if(p == NULL)
	{
		fprintf(stderr, "out of memory\n");
		return(0);
	}
	for(i = 0; i < row; i++)
	{
		image[i] =(int *) calloc(column, sizeof(int));
		label[i] =(int *) calloc(column, sizeof(int));
		if(image[i] == NULL)
		{
			fprintf(stderr, "out of memory\n");
			return(0);
		}
		if(label[i] == NULL)
		{
			fprintf(stderr, "out of memory\n");
			return(0);
		}
	}
	fseek(fp,0,SEEK_SET);
	for(i=1;i<row-1;i++)
	{
		for(j=1;j<column-1;j++)
		{
			fscanf(fp,"%d",&num);
			image[i][j] = num;
		}
	}
	clock_gettime(CLOCK_REALTIME,&tp);
	
	t1 = (((double)tp.tv_sec) * 1000000) + (((double)tp.tv_nsec) / 1000) ;
	for(i=1;i<(row-1);i++)
	{
		for(j=1;j<(column-1);j++)
		{
			if(image[i][j] == 1)
			{
				if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
				{
					label[i][j] = count;
					p[count] = count;
					count++;
				}
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					label[i][j] = p[label[i][j-1]];
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					label[i][j] = p[label[i-1][j+1]];				
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
				{
					label[i][j] = min(p[label[i-1][j+1]],p[label[i][j-1]]);
					p[max(p,label[i-1][j+1],label[i][j-1])] = label[i][j];
				}
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
					label[i][j] = p[label[i-1][j]];
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					label[i][j] = p[label[i-1][j]];
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					label[i][j] = p[label[i-1][j+1]];
				else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
				{
					label[i][j] = min(p[label[i-1][j+1]],p[label[i][j-1]]);
					p[max(p,label[i-1][j+1],label[i][j-1])] = label[i][j];
				}
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
					label[i][j] = p[label[i-1][j-1]];
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					label[i][j] = p[label[i][j-1]];
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
				{
					label[i][j] = min(p[label[i-1][j-1]],p[label[i-1][j+1]]);
					p[max(p,label[i-1][j-1],label[i-1][j+1])] = label[i][j];
				}
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
				{	
					label[i][j] = min(p[label[i-1][j+1]],p[label[i][j-1]]);
					p[max(p,label[i-1][j+1],label[i][j-1])] = label[i][j];
				}
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
					label[i][j] = p[label[i-1][j]];
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					label[i][j] = p[label[i][j-1]];
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					label[i][j] = p[label[i-1][j+1]];
				else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
				{
					label[i][j] = min(p[label[i-1][j+1]],p[label[i][j-1]]);
					p[max(p,label[i-1][j+1],label[i][j-1])] = label[i][j];
				}
			}
		}
	}
		
	while(1)
	{
		for(i=1;i<(row-1);i++)
		{
			for(j=1;j<(column-1);j++)
			{
				if(image[i][j] == 1)
				{
					if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
						label[i][j] = p[label[i][j]];
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j-1]]);
						p[max(p,label[i][j],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i-1][j+1]]);
						p[max(p,label[i][j],label[i-1][j+1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i-1][j+1]],p[label[i][j-1]]);
						p[max1(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
						p[max2(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i-1][j]]);
						p[max(p,label[i][j],label[i-1][j])] = label[i][j];
					}
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j-1]]);
						p[max(p,label[i][j],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i-1][j+1]]);
						p[max(p,label[i][j],label[i-1][j+1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 0)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i-1][j+1]],p[label[i][j-1]]);
						p[max1(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
						p[max2(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i-1][j-1]]);
						p[max(p,label[i][j],label[i-1][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j-1]]);
						p[max(p,label[i][j],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i-1][j-1]],p[label[i-1][j+1]]);
						p[max1(p,label[i][j],label[i-1][j-1],label[i-1][j+1])] = label[i][j];
						p[max2(p,label[i][j],label[i-1][j-1],label[i-1][j+1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 0)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i-1][j+1]],p[label[i][j-1]]);
						p[max1(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
						p[max2(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i-1][j]]);
						p[max(p,label[i][j],label[i-1][j])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 0)&&(image[i][j-1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j-1]]);
						p[max(p,label[i][j],label[i][j-1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i-1][j+1]]);
						p[max(p,label[i][j],label[i-1][j+1])] = label[i][j];
					}
					else if((image[i-1][j-1] == 1)&&(image[i-1][j] == 1)&&(image[i-1][j+1] == 1)&&(image[i][j-1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i-1][j+1]],p[label[i][j-1]]);
						p[max1(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
						p[max2(p,label[i][j],label[i-1][j+1],label[i][j-1])] = label[i][j];
					}
					if((image[i-1][j-1] != 0) && (label[i-1][j-1] != label[i][j]))
						check = 1;
					else if((image[i-1][j] != 0) && (label[i-1][j] != label[i][j]))
						check = 1;
					else if((image[i-1][j+1] != 0) && (label[i-1][j+1] != label[i][j]))
						check = 1;
					else if((image[i][j-1] != 0) && (label[i][j-1] != label[i][j]))
						check = 1;
				}
			}
		}
		if(check == -1 )
			break;
		check = -1;
		
		for(i=(row-2);i>0;i--)
		{
			for(j=(column-2);j>0;j--)
			{
				if(image[i][j] == 1)
				{
					if((image[i+1][j+1] == 0)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 0))
						label[i][j] = p[label[i][j]];
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j+1]]);
						p[max(p,label[i][j],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i+1][j-1]]);
						p[max(p,label[i][j],label[i+1][j-1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i+1][j-1]],p[label[i][j+1]]);
						p[max1(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
						p[max2(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i+1][j]]);
						p[max(p,label[i][j],label[i+1][j])] = label[i][j];
					}
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j+1]]);
						p[max(p,label[i][j],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i+1][j-1]]);
						p[max(p,label[i][j],label[i+1][j-1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 0)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i+1][j-1]],p[label[i][j+1]]);
						p[max1(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
						p[max2(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i+1][j+1]]);
						p[max(p,label[i][j],label[i+1][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j+1]]);
						p[max(p,label[i][j],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 0))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i+1][j+1]],p[label[i+1][j-1]]);
						p[max1(p,label[i][j],label[i+1][j+1],label[i+1][j-1])] = label[i][j];
						p[max2(p,label[i][j],label[i+1][j+1],label[i+1][j-1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 0)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i+1][j-1]],p[label[i][j+1]]);
						p[max1(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
						p[max2(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i+1][j]]);
						p[max(p,label[i][j],label[i+1][j])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 0)&&(image[i][j+1] == 1))
					{
						label[i][j] = min(p[label[i][j]],p[label[i][j+1]]);
						p[max(p,label[i][j],label[i][j+1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 0))
					{
						label[i][j] = min(p[label[i][j]],p[label[i+1][j-1]]);
						p[max(p,label[i][j],label[i+1][j-1])] = label[i][j];
					}
					else if((image[i+1][j+1] == 1)&&(image[i+1][j] == 1)&&(image[i+1][j-1] == 1)&&(image[i][j+1] == 1))
					{
						label[i][j] = min2(p[label[i][j]],p[label[i+1][j-1]],p[label[i][j+1]]);
						p[max1(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
						p[max2(p,label[i][j],label[i+1][j-1],label[i][j+1])] = label[i][j];
					}
					if((image[i+1][j+1] != 0) && (label[i+1][j+1] != label[i][j]))
						check = 1;
					else if((image[i+1][j] != 0) && (label[i+1][j] != label[i][j]))
						check = 1;
					else if((image[i+1][j-1] != 0) && (label[i+1][j-1] != label[i][j]))
						check = 1;
					else if((image[i][j+1] != 0) && (label[i][j+1] != label[i][j]))
						check = 1;
				}
			}
		}
		if(check == -1 )
			break;
		check = -1;
	}
	
	clock_gettime(CLOCK_REALTIME,&tp1);
	t2 = (((double)tp1.tv_sec) * 1000000) + (((double)tp1.tv_nsec) / 1000) ;
	time_spent = t2 -t1;
	printf("%f\n",time_spent);
//	fseek(fp2,0,SEEK_END);
//	fprintf(fp2,"%f\n",time_spent);
	
	k = 0;
	for(i=1;i <= count; i++)
	{
		if(p[i] == i)
		{
			k++;;
		}
	}
	printf("%d\n",k);
	/*	for(i = 1; i< row-1; i++)
	{
		for(j=1;j<column-1;j++)
			fprintf(fp1,"%d ",label[i][j]);
		fprintf(fp1,"\n");
	}
*/
	fclose(fp);
//	fclose(fp1);
//	fclose(fp2);
	return(0);
}

int min(int x,int y)
{
	if(x<=y)	
		return(x);
	else
		return(y);
}

int min2(int x,int y,int z)
{
	if((x<=y) && (x<=z))
		return(x);
	else if((y<=z) && (y<=x))
	 	return(y);
	else if((z<=y) && (z<=x))
		return(z);
}

int max(int *p,int x,int y)
{
	if(p[x] >= p[y])
		return(x);
	else
		return(y);
}

int max1(int *p,int x,int y,int z)
{
	if((p[x]>=p[y]) &&(p[x]>=p[z]))
		return(x);
	else if((p[y]>=p[z]) &&(p[y]>=p[x]))
		return(y);
	else if((p[z]>=p[x]) &&(p[z]>=p[y]))
		return(z); 
}

int max2(int *p,int x,int y,int z)
{
	if(((p[x]>=p[y]) && (p[x]<=p[z])) ||((p[x]>=p[z]) && (p[x]<=p[y])))
		return(x);
	else if(((p[y]>=p[x]) && (p[y]<=p[z])) || ((p[y]>=p[z]) && (p[y]<=p[x])))
		return(y);
	else if(((p[z]>=p[x]) && (p[z]<=p[y])) || ((p[z]>=p[y]) && (p[z]<=p[x])))
		return(z);
}
