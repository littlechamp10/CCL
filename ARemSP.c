						/*Experiments on Union-Find Algorithms for the Disjoint-Set Data Structure*/
						/*A New Two-Scan Algorithm for Labeling Connected Components in Binary Images*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int merge(int *,int, int);
void flatten(int *,int);
FILE *fp3;
int main()
{
	int row=0,chart=0,column=0;
	int num,i=0,j=0,count=1;
	int **image,**label,*p;
	FILE *fp,*fp1,*fp2;
	char ch,f_name[50];
	double time_spent,t1,t2;
	struct timespec tp,tp1;
	printf("Input file name: ");
	scanf("%s",f_name);
	fp = fopen(f_name,"r");
//	fp1 = fopen("Test_Output.txt","w");
//	fp2 = fopen("Test_Results.txt","a+");
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
	image = (int **)malloc(row * sizeof(int *));
	label = (int **)malloc(row * sizeof(int *));
	p = (int *)malloc(chart * sizeof(int *));
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
		image[i] =(int *) malloc(column * sizeof(int));
		label[i] =(int *) malloc(column * sizeof(int));
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
	p[0] = 0;
	fseek(fp,0,SEEK_SET);
	for(i=1;i<row-1;i++)
	{
		for(j=1;j<column-1;j++)
		{
			fscanf(fp,"%d",&num);
			image[i][j] = num;
		}
	}
	// Scaning Phase 
	clock_gettime(CLOCK_REALTIME,&tp);
	
	t1 = (((double)tp.tv_sec) * 1000000) + (((double)tp.tv_nsec) / 1000) ;
	
	for(i=1; i<(row-1); i=i+2)
	{
		//count = (i-1)*j + 1;
		for(j=1; j<(column-1); j++)
		{
			if(image[i][j] == 1)
			{
				if(image[i][j-1] == 0)
				{
					if(image[i-1][j] == 1)
					{
						label[i][j] = label[i-1][j];
						if(image[i+1][j-1] == 1)
							merge(p,label[i][j],label[i+1][j-1]);
					}
					else
					{
						if(image[i+1][j-1] == 1)
						{
							label[i][j] = label[i+1][j-1];
							if(image[i-1][j-1] == 1)
								merge(p,label[i][j],label[i-1][j-1]);
							if(image[i-1][j+1] == 1)
								merge(p,label[i][j],label[i-1][j+1]);
						}
						else
						{
							if(image[i-1][j-1] == 1)
							{
								label[i][j] = label[i-1][j-1];
								if(image[i-1][j+1] == 1)
									merge(p,label[i][j],label[i-1][j+1]);
							}
							else
							{
								if(image[i-1][j+1] == 1)
									label[i][j] = label[i-1][j+1];
								else
								{
									label[i][j] = count;
									p[count] = count;
									count++;	
								}
							}
						}
					}
				}
				else
				{
					label[i][j] = label[i][j-1];
					if(image[i-1][j] == 0)
					{
						if(image[i-1][j+1] == 1)
							merge(p,label[i][j],label[i-1][j+1]);
					}
				}
				if(image[i+1][j] == 1)
					label[i+1][j] = label[i][j];
			}
			else
			{
				if(image[i+1][j] == 1)
				{
					if(image[i][j-1] == 1)
						label[i+1][j] = label[i][j-1];
					else
					{
						if(image[i+1][j-1] == 1)
							label[i+1][j] = label[i+1][j-1];
						else
						{
							label[i+1][j] = count;
							p[count] = count;
							count++;
						}
					}
				}
			}
		}
	}
	
	count = count-1 ;
	
	clock_gettime(CLOCK_REALTIME,&tp1);
	t2 = (((double)tp1.tv_sec) * 1000000) + (((double)tp1.tv_nsec) / 1000) ;
	time_spent = t2 -t1;
//	fseek(fp2,0,SEEK_END);
//	fprintf(fp2,"%f\n",time_spent);
	printf("%f\n",time_spent);
	
	//analysis phase
	
	flatten(p,count);
	
	//labeling phase
	
	for(i=1;i<row;i++)
	{
		for(j=1;j<column;j++)
			label[i][j] = p[label[i][j]];
	}
	
	
	
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

int merge (int *p, int x, int y)
{
	int rootx,rooty,z;
	rootx = x;
	rooty = y;
	while( p[rootx] != p[rooty] )
	{
		if ( p[rootx] > p[rooty] )
		{
			if( rootx == p[rootx] )
			{
				p[rootx] = p[rooty];
				//break;
				return(p[rootx]);
			}
			z= p[rootx];
			p[rootx] = p[rooty];
			rootx = z;
		}
		else
		{
			if( rooty == p[rooty])
			{
				p[rooty] = p[rootx];
				//break;
				return(p[rootx]);
			}
			z = p[rooty];
			p[rooty] = p[rootx];
			rooty = z;
		}
	}
	return(p[rootx]);		
}

void flatten(int *p, int size)
{
	int k = 1,i;
	for(i=1;i <= size; i++)
	{
		//if(p[i] != 0)
		{
			if(p[i] < i)
				p[i] = p[p[i]];
			else
			{
				p[i] = k;
				k++;
			}
		}
	}
//	fseek(fp3,0,SEEK_END);
//	fprintf(fp3,"%d\n",k-1);
	printf("%d\n",k-1);
}
