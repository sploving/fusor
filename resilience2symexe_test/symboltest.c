#include "symboltest.h"

int symboltest(i){
    int a[] = {3,4,5,6,7,1,2,8,9,0};
    int b[] = {9,5,6,0,1,2,3,4,7,8};
    int j = b[a[i]];
    if (i != j){
        printf("Type I opaque predicate should not be satisfiable\n");
        return -1;
    }
    if (j==6 && i==6){
        printf("Flag captured! Type II opaque predicate should be satisfiable\n");
        return 1;
    }
    return 0;
}
