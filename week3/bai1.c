#include <stdio.h>
#include <stdlib.h>
typedef union
{
    int i;
    long l;
    float f;
    double d;
    void *v;
} Jval;

Jval new_jval_i(int i){Jval j;j.i = i;return j;}
Jval new_jval_l(long l){Jval j;j.l = l;return j;}
Jval new_jval_f(float f){Jval j;j.f = f;return j;}
Jval new_jval_d(double d){Jval j;j.d = d;return j;}
Jval new_jval_v(void *v){Jval j;j.v = v;return j;}

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }
int search_gen(Jval *list, int size, Jval key)
{
    for (int i = 0; i < size; i++)
        if (jval_i(list[i]) == jval_i(key))
            return i;

    return -1; // khong tim thay
}

int main()
{
    int size = 10;
    Jval key = new_jval_i(8);
    Jval *list = (Jval *)malloc(sizeof(Jval) * size);
    for (int i = 0; i < size; i++)
    {
        list[i] = new_jval_i(i + 2);
    }
    int check = search_gen(list, size, key);
    printf("%d", check);
    return 0;
}
