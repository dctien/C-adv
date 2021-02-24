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

// hàm tạo ra 1 mảng copy của mảng ban đầu (cấp phát động)
int* copyArray(int* source, int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    for(int i=0; i<n;i++)
        list[i] = source[i];
    return list;
}

//hàm sắp xếp nổi bọt
void bubblesort(int *list, int n)
{
    for(int i=n; i>1; i--)
        for(int j=1;j<i; j++)
        {
            if(list[j-1]> list[j])
            {
                int tmp = list[j];
                list[j] = list[j-1];
                list[j-1] = tmp;
            }
        }
}

// hàm sắp xếp lựa chọn
void selectionsort(int *list, int n)
{
    for(int i=n; i>1; i--)
    {
        int vtmax = 0;
        for(int j=1; j<i; j++)
            if(list[j]>list[vtmax]) vtmax = j;
        
        int tmp = list[i-1];
        list[i-1] = list[vtmax];
        list[vtmax] = tmp;
    }
}

int main()
{
    const int n=1000; 
    double time_spent = 0.0;
    
    printf("So luong phan tu n= %d\n",n);
    clock_t begin = clock();
    int *source = generateArray(n);
    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Sinh mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
	
	
    int *copy1, *copy2;
    
    begin = clock();
    copy1 = copyArray(source, n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Copy mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
    
    copy2 = copyArray(source, n);
    
    begin = clock();
    bubblesort(copy1,n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep noi bot mat thoi gian la %f micro seconds\n", time_spent*1e6);
    
    begin = clock();
    selectionsort(copy2,n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep lua chon mat thoi gian la %f micro seconds\n", time_spent*1e6);
    
    free(copy1);
    free(copy2);
    free(source);
    return 0;
}
