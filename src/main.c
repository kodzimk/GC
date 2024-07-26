#include<stdio.h>
#include<stdlib.h>

#define STACK_MAX_SIZE 256
#define IGCT 8

typedef enum
{
    INT,
    TWIN,
}oType;

typedef struct sObject
{
    oType type;
    unsigned char marked;

    struct sObject* next;

    union {
        int value;

        struct {
            struct sObject* head;
            struct sObject* tile;
        };
    };
}Object;

typedef struct
{
    Object* stack[STACK_MAX_SIZE];
    int stazkSize;

    Object* firstObject;

    int numObjects;
    int maxObjects;

}vm;

void push(vm* vm, Object* value)
{
    vm->stack[vm->stazkSize] = value;
}

Object* pop(vm* vm)
{
    return vm->stack[--vm->stazkSize];
}

vm* newVm()
{
    vm* mainVm = (vm*)malloc(sizeof(vm));
    mainVm->stazkSize = 0;
    mainVm->firstObject = NULL;
    mainVm->numObjects = 0;
    mainVm->maxObjects = IGCT;
    return mainVm;
}

void mark(Object* object)
{
    if (object->marked)
        return;

    object->marked = 1;

    if (object->type = TWIN)
    {
        mark(object->head);
        mark(object->tile);
    }
}


void markAll(vm* vm)
{
    for (int i = 0; i < vm->stazkSize; i++)
    {
        mark(vm->stack[i]);
    }
}

void mark_sweep(vm* vm)
{
    Object** object = &vm->firstObject;
    while (*object)
    {
        if (!(*object)->marked)
        {
            Object* unreached = *object;
            *object = unreached->next;
            free(unreached);

            vm->numObjects--;
        }
        else
        {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}


void gc(vm* vm)
{
    int numObjects = vm->numObjects;

    markAll(vm);
    mark_sweep(vm);

    vm->maxObjects = vm->numObjects * 2;
}

Object* newObject(vm* vm, oType type)
{
    if (vm->numObjects == vm->maxObjects)gc(vm);
    Object* object = (Object*)malloc(sizeof(Object));
    object->type = type;

    vm->numObjects++;
    return object;
}

void pushInt(vm* vm, int intV)
{
    Object* object = newObject(vm, INT);
    object->value = intV;
    push(vm, object);
}

Object* pushTwin(vm* vm)
{
    Object* object = newObject(vm, TWIN);
    object->tile = pop(vm);
    object->head = pop(vm);
    push(vm, object);

    return object;
}






int main(int ardv, char** argc)
{
    printf("sas");
    printf("sas");
    printf("sas");
    printf("sas");
    printf("sas");
    printf("sas");
   	return 0;
}