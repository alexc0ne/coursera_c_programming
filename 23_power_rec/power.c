

unsigned power(unsigned x, unsigned y)
{
    if (x == 0 && y == 0)
        return 1;

    if (x == 0)
        return 0;

    if (y == 0)
        return 1;
    
    if (y == 1)
        return x;

    unsigned pow = power(x, y/2);
    if (y % 2 == 0)
        return pow * pow;
    
    return x * pow * pow; 
}
