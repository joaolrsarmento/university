/***********************************/
/* Aluno: JOÃO LUÍS ROCHA SARMENTO */
/* CES-10: Introdução à Computação */
/* Prof. VITOR CURTIS              */
/***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#if CHAR_BIT != 8
#error "weird char size"
#endif

int find(void *x, void *array, size_t size_array, size_t size_variable, bool compare(const void *a, const void *b))
{
    size_t n = size_array / size_variable; //here we get the size of the array, that is, the quantity of numbers stored in the array
    for (int i = 0; i < (int)n; i++)
    {
        _Bool ret = compare(x, array + i*4); // if the comparison is successful, we return the array's index. Nevertheless, we have to pay attention to the fact that a void variable has a different size of the integer variable. This can be proved if we print sizeof(void) and sizeof(int), the size of the integer variable is going to be four times the void variable. That's the reason of the "4*i"
        if (ret)
            return i;
    }

    return -1;
}

// return true iff a=b (values)
_Bool compare_int(const void *a, const void *b)
{
    return (*(int *)a == *(int *)b); // the function receives a void pointer, but we need to compare integers. So, we've to use this casting
}

// return true iff a=b (values)
_Bool compare_float(const void *a, const void *b)
{
    return (*(float *)a == *(float *)b); // same casting technique as in the integer function, but, this time, we use to float numbers
}

int main()
{
    int vint[] = {1, 5, 10, 70, 3}, xint = 5;
    float vfloat[] = {1.3, 5.2, 10.1, 70.0, 3.3}, xfloat = 3.3;

    printf("vint[1]=vint[%d]=%d\n", find(&xint, (void *)vint, sizeof(vint), sizeof(*vint), compare_int), xint);
    printf("vfloat[4]=vfloat[%d]=%.1f\n", find(&xfloat, (void *)vfloat, sizeof(vfloat), sizeof(*vfloat), compare_float), xfloat);
}