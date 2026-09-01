#include <shmem.h>
#include <shmemg.h>

__global__ void ring_store(long *dest, long value, int peer) {
    long *rptr = (long *)shmemg_ptr(dest, peer);
    if (rptr != NULL) {
        *rptr = value;          /* direct store into the neighbor's buffer */
    } else {
        shmemg_putmem(dest, &value, sizeof(long), peer);
        shmemg_quiet();         /* fall back to RMA when not accessible */
    }
}

int main(void) {
    int provided;
    shmem_init_thread(SHMEM_THREAD_SINGLE | SHMEM_DEVICE_KERNEL_INIT,
                      &provided);
    if (!(provided & SHMEM_DEVICE_KERNEL_INIT))
        shmem_global_exit(1);

    int me   = shmem_my_pe();
    int npes = shmem_n_pes();
    int peer = (me + 1) % npes;

    long *dest = (long *)shmemg_malloc(sizeof(long));

    ring_store<<<1, 1>>>(dest, (long)me, peer);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();  /* dest now holds the left neighbor's value */

    shmemg_free(dest);
    shmem_finalize();
    return 0;
}
