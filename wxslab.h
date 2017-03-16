#pragma once

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

extern size_t wxslab_pagesize;

struct wxslab_header {                               //page header 
    struct slab_header *prev, *next;
    uint64_t slots;
    uintptr_t refcount;
    struct wxslab_header *page;
    uint8_t data[] __attribute__((aligned(sizeof(void *))));    //data area
};

struct wxslab_chain {
    size_t itemsize, itemcount;
    size_t slabsize, pages_per_alloc;
    uint64_t initial_slotmask, empty_slotmask;
    uintptr_t alignment_mask;
    struct slab_header *partial, *empty, *full;
};

void wxslab_init(struct wxslab_chain *, size_t);
void *wxslab_alloc(struct wxslab_chain *);
void wxslab_free(struct wxslab_chain *, const void *);
void wxslab_traverse(const struct wxslab_chain *, void (*)(const void *));
void wxslab_destroy(const struct wxslab_chain *);
