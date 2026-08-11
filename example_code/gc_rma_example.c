#include <shmem.h>
#include <shmemg.h>

__global__ void ring_put(long *dest, const long *src, int peer) {
    shmemg_putmem(dest, src, sizeof(long), peer);
    shmemg_quiet();  /* wait for the put to complete remotely */
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
    /* Initialize src on the GPU (vendor-specific), e.g., *src = me */

    ring_put<<<1, 1>>>(dest, src, peer);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();  /* dest now holds the left neighbor's value */

    shmemg_free(src);
    shmemg_free(dest);
    shmem_finalize();
    return 0;
}
