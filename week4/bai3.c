#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 5
#define INCREMENTAL_SIZE 5

typedef struct {
	void * key;
	void * value;
} Entry;

typedef struct {
	Entry * entries;
	int size, total;
	Entry (*makeNode)(void*, void*);
	int (*compare)(void*, void*);
} SymbolTable;

Entry makePhone(void* name, void* phone) {
	Entry res;
	res.key = strdup( (char*)name );
	res.value = malloc(sizeof(long));
	memcpy( res.value, phone, sizeof(long) );
	return res;
}

int comparePhone(void * key1, void* key2) {
	return strcmp((char*)key1, (char*)key2);
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),
		int (*compare)(void*, void*)
)
{
    SymbolTable spb;
    spb.size = INITIAL_SIZE;
    spb.total = 0;
    spb.entries = (Entry*)malloc(sizeof(Entry)*spb.size);
    return spb;
}
void dropSymbolTable(SymbolTable* book)
{
    for(int i=0; i<book->total; i++)
    {
        free(book->entries[i].key);
        free(book->entries[i].value);
    }
    free(book->entries);
    
    book->entries = NULL;
    book->total=0;
    book->size=0;
}
void addEntry(void* key, void* value, SymbolTable* book)
{
    if(book->size>book->total)
    {
        book->entries[book->total] = makePhone(key, value);
        book->total++;
    }
}
Entry* getEntry(void* key, SymbolTable* book){
	for(int i=0; i<book->total; i++)
        if(strcmp((char*)key, (char*)(book->entries[i]).key)==0) return  &(book->entries[i]);
    return NULL;

};

void printAllPhoneBook(const SymbolTable* book)
{
    printf("Danh ba hien tai co %d phan tu, kich thuoc toi da %d\n",book->total, book->size);
    for(int i=0; i<book->total; i++)
        printf("%20s\t%15ld\n", (char*)(book->entries[i]).key, *((long*)(book->entries[i]).value));
    
    printf("==================================\n");
}


int main()
{
    SymbolTable phoneBook = createSymbolTable(makePhone, comparePhone);
    long number = 983984775;
    char name[] = "Nguyen Van A";
    addEntry(name, &number, &phoneBook);
    printAllPhoneBook(&phoneBook);
    
    return 0;
}




