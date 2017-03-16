#include <assert.h>
#include "mp_alloc.h"

int main(int argc, char *argv[]) {

    int size = 1 << 12;
    printf("size:%d\n",size);
    mp_pool_t *p = mp_create_pool(size);

    int i; 
    int j;

    for (i = 0; i < 50; i++) {
        void *t=mp_alloc(p, 256);
	assert(t!=NULL);
    }

    for (i = 0; i < 10; i++) {
        char *pp = mp_calloc(p, 32);
        for (j = 0; j < 32; j++) {
            if (pp[j]) {
                printf("calloc wrong\n");
            }
        }
    }

    for ( i = 0; i < 5; i++) {
        void * l =  mp_alloc(p, 8192);
		assert(l!=NULL);

        mp_free(p, l);
    }

	void * l =  mp_alloc(p, 10000);
	memset(l,0x00,10000);
	
	assert(l!=NULL);

    mp_reset_pool(p);

    for (i = 0; i < 58; i++) {
        mp_alloc(p, 256);
    }

    mp_destroy_pool(p);
    printf("ok\n");


    return 0;

}
