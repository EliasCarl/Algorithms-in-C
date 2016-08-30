#include <stdio.h>

#define ARRAY_SIZE 15 

void print_array(int [], int);

void max_heapify(int [], int, int);
void build_max_heap(int [], int);
void heapsort(int [], int);

int main(void)
{
    int array[ARRAY_SIZE] = {4,1,3,2,16,9,10,14,8,7};
    int array2[ARRAY_SIZE] = {4,1,3,2,16,9,10,14,8,7};
    int len = sizeof(array) / sizeof(int);

    printf("%-22s", "Array before heapify:");
    print_array(array, len);

    build_max_heap(array, len);
    printf("%-22s", "Array after heapify:");
    print_array(array, len);

    printf("\n");

    printf("%-22s", "Array before heapsort:");
    print_array(array2, len);

    heapsort(array2, len);
    printf("%-22s", "Array after heapsort:");
    print_array(array2, len);
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
    int debug = 0;

    if (debug)
    {
        print_array(a, len);
        printf("Root:  a[%d] = %d\n", i, a[i]);
        printf("Left:  a[%d] = %d\n", l_child_index, a[l_child_index]);
        printf("Right: a[%d] = %d\n", r_child_index, a[r_child_index]);
        printf("\n");
    }

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
        printf("%2d%s", array[i], i == len-1 ? "" : ",");    
    }
    printf("]\n");
}

/*
 * Heapsort:
 * 
 * 1. Transform the array a into a max-heap. The maximum element is
 *    now stored at the root position a[0]. 
 *
 * 2. We can immediately swap a[0] element with a[len] because the
 *    max-heap property guarantees it is the max element. 
 *
 * 3. If we "forget" the elements a[len .. n] by decreasing len itself,
 *    we know that the children of the root remain max heaps. This
 *    is fine since we already know that a[len .. n] is correctly placed
 *    and we want to exclude them from further processing.
 *
 * 4. The root element swapped in (2) is still unprocessed, to incorporate 
 *    the new root into the max-heap below (remember, this new max-heap is
 *    the elements a[0 .. n-len]) we call max_heapify(a, 0, len).  
 *
 * 5. Since the subarray a[0 .. n-len] is now a max-heap, start over at (2).
 */

void heapsort(int a[], int len)
{
    int temp;

    build_max_heap(a, len);

    /* Offset len for 0 indexing. */
    len -= 1;
    
    while (len > 0)
    {
        temp = a[len];
        a[len] = a[0];
        a[0] = temp;

        len--;

        max_heapify(a, 0, len);
    }
}
