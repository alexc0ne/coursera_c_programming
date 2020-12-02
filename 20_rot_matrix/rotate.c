
void swap_char(char * a, char * b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}



void rotate(char matrix[10][10])
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (i < j)
                swap_char(&matrix[i][j], &matrix[j][i]);
   
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 5; ++j)
            swap_char(&matrix[i][j], &matrix[i][9-j]);
}
