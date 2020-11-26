#include <stdio.h>
#include <stdlib.h>


size_t maxSeq(int * array, size_t n);


int main()
{
    int a0[0];
    if (maxSeq(a0, 0) != 0)
        return EXIT_FAILURE;

    int a1[] = {1};
    if (maxSeq(a1, 1) != 1)
        return EXIT_FAILURE;

    int a2[] = {1,1};
    if (maxSeq(a2, 2) != 1)
        return EXIT_FAILURE;

    int a3[] = {1,1,1,2,1};
    if (maxSeq(a3, 5) != 2)
        return EXIT_FAILURE;

    int a4[] = {5,3,1,-3};
    if (maxSeq(a4, 4) != 1)
        return EXIT_FAILURE;

    int a5[] = {1,0,2,-1,3,-2};
    if (maxSeq(a5, 6) != 2)
        return EXIT_FAILURE;

    int a6[] = {1, -3, 2, -2, 3, -1, 4, 0};
    if (maxSeq(a6, 8) != 2)
        return EXIT_FAILURE;
    
    int a7[] = {1,2,3,-5,-4,-3,-2};
    if (maxSeq(a7, 7) != 4)
        return EXIT_FAILURE;

    int a8[] = { 1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
    if (maxSeq(a8, 10) != 4)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
