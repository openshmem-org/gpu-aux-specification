#include <shmem.h>
#include <shmemg.h>

__global__ void notifier(long *flag, const long *val, int peer) {
    shmemg_putmem(flag, val, sizeof(long), peer);
    shmemg_quiet();
}

__global__ void waiter(long *flag) {
    shmemg_long_wait_until(flag, SHMEM_CMP_EQ, 1);
    /* the flag has been set by PE 0 */
}

int main(void) {
    int provided;
    shmem_init_thread(SHMEM_THREAD_SINGLE | SHMEM_DEVICE_KERNEL_INIT,
                      &provided);
    if (!(provided & SHMEM_DEVICE_KERNEL_INIT))
        shmem_global_exit(1);

    int me = shmem_my_pe();

    long *flag = (long *)shmemg_calloc(1, sizeof(long));
    long *val  = (long *)shmemg_malloc(sizeof(long));
    /* Initialize *val = 1 on the GPU (vendor-specific) */

    shmem_barrier_all();

    if (me == 0)
        notifier<<<1, 1>>>(flag, val, 1);
    else if (me == 1)
        waiter<<<1, 1>>>(flag);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();

    shmemg_free(val);
    shmemg_free(flag);
    shmem_finalize();
    return 0;
}
