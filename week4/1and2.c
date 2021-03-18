#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[80];
  long number;
} PhoneEntry;

typedef struct {
  PhoneEntry * entries;
  int total;
  int size;
} PhoneBook;


#define INITIAL_SIZE 5
#define INCREMENTAL_SIZE 5

PhoneBook  createPhoneBook()
{
    PhoneBook pb;
    pb.total = 0;
    pb.size = INITIAL_SIZE;
    pb.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)*pb.size);
    return pb;
}

void  dropPhoneBook(PhoneBook* book)
{
    free(book->entries);
    book->entries = NULL;
    book->total=0;
    book->size=0;
}

void sapxep(PhoneBook* book){
    for(int i=0;i<book->total-1;i++){
        for(int j=i+1;j<book->total;j++){
            if(strcmp(book->entries[i].name,book->entries[j].name)>0){
                PhoneEntry temp;
                temp=book->entries[i];
                book->entries[i]=book->entries[j];
                book->entries[j]=temp;
            }
        }
    }
}

// them 1 ban ghi moi vao book
void addPhoneNumber(char * name, long number, PhoneBook* book)
{
    if(book->size>book->total)// chua day, co the them
    {
        strcpy((book->entries[book->total]).name, name);
        (book->entries[book->total]).number = number;
        
        book->total++;
    }
    else // cap phat dong mang moi, copy sang mang moi dung memcpy 
    {
        // tao mang moi kich thuoc bang mang cu cong them INCREMENTAL_SIZE
        PhoneEntry * newBook = (PhoneEntry*)malloc(sizeof(PhoneEntry)*(book->size+INCREMENTAL_SIZE));
        
        // copy phan tu mang cu sang mang moi
        for(int i=0; i<book->total; i++)
            memcpy(&newBook[i],&(book->entries[i]),sizeof(PhoneEntry));
        
        // xoa mang cu
        free(book->entries);
        
        // cap nhat lai thong tin cua phonebook moi
        book->entries = newBook;
        book->size = book->size + INCREMENTAL_SIZE;
        
        // them phan tu moi vao cuoi
        strcpy((book->entries[book->total]).name, name);
        (book->entries[book->total]).number = number;
        
        book->total++;
    }
    sapxep(book);
}

void printAllPhoneBook(const PhoneBook* book)
{
    printf("Danh ba hien tai co %d phan tu, kich thuoc toi da %d\n",book->total, book->size);
    for(int i=0; i<book->total; i++)
        printf("%20s\t%15ld\n", (book->entries[i]).name, (book->entries[i]).number);
    
    printf("==================================\n");
}
// phonebook duoc them vao ko theo thu tu ho getPhoneNumber
// tim kiem chi don gian la tuan tu 
// tra ve gia tri NULL neu khong tim thay
// tra ve dia chi phan tu neu tim thay
PhoneEntry * getPhoneNumber(char * name, const PhoneBook* book)
{
    for(int i=0; i<book->total; i++)
        if(strcmp(name, (book->entries[i]).name)==0) return  &(book->entries[i]);
    return NULL;
}

PhoneEntry * timkiemV2(char * name, const PhoneBook* book)
{
    for(int i=0; i<book->total; i++)
        if(strstr((book->entries[i]).name,name)!=NULL)
            printf("%20s\t%15ld\n", (book->entries[i]).name, (book->entries[i]).number);
    return NULL;
}

int main()
{
    PhoneBook pb;
    pb = createPhoneBook();
    addPhoneNumber("Nguyen Van Mau",123456789,&pb);
    addPhoneNumber("Nguyen Van 1",123456789,&pb);
    addPhoneNumber("Nguyen Van 2",123456789,&pb);
    addPhoneNumber("Nguyen Van 3",123456789,&pb);
    addPhoneNumber("Nguyen Van 4",123456789,&pb);
    addPhoneNumber("Nguyen Van 5",123456789,&pb);

    printAllPhoneBook(&pb);
    PhoneEntry * ret = getPhoneNumber("Nguyen Van 2",&pb );
    if(ret==NULL) printf("Khong ton tai trong danh ba!\n");
    else
        printf("tim thay thong tin : %20s\t%15ld\n", ret->name, ret->number);
    
    printf("==================================\n");
    timkiemV2("Nguyen",&pb);
    return 0;
}
