#include <shmem.h>
#include <shmemg.h>
#include <stdio.h>

int main(void) {
    int provided;
    int requested = SHMEM_THREAD_SINGLE | SHMEM_DEVICE_HOST_INIT;

    /* Select GPU before initializing OpenSHMEM */
    /* e.g., cudaSetDevice(0); */

    shmem_init_thread(requested, &provided);
    if (!(provided & SHMEM_DEVICE_HOST_INIT)) {
        fprintf(stderr, "GPU-aware support not available\n");
        shmem_global_exit(1);
    }

    int me = shmem_my_pe();
    int npes = shmem_n_pes();

    int *d_buf = (int *)shmemg_malloc(sizeof(int));

    if (me == 0) {
        int value = 42;
        shmem_int_put(d_buf, &value, 1, 1);
    }

    shmem_barrier_all();

    shmemg_free(d_buf);
    shmem_finalize();
    return 0;
}
