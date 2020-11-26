#include <stdlib.h>


size_t max(size_t a, size_t b)
{
    if (a > b) return a;
    return b;
}


size_t maxSeq(int * array, size_t n)
{
    if (n <= 0) return 0;
    if (n == 1) return 1;

    size_t max_size = 1;
    size_t current_max_size = 1;
    
    int * ptr = array + 1;  //current ptr --> array[1]
    int * end = array + n;

    while (ptr != end)
    {
        if (*ptr > *(ptr - 1))
            ++current_max_size;
        else
        {
            if (current_max_size > max_size)
                max_size = current_max_size;
            
            current_max_size = 1;
        } 

        ++ptr;
    }

    return max(max_size, current_max_size);
}
