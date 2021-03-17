#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[80];
    long number;
} PhoneEntry;

typedef struct
{
    PhoneEntry *entries;
    int total;
    int size;
} PhoneBooks;

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 10

PhoneBooks createPhoneBook()
{
    PhoneBooks phoneBook;
    phoneBook.total = 0;
    phoneBook.size = INITIAL_SIZE;
    phoneBook.entries = (PhoneEntry *)malloc(sizeof(PhoneEntry) * phoneBook.size);
    return phoneBook;
}

void dropPhoneBook(PhoneBooks *book)
{
    free(book->entries);
    book->entries = NULL;
    book->total = 0;
    book->size = 0;
}

// them 1 ban ghi moi vao book
void addPhoneNumber(char *name, long number, PhoneBooks *book)
{
    if (book->size > book->total)
    {
        strcpy((book->entries[book->total]).name, name);
        (book->entries[book->total]).number = number;
        book->total++;
    }
    else 
    {
        book->size += INCREMENTAL_SIZE;
        book->entries = (PhoneEntry *)realloc(book->entries, sizeof(PhoneEntry) * book->size);
        strcpy((book->entries[book->total]).name, name);
        (book->entries[book->total]).number = number;
        book->total++;
    }
}

PhoneEntry *getPhoneNumber(char *name, PhoneBooks *book)
{
    for (int i = 0; i < book->total; i++)
    {
        if (strcmp(name, book->entries[i].name) == 0)
            return (book->entries + i);
    }
    return NULL;
}

void display(PhoneBooks *book)
{
    for (int i = 0; i < book->total; i++)
    {
        printf("%-15s%-15ld\n", book->entries[i].name, book->entries[i].number);
    }
}

int main()
{
    PhoneBooks phoneBook;
    long id;
    phoneBook = createPhoneBook();
    char A[11][50];
    printf("Them danh ba:\n");

    for (int i = 0; i < 12; i++)
    {
        scanf("%[^\n]%*c", A[i]);
        id = i + 123456789;
        addPhoneNumber(A[i], id, &phoneBook);
    }

    display(&phoneBook);
    char s[40];
    printf("Nhap ten can tim: ");
    scanf("%[^\n]*c", s);
    PhoneEntry *check;
    check = getPhoneNumber(s, &phoneBook);
    if (check)
        printf("%-15s%-15ld\n", check->name, check->number);
    else
        printf("Nothing\n");
    dropPhoneBook(&phoneBook);
    return 0;
}
