#include <stdio.h>

#define ARRAY_SIZE 15

void quicksort(int[], int, int);
int partition(int[], int, int);
void print_array(int [], int len);

int main(void) 
{
    int array[ARRAY_SIZE] = {4,1,3,2,16,9,10,14,8,7,20,66,11,16,12};
    int len = sizeof(array) / sizeof(int);

    quicksort(array, 0, len-1);
}

void quicksort(int a[], int p, int r)
{
    printf("Pivot: %-2d ", a[r]);
    print_array(a,ARRAY_SIZE);

    int q;

    if (p < r)
    {
        /*
         * Partition the subarray we were given. We need the index
         * of the pivot in the next two recursive calls. Note that
         * the pivot a[r] is not always perfect and will sometimes
         * give different sized partitions. Here we have set the
         * pivot to the last element for simplicity.
         *
         * Note also that the pivot is now in its right place and 
         * not in subsequent calls to quicksort.
         */
        q = partition(a, p, r);


        /*
         * Quicksort the subarray a[p...q-1]. This means that we 
         * partition this subarray "around" the new pivot q-1.  
         */
        quicksort(a, p, q-1);


        /* Same */
        quicksort(a, q+1, r);
    }
}

/*
 * Rearrange the subarray a[p...r] in place such that each element
 * in a[p..q-1] is less than a[q] which in turn is smaller than
 * each element in a[q+1..r]. a[q] will be our pivot, here a[r].
 */
int partition(int a[], int p, int r)
{
    int temp;

    /* Here we select our pivot */
    int x = a[r];

    /* Index of last element in lower partition. */ 
    int i = p - 1;

    for (int j = p; j < r; j++)
    {
        if (a[j] < x)
        {
            /* Make room for another element in lower partition */
            i++;

            /* Now we move a[j] to the new index in the lower partition */
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;

        }
    }

    /*
     * Now j == r, and a[r] is our pivot. We want to move the pivot into
     * the correct place, which is between the lower and higher partitions.
     * We know that since i is the index to the last element in the lower 
     * partition, i+1 is the first element in the higher partition.
     */

    temp = a[i+1];
    a[i+1] = a[r];
    a[r] = temp;

    /* Return the index of the pivot */
    return i + 1;

}


void print_array(int array[], int len)
{
    printf("[");
    for (int i = 0; i < len; i++) 
    {
        printf("%2d%s", array[i], i == len-1 ? "" : ",");    
    }
    printf("]\n");
}
