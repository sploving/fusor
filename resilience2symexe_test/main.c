#include <stdio.h>

int main(int argc, char**argv){
    int i = (atoi(argv[1]) % 10 + 10) % 10;
    int a[] = {3,4,5,6,7,1,2,8,9,0};
    int b[] = {9,5,6,0,1,2,3,4,8,7};
    int c[] = {1, 2, 3, 4, 5, 6, 8, 9, 6, 0};
    int d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    int j = d[c[b[a[i]]]];
    if (i != j){
        printf("Type I opaque predicate should not be satisfiable\n");
    }
    if (j==7 && i==7){
        printf("Type II opaque predicate should be satisfiable\n");
    }
}