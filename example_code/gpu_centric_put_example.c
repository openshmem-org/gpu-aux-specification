#include <shmem.h>
#include <shmemg.h>

__global__ void put_kernel(int *dest, int *source, int pe) {
    shmemg_putmem(dest, source, sizeof(int), pe);
    shmemg_quiet();
}

int main(void) {
    int provided;
    int requested = SHMEM_THREAD_SINGLE | SHMEM_DEVICE_KERNEL_INIT;

    /* Select GPU before initializing OpenSHMEM */
    /* e.g., cudaSetDevice(0); */

    shmem_init_thread(requested, &provided);
    if (!(provided & SHMEM_DEVICE_KERNEL_INIT)) {
        fprintf(stderr, "GPU-centric support not available\n");
        shmem_global_exit(1);
    }

    int me = shmem_my_pe();
    int npes = shmem_n_pes();
    int next_pe = (me + 1) % npes;

    int *d_buf = (int *)shmemg_malloc(sizeof(int));
    int *d_src = (int *)shmemg_malloc(sizeof(int));

    /* Initialize d_src on GPU (vendor-specific) */

    put_kernel<<<1, 1>>>(d_buf, d_src, next_pe);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();

    shmemg_free(d_src);
    shmemg_free(d_buf);
    shmem_finalize();
    return 0;
}
