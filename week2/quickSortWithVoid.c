#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// n là số lượng phần tử cần sinh
// Hàm sinh và trả về mảng cấp phát động chứa n phần tử
	

int* generateArray(int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n;i++)
        list[i] = rand();
    return list;
}


// hàm tạo ra 1 mảng copy của mảng ban đầu (cấp phát động)
int* copyArray(int* source, int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    for(int i=0; i<n;i++)
        list[i] = source[i];
    return list;
}

int int_compare(void const* x, void const *y) {
	int m, n;
	m = *((int*)x); // ep ve kieu so nguyen
	n = *((int*)y); 
	if ( m == n ) return 0;
	return m > n? 1: -1;
}

int double_compare(void const* x, void const *y) {
	double m, n;
	m = *((double*)x); // ep ve kieu so nguyen
	n = *((double*)y); 
	if ( m == n ) return 0;
	return m > n? 1: -1;
}

void swap(void* a, void *b, int size)
{
    void *tmp = malloc(size);
    memcpy(tmp,a, size) ;
    memcpy(a,b, size) ;
    memcpy(b,tmp, size) ;
}

// mảng đầu vào number
// kích thước 1 phần tử t_size
// hàm so sánh compare
void quicksort(void *number,int first,int last, int (*compare)(void const *,void const *), int t_size)
{
   int i, j, pivot;
   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(compare((char*)number + i*t_size,(char*)number +pivot*t_size)==-1&&i<last)
            i++;
         while(compare((char*)number + j*t_size,(char*)number +pivot*t_size)==1)
            j--;
        // swap phan tư
         if(i<j){
             swap((char*)number + i*t_size,(char*)number + j*t_size, t_size);
         }
      }
      swap((char*)number + j*t_size,(char*)number + pivot*t_size, t_size);

      quicksort(number,first,j-1, compare, t_size);
      quicksort(number,j+1,last,compare, t_size);
   }
}

void printArr(int *list, int n)
{
    for (int i=0; i<n ;i++)
        printf("%d, ",list[i]);
    
    printf("\n");
}
int main()
{
    const int n=10; 
    double time_spent = 0.0;
    
    printf("So luong phan tu n=%d\n",n);
    clock_t begin = clock();
    int *source = generateArray(n);
    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Sinh mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
	
	
    int *copy1, *copy2, *copy3;
    
    begin = clock();
    copy1 = copyArray(source, n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Copy mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
    
    copy3 = copyArray(source, n);
    
   
    printArr(copy3,n);
    begin = clock();
    quicksort(copy3,0,n-1, int_compare,sizeof(int));
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep QuickSort mat thoi gian la %f micro seconds\n", time_spent*1e6);
	printArr(copy3,n);

    // testing
    printf("\n");
    printf("%d %d\n",copy3[0],copy3[1]);
    swap(copy3, copy3 + 1, sizeof(copy3[0]));
    printf("%d %d\n",copy3[0],copy3[1]);
    // giai phong bo nho dong
    free(copy3);
    free(source);
    
    return 0;
}
