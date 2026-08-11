#include <shmem.h>
#include <shmemg.h>

__global__ void put_and_sync(long *dest, const long *src, int peer) {
    shmemg_putmem(dest, src, sizeof(long), peer);
    shmemg_quiet();     /* complete the remote update before synchronizing */
    shmemg_sync_all();  /* barrier over SHMEM_DEVICE_TEAM_WORLD */
    /* every PE's dest now holds its neighbor's contribution */
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
    long *src  = (long *)shmemg_malloc(sizeof(long));
    /* Initialize src on the GPU (vendor-specific) */

    put_and_sync<<<1, 1>>>(dest, src, peer);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();

    shmemg_free(src);
    shmemg_free(dest);
    shmem_finalize();
    return 0;
}
