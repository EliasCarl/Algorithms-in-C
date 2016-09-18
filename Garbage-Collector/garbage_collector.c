/*
 * A mark-and-sweep garbage collector. Made following this tutorial.
 *
 * http://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/
 */

#include <assert.h>

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 256

typedef enum 
{
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct sObject 
{
    unsigned char marked;

    struct sObject* next;

    ObjectType type;
    union 
    {
        int value;

        struct 
        {
            struct sObject* Head;
            struct sObject* tail;
        };
    };
} Object;

/*
 * Since we need some type of language to use our garbace collector
 * we implement a simple VM to handle references to the objects we
 * defined above. The VM is stack-based, this means that the stack
 * holds every object currently in scope. When an object is no longer
 * referenced in the stack, it is lost forever. This, of course, is
 * not what we want, since we need a reference to an object to free
 * the memory that object occupies. We simply make a separate list
 * outside of the semantics of the language, hidden from the user,
 * which keeps track of _every_ allocated memory.
 */
typedef struct 
{
    /* The "separate" list. */
    Object* listHead;
    int numObjects;
    int maxObjects;

    /* The stack. */
    Object* stack[STACK_MAX];
    int stackSize;

} VM;

/*
 * Initialize the VM. The only thing that might change is the
 * maxObjects variable. When the number total objects in the list
 * hits this value, we run the garbage collector.
 */
VM* newVM() 
{
    VM* vm = malloc(sizeof VM);
    vm->stackSize = 0;
    vm->listHead = NULL;
    vm->numObjects = 0;
    vm->maxObjects = INITIAL_GC_THRESHOLD;
    return vm;
}

/*
 * This is a regular push, as with any stack. It is, however, important
 * to understand that this push is what makes an object available to the
 * user of the language using the VM. The stack is what defines which 
 * objects are in "scope". If an object is not in the stack, it may still
 * exist, but it's not available.
 */
void push (VM* vm, Object* value)
{
    assert(vm->stackSize < STACK_MAX, "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm)
{
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

Object* newObject(VM* vm, ObjectType type)
{
    /* 
     * Before the language accommodate the request to allocate memory
     * for a new object, it makes a quick check to see if the vm is 
     * okay with one more object in it's list. If not, we run our GC
     * on the vm to free up unreferenced space.
     */
    if (vm->numObjects == vm->maxObjects) {
        collect_garbage(vm);
    }       

    /* Proceed to allocate memory for object. */
    Object* objectptr = malloc(sizeof Object);
    objectptr->type = type;
    objectptr->marked = 0;

    /* Return pointer to the object. */
    return objectptr;
}

/*
 * Register an object in a VMs list of objects. If this is not done
 * the reference to this object will be lost forever when it goes
 * out of scope, and we have a memory leak. I have put this procedure
 * in it's own function to be explicit, but this can be placed in the
 * above newObject() to be sure it is _always_ done.
 */
void registerObject(VM* vm, Object* objectptr)
{
    objectptr->next = vm->listHead;
    vm->listHead = objectptr;
    vm->numObjects++;
}

/* Allocate memory for object and register it in a vm. */
void pushInt(VM* vm, int value)
{
    Object* objectptr = newObject(vm, OBJ_INT);
    registeObject(vm, objectptr);
    object->value = value;
    push(vm, object); 
}

/* Same as above but for a different type. */
void pushPair(VM* vm)
{
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

/*
 * Where it all comes together. We know that every object that can be
 * reached from any object in the specified VMs stack is in scope. We
 * flip the mark bit on all of those objects. Objects which are not 
 * reachable from any object in the VMs stack will have the mark bit
 * set to 0.
 */
void markAll(VM* vm)
{
    for (int i = 0; i < vm->stackSize; i++)
    {
        recursivelyMark(vm->stack[i]);
    }
}

void recursivelyMark(Object* object)
{
    /* Watch out for cycles. */
    if (object->marked) return;

    /* Mark this and all objects it references. */
    object->marked = 1;
    if (object->type == OBJ_PAIR)
    {
        recursivelyMark(object->head);
        recursivelyMark(object->tail);
    }
}

void sweep(VM* vm)
{
    /* Loop over every object in the VMs list. */
    Object** listptr = &vm->listHead;
    while (*listptr)
    {
        if (!(*listptr)->marked)
        {
            /* Save a pointer to the unmarked object. */
            Object* unmarkedptr = *object;

            /* Remove the unmarked object from the list. */
            *listptr = unmarkedptr->next;

            /* Now free. */
            free(unreached);
            vm->numObjects--;
        }
        else
        {
            /* Reset marked object. */
            (*listptr)->marked = 0;

            /* Advance the listptr. */
            listptr = &(*listptr)->next;
        }
    }
}

void collect_garbage(VM* vm)
{
    int numObjects = vm->numObjects;

    markAll(vm);
    sweep(vm);

    /*
     * Now that the garbage is collected, we set maxObjects to double
     * the amount of objects left.
     */
    vm->maxObjects = vm->numObjects * 2;
}
