#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);



void test(unsigned x, unsigned y, unsigned res)
{
    if (power(x, y) != res)
    {
        //printf("%d %d %d\n", y, x, res);
        exit(EXIT_FAILURE);
    }
}



void do_tests()
{
    test(0,0,1);
    test(0,1,0);
    test(1,0,1);
    test(2,-2,0);
    test(2,2.5,4);
    test(100,100,0);
    test(-2,2,4);
    test(-1,-1,4294967295);
    test(2,3,8);
    test(2.5,2,4);
    test(2.5,2.3,4);
    test(1000,5,2764472320);
}



void run_power()
{
    printf("power(0,0) = %u\n", power(0,0));
    printf("power(0,1) = %u\n", power(0,1));
    printf("power(1,0) = %u\n", power(1,0));
    printf("power(2,-2) = %u\n", power(2,-2));
    printf("power(2,2.5) = %u\n", power(2,2.5));
    printf("power(100,100) = %u\n", power(100,100));
    printf("power(-2,2) = %u\n", power(-2,2));
    printf("power(-1,-1) = %u\n", power(-1,-1));
    printf("power(2,3) = %u\n", power(2,3));
    printf("power(2.5,2.3) = %u\n", power(2.5,2.3));
    printf("power(1000,5) = %u\n", power(1000,5));
}



int main()
{
    do_tests(); 
    //run_power();

    return EXIT_SUCCESS;
}
