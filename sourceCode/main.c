#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>

void bubble_sort(float *iarr,int *rank, int num);


int main(void){
  int index; 
  clock_t start = clock(),diff;

  for (index=1;index<48;index++){
	FILE *fp;
	char fileNameAU1[99]="";
	char fileNameAU12[99]="";

	char fileNameAU17[99]="";
	char fileNameTemp[99]="";
    if(index<10){
	sprintf(fileNameAU1, "../data/00%d_AU01_query.dat", index);
	sprintf(fileNameAU12, "../data/00%d_AU12_query.dat", index);
	sprintf(fileNameAU17, "../data/00%d_AU17_query.dat", index);
	sprintf(fileNameTemp, "../data/00%d_template.dat", index);
    }else{
        sprintf(fileNameAU1, "../data/0%d_AU01_query.dat", index);
	sprintf(fileNameAU12, "../data/0%d_AU12_query.dat", index);
	sprintf(fileNameAU17, "../data/0%d_AU17_query.dat", index);
	sprintf(fileNameTemp, "../data/0%d_template.dat", index);
   
    }

	char buff[100000];
	char *line;
	line = (char *)malloc(1000000*sizeof(char));
	float *x1bar;
	float *x12bar;
	float *x17bar;
	x1bar = (float *)malloc(5633*(sizeof(float)));
	x12bar = (float *)malloc(5633*(sizeof(float)));
	x17bar = (float *)malloc(5633*(sizeof(float)));
	float *ybar[5633];
	int j;	
	for (j = 0; j < 139; j++){
		ybar[j] = (float *)malloc(5633*sizeof(float));
	}
//read file from AU1 and save it in x1bar
	fp = fopen(fileNameAU1, "r");
	int i1;
	for (i1=0;i1<5632;i1++){
		fscanf(fp, "%s", buff);
		x1bar[i1]=atof(buff);
	}
	fclose(fp);
//read file from AU12 and save it in x12bar
	fp = fopen(fileNameAU12, "r");
	int i12;
	for (i12=0;i12<5632;i12++){
		fscanf(fp, "%s", buff);
		x12bar[i12]=atof(buff);
	}
	fclose(fp);
//read file from AU17 and save it in x17bar
	fp = fopen(fileNameAU17, "r");
	int i17;
	for (i17=0;i17<5632;i17++){
		fscanf(fp, "%s", buff);
		x17bar[i17]=atof(buff);
	}
	fclose(fp);
//read file from corresponding template and save it in ybar
	fp = fopen(fileNameTemp,"r");
	int k=0;
	while (fgets(line,1000000,(FILE*)fp)){
		char *pch;
		int p = 0;
		pch = strtok(line," ");
		while(pch !=NULL){
			ybar[k][p]=atof(pch);
			pch = strtok(NULL," ");
			p++;
		}
		k++;
	}
	fclose(fp);

//implement of algorithm and find the 10 nearest one for AU1
	float *result1;
	result1 = (float *)malloc(139*(sizeof(float)));
	int l1,k1;
	float v1, v2, v3;
	for (l1=0;l1<138;l1++){
		v1=0;
		v2=0;
		v3=0;
		for (k1 = 0;k1<5632;k1++){
			v1 = v1+x1bar[k1]*ybar[l1][k1];
			v2 = v2 + x1bar[k1]*x1bar[k1];
			v3 = v3 + ybar[l1][k1]*ybar[l1][k1];
		}
		result1[l1]=v1/(sqrt(v2) * sqrt(v3));
	}
	//sort and return proper index
	int *sort1;
	sort1 = (int *)malloc(138*(sizeof(int)));
	int s1;
	for (s1=0;s1<138;s1++){
		sort1[s1]=s1;
	}

	bubble_sort(result1,sort1,138); 
	int max10;
	printf("\nThe 10 nearest neighbors for AU1 in pattern 0%d are \n",index);
	for (max10=137;max10>=128;max10--){
		printf("%d\t",sort1[max10]+1);
	}
//implement of algorithm and find the 10 nearest one for AU12
	float *result12;
	result12 = (float *)malloc(139*(sizeof(float)));
	int l12,k12;
	float v12, v22, v32;
	for (l12=0;l12<138;l12++){
		v12=0;
		v22=0;
		v32=0;
		for (k12 = 0;k12<5632;k12++){
			v12 = v12+x12bar[k12]*ybar[l12][k12];
			v22 = v22 + x12bar[k12]*x12bar[k12];
			v32 = v32 + ybar[l12][k12]*ybar[l12][k12];
		}
		result12[l12]=v12/(sqrt(v22) * sqrt(v32));
	}
	//sort and return proper index
	int *sort12;

	sort12 = (int *)malloc(138*(sizeof(int)));
	int s12;
	for (s12=0;s12<138;s12++){
		sort12[s12]=s12;
	}

	bubble_sort(result12,sort12,138); 
	int max102;
	printf("\nThe 10 nearest neighbors for AU12 in pattern 0%d are \n",index);
	for (max102=137;max102>=128;max102--){
		printf("%d\t",sort12[max102]+1);
	}
//implement of algorithm and find the 10 nearest one for AU17
	float *result17;
	result17 = (float *)malloc(139*(sizeof(float)));
	int l17,k17;
	float v17, v27, v37;
	for (l17=0;l17<138;l17++){
		v17=0;
		v27=0;
		v37=0;
		for (k17 = 0;k17<5632;k17++){
			v17 = v17+x17bar[k17]*ybar[l17][k17];
			v27 = v27 + x17bar[k17]*x17bar[k17];
			v37 = v37 + ybar[l17][k17]*ybar[l17][k17];
		}
		result17[l17]=v17/(sqrt(v27) * sqrt(v37));
	}
	//sort and return proper index
	int *sort17;
	sort17 = (int *)malloc(138*(sizeof(int)));
	int s17;
	for (s17=0;s17<138;s17++){
		sort17[s17]=s17;
	}
	bubble_sort(result17,sort17,138); 
	int max107;
	printf("\nThe 10 nearest neighbors for AU17 in pattern 0%d are \n",index);
	for (max107=137;max107>=128;max107--){
		printf("%d\t",sort17[max107]+1);
	}
//free the memory
	free(result1);
	free(result12);
	free(result17);
	free(sort12);
	free(sort17);
	free(sort1);
	free(x1bar);
	free(x12bar);
	free(x17bar);
	free(ybar[5633]);
  }





//clc the end time and convert to seconds and milliseconds
	diff=clock() - start;
	int msec = diff*1000/CLOCKS_PER_SEC;
	printf("\nTime taken %d seconds and %d milliseconds\n", msec/1000, msec%1000);
	return 0;
}
//bubble sort algorithm, swtich the index array at the same time swtich the sorting array
void bubble_sort(float *iarr,int *rank, int num){
	int i, j,tempRank;
	float temp;
	for (i = 1; i < num; i++) {
		for (j = 0; j < num - 1; j++) {
			if (iarr[j] > iarr[j + 1]) {
				temp = iarr[j];
				tempRank=rank[j];
				iarr[j] = iarr[j + 1];
				rank[j] = rank[j+1];
				iarr[j + 1] = temp;
				rank[j+1] = tempRank;
			}
		}

	}
	
}


