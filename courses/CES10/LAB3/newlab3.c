#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n)
    {
        int *money = (int *)malloc(n*sizeof(int));
        int total = 0;
        for (int i = 0; i < n; i++)
        {
            int dollar, cent;
            scanf("%d.%d", &dollar, &cent);
            money[i] = dollar * 100 + cent;
            total += money[i];
        }

        int upper = ceil(1.0 * total / n);
        int lower = total / n;

        int smaller = 0, larger = 0;
        for (int i = 0; i < n; i++)
            if (money[i] < lower)
                smaller += lower - money[i];
            else if (money[i] > upper)
                larger += money[i] - upper;

        int solution = fmax(smaller, larger);

        printf("$%d.", solution / 100);
        if (solution % 100 < 10)
            printf("0");
        printf("%d\n", solution % 100);
        free(money);
    }
    return 0;
}