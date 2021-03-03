#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// n là số lượng phần tử cần sinh
// Hàm sinh và trả về mảng cấp phát động chứa n phần tử
	

void swap(void* buf, int sizeOfElements, int firstIndex,int secondIndex){
    char* temp1 = (char*)buf+(sizeOfElements*firstIndex);
    char* temp2 = (char*)buf+(sizeOfElements*secondIndex);
    void *s = malloc(sizeOfElements) ;
    memcpy(s,temp1,sizeOfElements);
    memcpy(temp1,temp2,sizeOfElements);
    memcpy(temp2,s,sizeOfElements);
    free(s);
}

void quickSort(void *buf,int sizeOfElements,int leftIndex,int rightIndex,int (*compare)(const void*,const void*) ){
    int i,j,pivot;
    if (leftIndex < rightIndex){
        pivot = leftIndex;
        i = leftIndex;
        j = rightIndex;
        while(i<j){
            while((compare((char*)buf+sizeOfElements*i,(char*)buf+sizeOfElements*pivot)) <= 0 && i < rightIndex)
                i++;
            while((compare((char*)buf+sizeOfElements*j,(char*)buf+sizeOfElements*pivot)) > 0)
                j--;
            if (i<j){
                swap(buf,sizeOfElements,i,j);
            }
        }
        swap(buf,sizeOfElements,pivot,j);
        quickSort(buf,sizeOfElements,leftIndex,j-1,compare);
        quickSort(buf,sizeOfElements,j+1,rightIndex,compare);
    }
}

int string_compare_case(void const *str1, void const *str2)
{
    char *s1, *s2;
	s1 = (char*)str1; // ep ve kieu xau
	s2 = (char*)str2; 
	return strcmp(s1,s2);
}

int string_compare_nocase(void const *str1, void const *str2)
{
    char *s1, *s2;
	s1 = (char*)str1; // ep ve kieu xau
	s2 = (char*)str2; 
	for (;; s1++, s2++) {
        int d = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (d != 0 || !*s1)
            return d>0?1:(d<0?-1:0);
    }
}

int main()
{
    char namelist[][30]={"iPhone","Apple","apple","Samsung","Google","Facebook","Xiaomi","Huwei"};
    char namelist2[][30]={"iPhone","Apple","apple","Samsung","Google","Facebook","Xiaomi","Huwei"};

   
    printf("Xap sep phan biet chu hoa chu thuong: \n");
    quickSort(namelist,sizeof(namelist[0]),0,7, string_compare_case);
    printf ("\nSap xep co phan biet chu hoa,thuong:\n");
    int i;
    for (i=0;i<8;i++)   
        printf ("%s\t",namelist[i]);
    
    quickSort(namelist2,sizeof(namelist[0]),0,7, string_compare_nocase);
    printf ("\nSap xep khong phan biet chu hoa,thuong:\n");
    for (i=0;i<8;i++)   
        printf ("%s\t",namelist[i]);
    printf("\n");
    
    
    // end = clock();
    // time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    // printf("Sap xep QuickSort mat thoi gian la %f micro seconds\n", time_spent*1e6);
	// printArr(copy3,n);

    // giai phong bo nho dong
    // free(copy3);
    // free(source);
    
    return 0;
}
