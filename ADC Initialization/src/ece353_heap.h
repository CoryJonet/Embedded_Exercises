#ifndef __ECE353_HEAP_H__
#define __ECE353_HEAP_H__

#include <stdint.h>

#define HEAP_INIT_VAL               0xFF
#define HEAP_FREE_VAL               0xBB
#define ALLOCATED                   0xABCD
#define NOT_ALLOCATED               0x0000
#define HEAP_SUCCESS                0x00000000
#define HEAP_ERR_HEAD_NULL          0x00000100
#define HEAP_ERR_NO_SPACE           0x00000200
#define HEAP_ERR_INVALID_SIZE       0x00000300
#define HEAP_ERR_INIT               0x00000400
#define NULL                        0


typedef struct heapBlock heapBlock;

struct heapBlock{
    uint16_t    allocated;
    uint16_t    size;
};

extern uint8_t* getHeapBase(void);
extern uint8_t* getHeapSize(void);
uint32_t ece353HeapInit (uint8_t *pHeap, uint16_t bytes);
heapBlock * ece353SplitBlock(heapBlock *block, uint16_t bytes);
uint8_t * ece353HeapAlloc(uint8_t *pHeap, uint16_t bytes);
void ece353HeapFree(uint8_t *block);
extern ece353HeapCoalesce(uint8_t *heapBase, uint16_t heapSize);

#endif

