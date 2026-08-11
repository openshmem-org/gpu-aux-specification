#include <shmem.h>
#include <shmemg.h>

__global__ void take_ticket(long *counter, long *ticket, int root) {
    /* Returns this PE's unique ticket; a non-fetching update would
       instead use shmemg_long_atomic_add(counter, 1, root). */
    *ticket = shmemg_long_atomic_fetch_add(counter, 1, root);
}

int main(void) {
    int provided;
    shmem_init_thread(SHMEM_THREAD_SINGLE | SHMEM_DEVICE_KERNEL_INIT,
                      &provided);
    if (!(provided & SHMEM_DEVICE_KERNEL_INIT))
        shmem_global_exit(1);

    long *counter = (long *)shmemg_calloc(1, sizeof(long));
    long *ticket  = (long *)shmemg_malloc(sizeof(long));

    shmem_barrier_all();  /* counter initialized to 0 on every PE */

    take_ticket<<<1, 1>>>(counter, ticket, 0);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();

    shmemg_free(ticket);
    shmemg_free(counter);
    shmem_finalize();
    return 0;
}
