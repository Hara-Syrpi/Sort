#include <stdio.h>
#include <stdlib.h> 

#define swap(a,b) {temp=(a); (a)=(b); (b)=temp;}

#define TRUE 1
#define FALSE 0

int *newarray(int n);

void display(int *arr, int n);
void insertsort(int *arr, int n);
void bubblesort(int *arr, int n);
void selectsort(int *arr, int n);
void shellsort(int *arr, int n);
void quicksort(int *arr, int start, int end, int n);
void mergesort(int *arr, int start, int end, int n);
void merge(int *arr, int start, int middle, int end, int n);

int main(void)
{
	int *p, *q, i, len, opt;

	printf("Give the number of integers you want to sort: ");
	scanf("%d",&len);

	p = newarray(len); /* create array dynamically */
	q = newarray(len); /* backup */

	printf("Give the integers you want to sort: ");

	for(i = 0; i < len; i++) scanf("%d",&q[i]);
	for(;;)
    {
		printf("\n\t1. Insertion Sort\n");
		printf("\t2. Bubble Sort\n");
		printf("\t3. Selection Sort\n");
		printf("\t4. Shell Sort\n");
		printf("\t5. Quick Sort\n");
		printf("\t6. Merge Sort\n");
		printf("\t7. Exit\n\n");
		printf("Please Select: ");
		scanf("%d",&opt);

		if(opt == 7) break;

		for(i = 0; i < len; i++) p[i]=q[i];
		printf("\n"); display(p,len); printf("\n\n");

		switch(opt)
		{
			case 1:
				insertsort(p,len); break;
			case 2:
				bubblesort(p,len); break;
			case 3:
				selectsort(p,len); break;
			case 4:
				shellsort(p,len); break;
			case 5:
				quicksort(p,0,len-1,len); break;
			case 6:
				mergesort(p,0,len-1,len); break;
			default:
				printf("Wrong Input!\n");
		}
	}

	free(p); free(q);
	return 0;
}

/* -------------------------------------------------------------- */

int *newarray(int n)
{
	int *p;
	/* allocate memory using malloc */
	p = (int *)malloc(sizeof(n));
	if(p==NULL){
		fprintf(stderr,"Out of memory!\n");
		exit(1);
	}
	return p;
}

/* -------------------------------------------------------------- */

void display(int *arr, int n)
{
	int i;
	for(i=0; i<n; i++) printf("\t%d", arr[i]);
	while(getchar()!='\n'); /* wait new line */
}

/* -------------------------------------------------------------- */

void insertsort(int *arr, int n)
{
	int i, j, a;
	for(j=1; j<n; j++){
		a = arr[j];
		i=j-1;
		while(i>-1 && arr[i]>a){
			arr[i+1]=arr[i];
			i--;
		}
		arr[i+1]=a;
		display(arr,n);
	}
}

/* -------------------------------------------------------------- */

void bubblesort(int *arr, int n)
{
	int i, j, temp, done=FALSE;

	for(i=1; i<n; i++){
		if(done) break;
		done=TRUE;
		for(j=n-1; j>=i; j--) {
			if(arr[j-1]>arr[j]){
				swap(arr[j],arr[j-1]);
				done=FALSE;
			}
		}
		display(arr,n);
	}
}

/* -------------------------------------------------------------- */

void selectsort(int *arr, int n)
{
	int i, j, k, temp;

	for(i=0; i<n-1; i++){
		k=i;
		for(j=i+1; j<n; j++)
			if(arr[k]>arr[j]) k=j;
		if(k!=i) swap(arr[k],arr[i]);
		display(arr,n);
	}
}

/* -------------------------------------------------------------- */

void shellsort(int *arr, int n)
{
	int i,j,incr,temp;

	for(incr=n/2; incr>0; incr/=2){
		for(i=incr; i<n; i++){
			j=i-incr;
			while(j>-1){
				if(arr[j]>arr[j+incr]){
					swap(arr[j],arr[j+incr]);
					j=j-incr;
				} else j=-1;
			}
		}
		display(arr,n);
	}
}

/* -------------------------------------------------------------- */

void quicksort(int *arr, int start, int end, int n)
{
	int leftmost, rightmost, pivot, temp;

	if(start<end){
		pivot=start;
		leftmost=start;
		rightmost=end;
		while(start<end){
			while(arr[start]<=arr[pivot] && start<rightmost+1) start++;
			while(arr[end]>arr[pivot]) end--;
			if(start<end){
				swap(arr[start],arr[end]);
			}
		}
		swap(arr[end],arr[pivot]);
		display(arr,n);
		quicksort(arr,leftmost,end-1,n);
		quicksort(arr,start,rightmost,n);
	}
}

/* -------------------------------------------------------------- */

void mergesort(int *arr, int start, int end, int n)
{
	int middle;
	if(start!=end){
		middle=(start+end)/2;
		mergesort(arr,start,middle,n);
		mergesort(arr,middle+1,end,n);
		merge(arr,start,middle,end,n);
		display(arr,n);
	}
}

/* -------------------------------------------------------------- */

void merge(int *arr, int start, int middle, int end, int n)
{
	int i, j, temp;
	int *aux;
	aux = newarray(n);

	i=start;
	j=middle+1;
	temp=start;
	while(i<=middle && j<=end)
		if(arr[i]<=arr[j])
			aux[temp++]=arr[i++];
		else
			aux[temp++]=arr[j++];
	while(i<=middle) aux[temp++]=arr[i++];
	while(j<=end) aux[temp++]=arr[j++];
	for(temp=start; temp<=end; temp++) arr[temp]=aux[temp];
	free(aux);
}

/* -------------------------------------------------------------- */

