#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    long long int s, n, size, i, digit[9], aux, j, k;
    while (scanf("%lld %lld", &s, &n) == 2)
    {
        if (s == 0 && n == 0)
            exit(-1);
        else
        {
            size = log10(n) + 1;
            for (i = 1; i <= size; i++)
            {
                aux = pow(10, i);
                digit[i] = (n % aux) / pow(10, i - 1);
            }
            for (j = 1; j <= 2 * s + 3; j++)
            {
                for (i = size; i >= 1; i--)
                {
                    if (j == 1 || j == s + 2 || j == 2 * s + 3)
                    {
                        printf(" ");
                        if (digit[i] == 1)
                        {
                            for (k = 0; k < s; k++)
                            {
                                printf(" ");
                            }
                        }
                        if (digit[i] == 2 || digit[i] == 3 || digit[i] == 5 || digit[i] == 6 || digit[i] == 8 || digit[i] == 9)
                        {
                            for (k = 0; k < s; k++)
                            {
                                printf("-");
                            }
                        }
                        if (digit[i] == 4)
                        {
                            if (j == 1 || j == 2 * s + 3)
                            {
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                            }
                            else
                            {
                                for (k = 0; k < s; k++)
                                {
                                    printf("-");
                                }
                            }
                        }
                        if (digit[i] == 7)
                        {
                            if (j == 1)
                            {
                                for (k = 0; k < s; k++)
                                {
                                    printf("-");
                                }
                            }
                            else
                            {
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                            }
                        }
                        if (digit[i] == 0)
                        {
                            if (j == 1 || j == 2 * s + 3)
                            {
                                for (k = 0; k < s; k++)
                                {
                                    printf("-");
                                }
                            }
                            else
                            {
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                            }
                        }
                        printf("  ");
                    }
                    if ((j > 1 && j < s + 2) || (j > s + 2 && j < 2 * s + 3))
                    {
                        if (digit[i] == 1)
                        {
                            printf(" ");
                            for (k = 0; k < s; k++)
                            {
                                printf(" ");
                            }
                            printf("| ");
                        }
                        if (digit[i] == 2)
                        {
                            if (j > 1 && j < s + 2)
                            {
                                printf(" ");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                            if (j > s + 2 && j < 2 * s + 3)
                            {
                                printf("|");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("  ");
                            }
                        }
                        if (digit[i] == 3)
                        {
                            printf(" ");
                            for (k = 0; k < s; k++)
                            {
                                printf(" ");
                            }
                            printf("| ");
                        }
                        if (digit[i] == 4)
                        {
                            if (j > 1 && j < s + 2)
                            {
                                printf("|");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                            if (j > s + 2 && j < 2 * s + 3)
                            {
                                printf(" ");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                        }
                        if (digit[i] == 5)
                        {
                            if (j > 1 && j < s + 2)
                            {
                                printf("|");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("  ");
                            }
                            if (j > s + 2 && j < 2 * s + 3)
                            {
                                printf(" ");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                        }
                        if (digit[i] == 6)
                        {
                            if (j > 1 && j < s + 2)
                            {
                                printf("|");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("  ");
                            }
                            if (j > s + 2 && j < 2 * s + 3)
                            {
                                printf("|");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                        }
                        if (digit[i] == 7)
                        {
                            printf(" ");
                            for (k = 0; k < s; k++)
                            {
                                printf(" ");
                            }
                            printf("| ");
                        }
                        if (digit[i] == 8)
                        {
                            printf("|");
                            for (k = 0; k < s; k++)
                            {
                                printf(" ");
                            }
                            printf("| ");
                        }
                        if (digit[i] == 9)
                        {
                            if (j > 1 && j < s + 2)
                            {
                                printf("|");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                            if (j > s + 2 && j < 2 * s + 3)
                            {
                                printf(" ");
                                for (k = 0; k < s; k++)
                                {
                                    printf(" ");
                                }
                                printf("| ");
                            }
                        }
                        if (digit[i] == 0)
                        {
                            printf("|");
                            for (k = 0; k < s; k++)
                            {
                                printf(" ");
                            }
                            printf("| ");
                        }
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}
