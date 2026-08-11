#include <shmem.h>
#include <shmemg.h>
#include <stdint.h>

#define MSG_LEN 256

__global__ void producer(char *dest, const char *src,
                         uint64_t *sig, int peer) {
    shmemg_putmem_signal(dest, src, MSG_LEN, sig, 1,
                         SHMEM_SIGNAL_SET, peer);
    shmemg_quiet();
}

__global__ void consumer(const uint64_t *sig) {
    while (shmemg_signal_fetch(sig) == 0) { /* busy-wait for arrival */ }
    /* dest now holds the delivered message */
}

int main(void) {
    int provided;
    shmem_init_thread(SHMEM_THREAD_SINGLE | SHMEM_DEVICE_KERNEL_INIT,
                      &provided);
    if (!(provided & SHMEM_DEVICE_KERNEL_INIT))
        shmem_global_exit(1);

    int me = shmem_my_pe();

    char     *dest = (char *)shmemg_malloc(MSG_LEN);
    char     *src  = (char *)shmemg_malloc(MSG_LEN);
    uint64_t *sig  = (uint64_t *)shmemg_calloc(1, sizeof(uint64_t));
    /* Initialize src on the GPU (vendor-specific) */

    shmem_barrier_all();

    if (me == 0)
        producer<<<1, 1>>>(dest, src, sig, 1);
    else if (me == 1)
        consumer<<<1, 1>>>(sig);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();

    shmemg_free(sig);
    shmemg_free(src);
    shmemg_free(dest);
    shmem_finalize();
    return 0;
}
