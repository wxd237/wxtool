
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "wxslab.h"


#define POWEROF2(x) ((x) != 0 && ((x) & ((x) - 1)) == 0)
#define SLOTS_FIRST ((uint64_t) 1)
#define SLOTS_ALL_ZERO ((uint64_t) 0)

void slab_init(struct wxslab_chain *const sch, const size_t itemsize)
{
    assert(sch != NULL);
    assert(itemsize >= 1 && itemsize <= SIZE_MAX);
    assert(POWEROF2(wxslab_pagesize));

    sch->itemsize = itemsize;

    const size_t data_offset = offsetof(struct wxslab_header, data);
    const size_t least_slabsize = data_offset + 64 * sch->itemsize;
    sch->slabsize = (size_t) 1 << (size_t) ceil(log2(least_slabsize));
    sch->itemcount = 64;

    if (sch->slabsize - least_slabsize != 0) {
        const size_t shrinked_slabsize = sch->slabsize >> 1;

        if (data_offset < shrinked_slabsize &&
            shrinked_slabsize - data_offset >= 2 * sch->itemsize) {

            sch->slabsize = shrinked_slabsize;
            sch->itemcount = (shrinked_slabsize - data_offset) / sch->itemsize;
        }
    }

    sch->pages_per_alloc = sch->slabsize > wxslab_pagesize ?
        sch->slabsize : wxslab_pagesize;

    sch->empty_slotmask = ~SLOTS_ALL_ZERO >> (64 - sch->itemcount);
    sch->initial_slotmask = sch->empty_slotmask ^ SLOTS_FIRST;
    sch->alignment_mask = ~(sch->slabsize - 1);
    sch->partial = sch->empty = sch->full = NULL;

//    assert(slab_is_valid(sch));
}
