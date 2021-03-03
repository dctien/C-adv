#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Sinh so ngau nhien khong trung lap
int* generateArray(int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n;i++)
        list[i] = rand();
    return list;
}

//Sinh so ngau nhien trung lap 
int* generateArrayDuplicate(int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n;i++)
    {
        list[i] = rand();
        int m = rand()%100;
        // tạo ra m lần lặp của phần tử thứ i
        for(int j=1; j<=m; j++)
        {
            list[i+j] = list[i];
        }
        i = i + m;
    }
    return list;
}

// quicksort 2-way partitioning
void quicksort(int *number,int first,int last)
{
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
        // swap phan tư
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);
   }
}

// thuật toán quick sort chia dãy thành 3 phần
void sort(int a[], int l, int r) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while (a[++i] < a[r]);
		while (a[r] < a[--j]) if (j == l) break;
		if (i >= j) break;
		exch(a, i, j);
		if (a[i]==a[r]) exch(a, ++p, i);
		if (a[j]==a[r]) exch(a, --q, j);
	}
	exch(a, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) exch(a, k, j--);
	for (int k = r-1; k >= q; k--) exch(a, k, i++);
	sort(a, l, j);
	sort(a, i, r);
}

int main(){
    const int n=10000; 
    double time_spent = 0.0;

    printf("So luong phan tu n=%d\n",n);
    printf("\nVoi sinh so ngau nhien khong trung lap\n");
    clock_t begin = clock();
    int *source = generateArray(n);
    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Sinh mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
	
	
    int *copy1, *copy2, *copy3, *copy4, *copy5;
    
    begin = clock();
    copy1 = copyArray(source, n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Copy mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
    
    copy2 = copyArray(source, n);
    copy3 = copyArray(source, n);
    copy4 = copyArray(source, n);
    copy5 = copyArray(source, n);

    begin = clock();
    sort(copy3,0,n-1);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep QuickSort 3-way partitioning mat thoi gian la %f micro seconds\n", time_spent*1e6);
	
//voi so ngau nhien trung lap
    printf("\nVoi sinh so ngau nhien trung lap\n");
    clock_t begin1 = clock();
    int *source1 = generateArrayDuplicate(n);
    clock_t end1 = clock();
    // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Sinh mang mat thoi gian la %f micro seconds\n", time_spent*1e6);	
    
    begin1 = clock();
    quicksort(copy4,0,n-1);
    end1 = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep QuickSort 2-way partitioning mat thoi gian la %f micro seconds\n", time_spent*1e6);
	
    begin1 = clock();
    sort(copy5,0,n-1);
    end1 = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep QuickSort 3-way partitioning mat thoi gian la %f micro seconds\n", time_spent*1e6);

    // giai phong bo nho dong
    free(copy1);
    free(copy2);
    free(copy3);
    free(copy4);
    free(copy5);
    free(source);
    free(source1);
    return 0;
}


