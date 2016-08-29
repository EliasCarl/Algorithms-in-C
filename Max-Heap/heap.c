#include <stdio.h>

#define ARRAY_SIZE 15 

void print_array(int [], int);

void max_heapify(int [], int, int);
void build_max_heap(int [], int);

int main(void)
{
    int array[ARRAY_SIZE] = {4,1,3,2,16,9,10,14,8,7};
    int len = sizeof(array) / sizeof(int);

    printf("%-22s", "Array before heapify:");
    print_array(array, len);

    build_max_heap(array, len);
    printf("%-22s", "Array after heapify:");
    print_array(array, len);
}

void build_max_heap(int a[], int len)
{
    /* 
     * The max heap property is the following:
     *
     * a[parent(i)] >= a[i]
     *
     * Elements in the subarray a[len/2 + 1 ... len] are 1 element heaps. 
     * These 1 element heaps satisfy the max-heap property (since they have
     * neither parent nor children). We need not employ max_heapify on these.
     * 
     * Instead we meax_heapify every element in the subarray above starting
     * with the highest index (len/2) and move down the list. Since all
     * elements after a[len/2] are max heaps, we know max_heapify is a valid
     * procedure. 
     */

    printf("Starting index: %d\n\n", len / 2);

    int i;
    for (i = len - 1 / 2; i >= 0; i--) 
    {
        max_heapify(a, i,  len); 
    }
}

void max_heapify(int a[], int i, int len)
{
    int l_child_index = 2 * i + 1;
    int r_child_index = 2 * i + 2;
    int largest_index = i;
    int temp;

    /* Instantly return if leaf node */
    if (l_child_index >= len || r_child_index >= len)
    {
        return;
    }

    // Debug
    print_array(a, len);
    printf("Root:  a[%d] = %d\n", i, a[i]);
    printf("Left:  a[%d] = %d\n", l_child_index, a[l_child_index]);
    printf("Right: a[%d] = %d\n", r_child_index, a[r_child_index]);
    printf("\n");

    /*
     * Find which of i, l_child(i) and r_child(i) is largest.
     * Store the index of the largest.
     */

    if (l_child_index < len && a[l_child_index] > a[largest_index])
    {
        largest_index = l_child_index; 
    }
    if (r_child_index < len && a[r_child_index] > a[largest_index])
    {
        largest_index = r_child_index; 
    }

    /*
     * If the one of the children was the largest, swap it with a[i].
     */

    if (largest_index != i)
    {
        temp = a[i];
        a[i] = a[largest_index];
        a[largest_index] = temp;

        /*
         * Recursively max_heapify on our new root node largest_index.
         */

        max_heapify(a, largest_index, len);
    }


    /*
     * a[i] is now a max-heap.
     */

}

void print_array(int array[], int len)
{
    printf("[");
    for (int i = 0; i < len; i++) 
    {
        printf("%d%s", array[i], i == len-1 ? "" : ",");    
    }
    printf("]\n");
}
