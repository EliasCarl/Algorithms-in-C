/*
 * The struct is wrapped in a union to make sure it's aligned
 * on a worst-case basis, which in this case is a long. This
 * may not be needed anymore.
 *
 * TODO: Is explicit alignment necessary or is it handled by 
 * compilers today?
 */
union header {
    struct {
        union header *next;
        unsigned size;
    } s;
    long x;         /* union will be at least this size */
}
typedef union header Header;

Header* morecore(size_t);
void* kr_malloc(size_t);
void free(void* ptr);
