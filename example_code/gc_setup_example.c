#include <shmem.h>
#include <shmemg.h>

__global__ void query_kernel(int *out) {
    out[0] = shmemg_my_pe();
    out[1] = shmemg_n_pes();
}

int main(void) {
    int provided;
    shmem_init_thread(SHMEM_THREAD_SINGLE | SHMEM_DEVICE_KERNEL_INIT,
                      &provided);
    if (!(provided & SHMEM_DEVICE_KERNEL_INIT))
        shmem_global_exit(1);

    /* out resides in the GPU symmetric heap so the kernel can write to it */
    int *out = (int *)shmemg_malloc(2 * sizeof(int));

    query_kernel<<<1, 1>>>(out);
    /* cudaDeviceSynchronize(); */

    /* out[0] == shmem_my_pe(), out[1] == shmem_n_pes() */

    shmemg_free(out);
    shmem_finalize();
    return 0;
}
