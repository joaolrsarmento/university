#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, sum, sum2;
    double *value, media;
    while (1)
    {
        if(scanf("%d", &n) == EOF || !n)
            exit(1);
        else
        {
            value = (double *)malloc(n * sizeof(double));
            sum = 0;
            sum2 = 0;
            media = 0;
            for (i = 0; i < n; i++)
            {
                scanf("%lf", &value[i]);
                sum += 100 * value[i];
            }
            media = 1.0 * sum / n;
            for (i = 0; i < n; i++)
            {
                if (value[i] > media / 100.0)
                {
                    sum2 += (100.0 * value[i] - media);
                }
            }
            printf("$%.2lf\n", sum2 / 100.0);
            free(value);
        }
    }
    return 0;
}