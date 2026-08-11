#include <shmem.h>
#include <shmemg.h>

__global__ void put_on_ctx(shmem_ctx_t ctx, int *dest,
                           const int *src, int peer) {
    shmemg_ctx_putmem(ctx, dest, src, sizeof(int), peer);
    shmemg_ctx_quiet(ctx);
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

    /* Device contexts must be created on the host from the device team. */
    shmem_ctx_t ctx;
    if (shmem_team_create_ctx(SHMEM_DEVICE_TEAM_WORLD,
                              SHMEM_DEVICE_CTX, &ctx) != 0)
        shmem_global_exit(1);

    int *dest = (int *)shmemg_malloc(sizeof(int));
    int *src  = (int *)shmemg_malloc(sizeof(int));
    /* Initialize src on the GPU (vendor-specific) */

    put_on_ctx<<<1, 1>>>(ctx, dest, src, peer);
    /* cudaDeviceSynchronize(); */

    shmem_barrier_all();

    shmem_ctx_destroy(ctx);   /* destroy the device context on the host */
    shmemg_free(src);
    shmemg_free(dest);
    shmem_finalize();
    return 0;
}
