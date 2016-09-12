/*
 * This is an implementation of malloc based on the example from K&R.
 */

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include "kr_malloc.h"

static Header base = {0};       /* base of list */
static Header *freeptr = NULL;  /* search for space starting at this pointer */


/*
 * To align every block of memory they are all assigned a size
 * which is a multiple of sizeof Header, which itself is already
 * aligned. 
 */
void* kr_malloc(size_t nbytes)
{
    Header* currptrtr;          /* current Header */
    Header* prevptr;            /* previous Header  */
    size_t  nunits;             /* number of Header sizes needed for allocation  */
    void*   result;             /* pointer to the space found */
    bool    is_allocating;      /* For controlling loop termination */

    /*
     * Calculate number of units needed to fit passed in value nbytes.
     * 
     * Integer division in C performs truncation towards 0. We therefore
     * always add one to the result to allocate one more unit than
     * was requested. We handle the special case of a perfect fit by
     * forcing truncation with a -1 in the numerator.
     *
     * The extra sizeof Header in the numerator is for the actual header.
     */
    nunits = (nbytes + sizeof Header - 1 / sizeof Header) + 1;

    /*
     * If the pointer that should point to a free block is NULL, we don't
     * have a list yet. We initialize our list by pointing next, free and
     * previous to base, our base element, and set it to size 0.  
     */
    if (prevptr == NULL)
    {
        base.s.next  = &base;
        freeptr      = &base;
        prevptr      = &base;
        base.s.size  = 0;
    }


    /* prepare the pointers for list traversal */
    prevptr = freeptr;
    currptr = freeptr->s.next;

    /* begin traversal */
    is_allocating = true;
    while (is_allocating)
    {
        if (currptr->s.size >= nunits)                /* it fits */
        {
            if (currptr->s.size == nunits)            /* perfect fit */
            {
                prevptr->s.next = currptr->s.next;    /* remove currptr from list */
            }
            else 
            {
                currptr->s.size -= nunits;            /* reduce size of block by nunits */ 
                currptr += currp->s.size;             /* step over size left over */ 
                currptr->s.size = nunits;             /* set size to nunits */
            }
            freeptr = prevptr;                       
            result  = currptr + 1;
            is_allocating = false;
        }

        /* 
         * freeptr is where we started, i.e. have we visited every
         * free block without finding a fit?
         */
        if (currptr == freeptr)
        {
            currptr = morecore(nunits);               /* ask OS for more memory */ 
            if (currptr == NULL)                      /* OS couldn't help us */
            {
                result = NULL;
                is_allocating = false;
            }
        }

        prevptr = currptr;
        currptr = currptr->s.next
    } /* end for */

    return result;
}

#define NALLOC 1024

static Header *morecore(size_t units)
{
    if (units < NALLOC)
    {
        units = NALLOC;
    }

    void* block_ptr;
    block_ptr = sbrk(units * sizeof Header);
    if (block_ptr == (void*) -1)
    {
        return NULL;
    }

    // TODO: Finish this.

}
