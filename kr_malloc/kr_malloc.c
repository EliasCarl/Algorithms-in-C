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
    Header* currptr;            /* current Header */
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
    void* newmem;
    Header* headerptr;

    /* Allocate at least (1024 * sizeof Header) bytes */
    if (units < NALLOC)
    {
        units = NALLOC;
    }

    /* request to move the program break */
    newmem = sbrk(units * sizeof Header);
    if (newmem == (void*) -1)
    {
        /* OS couldn't give us any memory */
        return NULL;
    }

    headerptr = (Header*) newmem;                     /* cast to our own Header type */
    headerptr->s.size = units;                        /* set size of new block header */
    free((void*) headerptr + 1);                      /* place the new block in the list */
    return freeptr;                                   /* returns the start of the list */
}

void free(void* ptr)
{
    /* TODO: Cleanup: variable naming etc */

    Header* hp;
    Header* currptr;
    
    bp = (Header*) ptr - 1;                           /* point hp to the header block */

    /* 
     * We traverse the list of (free) blocks and stop
     * once we find the header of the block just before
     * the one we're trying to free.
     *
     * The first for loop exits if the heaper pointer (hp)
     * is between the current block and the next one. The
     * inner if statement handles the case where hp is a
     * block in the beginning or end of the list.
     */
    for (currptr = freep; !(hp > currptr && hp < currptr->s.next); currptr = currptr->s.next)
    {
        if (currptr >= curreptr->s.next && (hp > currptr || hp < currptr->s.next))
        {
            break;
        }
    }

    /* Now currptr points to the header of the block just
     * before hp and currptr->s.next is the block immediately
     * after block hp.
     */

    if (hp + hp->s.size == currptr->s.next)
    {
        /*
         * If hp is immediately adjacent to currptr->s.next,
         * meaning there are no allocated blocks between them,
         * then merge the two together. If not, just point hp 
         * next without merging.
         */

        hp->s.size += currptr->s.next->s.size;
        hp->s.next = currptr->s.next->s.next;
    }
    else
    {
        hp->s.next = currptr->s.next;
    }

    /*
     * Do the same thing but for the block before hp.
     */
    if (currptr + currptr->s.size == hp)
    {
        currptr->s.size += hp->s.size;
        currptr->s.next = hp->s.next;
    }
    else
    {
        currptr->s.next = hp;
    }

    /* 
     * Set the freep to p so that the next search for
     * free blocks will begin at our newly freed block
     */
    freep = p;
}
