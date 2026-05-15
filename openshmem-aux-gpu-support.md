# OpenSHMEM Auxiliary Specification for GPU Support

> **Version 0.1** | Based on OpenSHMEM 1.6

---

## Table of Contents

- [OpenSHMEM Auxiliary Specification for GPU Support](#openshmem-auxiliary-specification-for-gpu-support)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Relationship to OpenSHMEM](#relationship-to-openshmem)
  - [Specification Scope](#specification-scope)
  - [Execution Model](#execution-model)
    - [Processing Elements and GPU Association](#processing-elements-and-gpu-association)
    - [GPU Symmetric Heap](#gpu-symmetric-heap)
  - [Communication Model](#communication-model)
    - [GPU-Aware Communication](#gpu-aware-communication)
    - [GPU-Centric Communication](#gpu-centric-communication)
    - [Supported Operations](#supported-operations)
    - [Ordering and Completion](#ordering-and-completion)
  - [Team Management](#team-management)
    - [Predefined Device Teams](#predefined-device-teams)
      - [SHMEM\_DEVICE\_TEAM\_WORLD](#shmem_device_team_world)
      - [SHMEM\_DEVICE\_TEAM\_SHARED](#shmem_device_team_shared)
    - [Atomicity Domains](#atomicity-domains)
  - [Context Management](#context-management)
    - [Default Device Context](#default-device-context)
    - [Context Separation](#context-separation)
  - [Language Bindings and Conformance](#language-bindings-and-conformance)
  - [Compatibility](#compatibility)
  - [Library Constants](#library-constants)
  - [Library Handles](#library-handles)
  - [Environment Variables](#environment-variables)
  - [Initialization and Memory Management](#initialization-and-memory-management)
    - [shmem\_init\_thread](#shmem_init_thread)
      - [Synopsis](#synopsis)
      - [Arguments](#arguments)
      - [Description](#description)
      - [Return Values](#return-values)
      - [Notes](#notes)
    - [Memory Management](#memory-management)
      - [shmemg\_malloc](#shmemg_malloc)
        - [Synopsis](#synopsis-1)
        - [Arguments](#arguments-1)
        - [Description](#description-1)
        - [Return Values](#return-values-1)
      - [shmemg\_calloc](#shmemg_calloc)
        - [Synopsis](#synopsis-2)
        - [Arguments](#arguments-2)
        - [Description](#description-2)
        - [Return Values](#return-values-2)
      - [shmemg\_align](#shmemg_align)
        - [Synopsis](#synopsis-3)
        - [Arguments](#arguments-3)
        - [Description](#description-3)
        - [Return Values](#return-values-3)
      - [shmemg\_free](#shmemg_free)
        - [Synopsis](#synopsis-4)
        - [Arguments](#arguments-4)
        - [Description](#description-4)
        - [Return Values](#return-values-4)
  - [GPU-Aware Communication](#gpu-aware-communication-1)
    - [Remote Memory Access (RMA)](#remote-memory-access-rma)
      - [Blocking Put](#blocking-put)
      - [Scalar Put](#scalar-put)
      - [Strided Put](#strided-put)
      - [Nonblocking Put](#nonblocking-put)
      - [Blocking Get](#blocking-get)
      - [Scalar Get](#scalar-get)
      - [Strided Get](#strided-get)
      - [Nonblocking Get](#nonblocking-get)
    - [Atomic Memory Operations (AMO)](#atomic-memory-operations-amo)
      - [Non-fetching AMOs](#non-fetching-amos)
      - [Fetching AMOs](#fetching-amos)
      - [Nonblocking AMOs](#nonblocking-amos)
    - [Signaling Operations](#signaling-operations)
      - [Put-with-Signal](#put-with-signal)
      - [Nonblocking Put-with-Signal](#nonblocking-put-with-signal)
      - [Signal Fetch](#signal-fetch)
    - [Point-to-Point Synchronization](#point-to-point-synchronization)
      - [Wait-Until](#wait-until)
      - [Wait-Until (Array Variants)](#wait-until-array-variants)
      - [Test](#test)
      - [Test (Array Variants)](#test-array-variants)
      - [Signal-Wait-Until](#signal-wait-until)
      - [Memory Ordering](#memory-ordering)
        - [shmem\_fence](#shmem_fence)
          - [Synopsis](#synopsis-5)
          - [Arguments](#arguments-5)
          - [Description](#description-5)
          - [Return Values](#return-values-5)
          - [Notes](#notes-1)
          - [Example](#example)
        - [shmem\_quiet](#shmem_quiet)
          - [Synopsis](#synopsis-6)
          - [Arguments](#arguments-6)
          - [Description](#description-6)
          - [Return Values](#return-values-6)
          - [Notes](#notes-2)
          - [Example](#example-1)
        - [shmem\_put\_signal](#shmem_put_signal)
          - [Synopsis](#synopsis-7)
          - [Arguments](#arguments-7)
          - [Description](#description-7)
          - [Return Values](#return-values-7)
          - [Notes](#notes-3)
          - [Example](#example-2)
        - [Global Synchronization](#global-synchronization)
          - [Synopsis](#synopsis-8)
          - [Arguments](#arguments-8)
          - [Description](#description-8)
          - [Return Values](#return-values-8)
          - [Notes](#notes-4)
  - [GPU-Centric Communication](#gpu-centric-communication-1)
    - [Library Setup and Query](#library-setup-and-query)
      - [shmemg\_my\_pe](#shmemg_my_pe)
        - [Synopsis](#synopsis-9)
        - [Arguments](#arguments-9)
        - [Description](#description-9)
        - [Return Values](#return-values-9)
        - [Notes](#notes-5)
      - [shmemg\_n\_pes](#shmemg_n_pes)
        - [Synopsis](#synopsis-10)
        - [Arguments](#arguments-10)
        - [Description](#description-10)
        - [Return Values](#return-values-10)
        - [Notes](#notes-6)
    - [Context Management](#context-management-1)
    - [Communication Operations](#communication-operations)
      - [Remote Memory Access (RMA)](#remote-memory-access-rma-1)
        - [Blocking Put](#blocking-put-1)
          - [Synopsis](#synopsis-11)
          - [Arguments](#arguments-11)
          - [Description](#description-11)
          - [Return Values](#return-values-11)
        - [Nonblocking Put](#nonblocking-put-1)
          - [Synopsis](#synopsis-12)
          - [Arguments](#arguments-12)
          - [Description](#description-12)
          - [Return Values](#return-values-12)
        - [Blocking Get](#blocking-get-1)
          - [Synopsis](#synopsis-13)
          - [Arguments](#arguments-13)
          - [Description](#description-13)
          - [Return Values](#return-values-13)
        - [Nonblocking Get](#nonblocking-get-1)
          - [Synopsis](#synopsis-14)
          - [Arguments](#arguments-14)
          - [Description](#description-14)
          - [Return Values](#return-values-14)
      - [Atomic Memory Operations (AMO)](#atomic-memory-operations-amo-1)
        - [Non-fetching AMOs](#non-fetching-amos-1)
          - [Synopsis](#synopsis-15)
          - [Arguments](#arguments-15)
          - [Description](#description-15)
          - [Return Values](#return-values-15)
        - [Fetching AMOs](#fetching-amos-1)
          - [Synopsis](#synopsis-16)
          - [Arguments](#arguments-16)
          - [Description](#description-16)
          - [Return Values](#return-values-16)
        - [Nonblocking Fetching AMOs](#nonblocking-fetching-amos)
          - [Synopsis](#synopsis-17)
          - [Arguments](#arguments-17)
          - [Description](#description-17)
          - [Return Values](#return-values-17)
      - [Signaling Operations](#signaling-operations-1)
        - [Put-with-Signal](#put-with-signal-1)
          - [Synopsis](#synopsis-18)
          - [Arguments](#arguments-18)
          - [Description](#description-18)
          - [Return Values](#return-values-18)
          - [Notes](#notes-7)
        - [Nonblocking Put-with-Signal](#nonblocking-put-with-signal-1)
          - [Synopsis](#synopsis-19)
          - [Arguments](#arguments-19)
          - [Description](#description-19)
          - [Return Values](#return-values-19)
        - [Signal-Fetch](#signal-fetch-1)
          - [Synopsis](#synopsis-20)
          - [Arguments](#arguments-20)
          - [Description](#description-20)
          - [Return Values](#return-values-20)
      - [Point-to-Point Synchronization](#point-to-point-synchronization-1)
        - [Wait-Until](#wait-until-1)
          - [Synopsis](#synopsis-21)
          - [Arguments](#arguments-21)
          - [Description](#description-21)
          - [Return Values](#return-values-21)
        - [Test](#test-1)
          - [Synopsis](#synopsis-22)
          - [Arguments](#arguments-22)
          - [Description](#description-22)
          - [Return Values](#return-values-22)
        - [Signal-Wait-Until](#signal-wait-until-1)
          - [Synopsis](#synopsis-23)
          - [Arguments](#arguments-23)
          - [Description](#description-23)
          - [Return Values](#return-values-23)
      - [Memory Ordering](#memory-ordering-1)
        - [shmemg\_fence](#shmemg_fence)
          - [Synopsis](#synopsis-24)
          - [Arguments](#arguments-24)
          - [Description](#description-24)
          - [Return Values](#return-values-24)
          - [Notes](#notes-8)
        - [shmemg\_quiet](#shmemg_quiet)
          - [Synopsis](#synopsis-25)
          - [Arguments](#arguments-25)
          - [Description](#description-25)
          - [Return Values](#return-values-25)
          - [Notes](#notes-9)
      - [Collective Operations](#collective-operations)
        - [shmemg\_sync\_all](#shmemg_sync_all)
          - [Synopsis](#synopsis-26)
          - [Arguments](#arguments-26)
          - [Description](#description-26)
          - [Return Values](#return-values-26)
        - [shmemg\_team\_sync](#shmemg_team_sync)
          - [Synopsis](#synopsis-27)
          - [Arguments](#arguments-27)
          - [Description](#description-27)
          - [Return Values](#return-values-27)
- [Annex A Writing OpenSHMEM GPU Program](#annex-a-writing-openshmem-gpu-program)
- [Annex B Compiling and Running OpenSHMEM GPU Program](#annex-b-compiling-and-running-openshmem-gpu-program)
- [Annex C Undefined Behavior in OpenSHMEM GPU Support](#annex-c-undefined-behavior-in-openshmem-gpu-support)
- [Annex D History of GPU Support in OpenSHMEM](#annex-d-history-of-gpu-support-in-openshmem)
- [Annex E Changes to this Document](#annex-e-changes-to-this-document)
- [Index](#index)

---

## Introduction

OpenSHMEM Auxiliary Specification for GPU Support defines extensions to the OpenSHMEM library interface specification for GPU-aware and GPU-centric communication. These extensions allow OpenSHMEM implementations to use GPU-attached memory buffers for remote memory access, atomic memory operations, and synchronization while maintaining compatibility with the core OpenSHMEM programming model.

Two communication paradigms are defined:

> **GPU-Aware Communication**
> A programming model in which GPU-attached memory buffers may be used as source or destination operands in OpenSHMEM operations. The host PE invokes OpenSHMEM routines, and the implementation shall manage data transfers involving GPU-attached memory.

> **GPU-Centric Communication**
> A programming model in which communication operations may be initiated directly from GPU execution contexts, such as device kernels. GPU threads invoke OpenSHMEM routines without host-side intervention.

## Relationship to OpenSHMEM

The OpenSHMEM Auxiliary Specification for GPU Support is based on the OpenSHMEM specification version 1.6. It supplements, but does not replace, the OpenSHMEM 1.6 specification. All routines, semantics, and requirements defined in OpenSHMEM 1.6 remain valid. Where new concepts are introduced or existing semantics are modified, such changes are explicitly identified.

The extensions maintain the fundamental principles established by the OpenSHMEM specification, including:
- Processing elements (PEs) and symmetric data objects
- Team-based process subsets and communication contexts
- Memory ordering and synchronization guarantees
- Collective and point-to-point communication semantics

Implementation of these extensions is optional. An OpenSHMEM implementation may support GPU-aware communication, GPU-centric communication, both, or neither. Applications may query implementation capabilities at runtime.

Applications that do not utilize GPU-attached memory buffers or the interfaces defined herein shall continue to execute correctly.

---

## Specification Scope

The following are defined:
- Extensions to the OpenSHMEM memory model to support a GPU symmetric heap allocated from GPU-attached memory
- Host-side interfaces for allocating and managing symmetric data objects within the GPU symmetric heap
- Device-side interfaces for initiating communication operations from GPU execution contexts (GPU kernels)
- Semantics for data movement, atomic memory operations, and synchronization involving GPU-attached symmetric memory
- Query interfaces for discovering implementation capabilities and symmetric memory object properties
- Requirements for memory ordering and coherence when both the default and GPU symmetric heaps are in use

The following are **not** defined:
- GPU programming models, device kernel languages, or GPU runtime APIs
- Mechanisms for selecting or assigning GPUs to processing elements
- Specific GPU architectures, vendor-specific features, or device driver interfaces
- Performance characteristics, optimization requirements, or benchmarking methodologies
- Network hardware capabilities, protocols, or transport-layer mechanisms
- Extensions for non-GPU accelerators (FPGAs, DSPs, etc.)

---

## Execution Model

The execution model defined by the OpenSHMEM specification is extended by the introduction of a GPU symmetric heap allocated from GPU-attached memory. This GPU symmetric heap is distinct from, and in addition to, the default symmetric heap defined by the OpenSHMEM specification.

### Processing Elements and GPU Association

The concept of a processing element (PE) is defined by the OpenSHMEM specification. Each PE that utilizes the GPU support defined by this specification shall be associated with exactly one GPU. The association between a PE and its GPU shall be established during initialization of the OpenSHMEM library and shall remain fixed for the duration of the program.

The mechanism by which a GPU is selected for association with a PE is outside the scope of this specification. The application or runtime environment shall select the GPU prior to initialization of the OpenSHMEM library. The OpenSHMEM implementation shall use the GPU that has been made current or otherwise designated by the execution environment at the time of library initialization.

> **Constraint:** A PE shall not be associated with more than one GPU. A PE that has no associated GPU shall not invoke the GPU interfaces defined herein. All PEs in the OpenSHMEM program shall have a valid PE-to-GPU association to use these interfaces.

### GPU Symmetric Heap

The GPU symmetric heap is distributed across PEs, with each PE's allocation residing in the memory of its associated GPU. Routines are provided for allocating and managing the GPU symmetric heap from the host, and for performing one-sided read (get), write (put), and atomic memory operations on symmetric objects within it from both the host and GPU execution contexts. These routines follow the partitioned global address space (PGAS) programming model established by the OpenSHMEM specification.

---

## Communication Model

The one-sided communication semantics defined by the OpenSHMEM specification apply to symmetric objects allocated from the GPU symmetric heap. All routines defined in OpenSHMEM 1.6—including RMA, AMO, signaling, synchronization, and collective operations—retain their specified behavior and may be used with GPU-attached memory buffers.

The remote operand in a communication operation may reside in either the default symmetric heap or the GPU symmetric heap. The same OpenSHMEM routine shall be used regardless of whether the remote memory is CPU-attached or GPU-attached.

### GPU-Aware Communication

GPU-aware communication allows GPU-attached memory buffers to be used as operands in existing OpenSHMEM routines without modification to interfaces or calling conventions. GPU-attached memory buffers may be used as:

- **Source operands** in put operations
- **Destination operands** in get operations
- **Local operands** in atomic memory operations
- **Target buffers** in point-to-point synchronization operations
- **Local buffers** in collective operations

The OpenSHMEM implementation shall manage data movement between the GPU memory hierarchy and the network interface. The completion and ordering semantics defined in OpenSHMEM 1.6 shall apply.

### GPU-Centric Communication

GPU-centric communication allows GPU threads to invoke put, get, and atomic memory operations directly from GPU execution contexts. Device-initiated operations use the same addressing model defined by the OpenSHMEM specification: a symmetric address and a target PE identifier. The symmetric address shall be the address returned by the GPU symmetric heap allocation routine and is valid only at the PE where the allocation was performed.

> **Note:** Support for GPU-centric communication is independent of support for GPU-aware communication; an implementation may support either or both.

### Supported Operations

The following operations are supported on symmetric objects in the GPU symmetric heap:

| Operation | Description |
|---|---|
| **Remote Memory Access (RMA)** | Put and get operations, including bulk and scalar variants |
| **Atomic Memory Operations (AMO)** | Fetch-and-operate and compare-and-swap variants |
| **Signaling Operations** | Combined data transfer and signal update at the target PE |
| **Synchronization** | Barrier, fence, quiet, and point-to-point wait/test primitives |

### Ordering and Completion

Ordering and completion semantics follow the OpenSHMEM memory model. Updates to symmetric objects are unordered by default. A PE may enforce point-to-point ordering using `shmem_fence` and global ordering using `shmem_quiet`. Barrier and point-to-point wait/test operations may be used to coordinate access across PEs.

---

## Team Management

Two predefined device teams supplement the predefined teams defined by the OpenSHMEM specification, `SHMEM_TEAM_WORLD` and `SHMEM_TEAM_SHARED`. The existing `shmem_team_split_*` routines may be used with device teams as parent teams.

### Predefined Device Teams

#### SHMEM_DEVICE_TEAM_WORLD

`SHMEM_DEVICE_TEAM_WORLD` is a predefined team of type `shmem_team_t` that contains all PEs in the OpenSHMEM program that have a valid PE-to-GPU association. `SHMEM_DEVICE_TEAM_WORLD` is a separate predefined team from `SHMEM_TEAM_WORLD`. Because all PEs are required to have a valid PE-to-GPU association (see Processing Elements and GPU Association), the set of member PEs in `SHMEM_DEVICE_TEAM_WORLD` is the same as the set of member PEs in `SHMEM_TEAM_WORLD`.

#### SHMEM_DEVICE_TEAM_SHARED

`SHMEM_DEVICE_TEAM_SHARED` is a predefined team of type `shmem_team_t` that corresponds to the set of PEs that share a GPU memory domain. `SHMEM_DEVICE_TEAM_SHARED` refers to the team of all PEs that would mutually return a non-null address from a call to `shmem_ptr` or `shmem_team_ptr` for all GPU symmetric heap objects. That is, `shmem_ptr` and `shmem_team_ptr` must return a non-null pointer to the local PE for all GPU symmetric heap objects on all target PEs in the team. This means that GPU symmetric heap objects on each PE are directly load/store accessible by all PEs in the team.

`SHMEM_DEVICE_TEAM_SHARED` may or may not correspond to the same set of PEs as `SHMEM_TEAM_SHARED`. The membership of `SHMEM_DEVICE_TEAM_SHARED` depends on the GPU memory topology, which may differ from the CPU memory topology that determines `SHMEM_TEAM_SHARED`.

### Atomicity Domains

The OpenSHMEM specification defines an atomicity domain as a set of communication contexts whose associated teams are all split by (possibly recursive) calls to a `shmem_team_split_*` routine from a common predefined team. The OpenSHMEM specification defines two predefined teams, `SHMEM_TEAM_WORLD` and `SHMEM_TEAM_SHARED`, each forming a separate atomicity domain.

Two additional predefined teams, `SHMEM_DEVICE_TEAM_WORLD` and `SHMEM_DEVICE_TEAM_SHARED`, each form a separate atomicity domain. These device atomicity domains are independent of each other and independent of the atomicity domains rooted at `SHMEM_TEAM_WORLD` and `SHMEM_TEAM_SHARED`.

> **Warning:** Atomic operations that use communication contexts in different atomicity domains to access the same location concurrently result in **undefined behavior**, as specified in the OpenSHMEM specification. This applies equally to contexts derived from device teams. For example, concurrent atomic operations on the same location using a context derived from `SHMEM_DEVICE_TEAM_WORLD` and a context derived from `SHMEM_TEAM_WORLD` result in undefined behavior.

---

## Context Management

The OpenSHMEM specification defines communication contexts as objects that allow the caller to manage the ordering and completion of communication operations. The context model is extended to support GPU-centric operations. Device contexts are created using the existing `shmem_ctx_create` and `shmem_team_create_ctx` routines with the `SHMEM_DEVICE_CTX` option.

### Default Device Context

`SHMEM_DEVICE_CTX_DEFAULT` is a predefined communication context of type `shmem_ctx_t` that serves as the default context for all GPU-centric operations. All GPU-centric communication operations and synchronizations that do not specify a context shall be performed on `SHMEM_DEVICE_CTX_DEFAULT`. The default device context is associated with `SHMEM_DEVICE_TEAM_WORLD`.

`SHMEM_DEVICE_CTX_DEFAULT` shall not be passed to `shmem_ctx_destroy`.

### Context Separation

Communication contexts are not shared between GPU-aware and GPU-centric operations.

| Context Type | Created With | Use For |
|---|---|---|
| Device context | `SHMEM_DEVICE_CTX` option | GPU-centric operations (from GPU kernels) |
| Host context | Without `SHMEM_DEVICE_CTX` (incl. `SHMEM_CTX_DEFAULT`) | GPU-aware or host-side operations |

> **Warning:** Using a device context for GPU-aware operations or a non-device context for GPU-centric operations results in **undefined behavior**.

---

## Language Bindings and Conformance

ISO C language bindings are provided. An implementation that provides C bindings for the interfaces defined herein may claim conformance to this auxiliary specification.

The header file `shmemg.h` shall contain the interfaces, types, and constant names defined herein. An OpenSHMEM program that uses the GPU extensions shall include `shmemg.h` in addition to `shmem.h`.

API routines use the `shmemg_` prefix. An OpenSHMEM program should avoid defining routine names, variables, or other identifiers with the prefix `shmemg` using any combination of uppercase letters, lowercase letters, and underscores.

---

## Compatibility

The extensions are backward compatible with OpenSHMEM 1.6. Applications that do not use GPU-attached memory or the interfaces defined herein shall execute correctly and without observable change in behavior. The GPU symmetric heap does not alter the behavior of existing routines when operating on CPU-attached memory from the default symmetric heap.

---

## Library Constants

The OpenSHMEM GPU specification provides a set of compile-time constants that may be used to specify options to API routines or provide implementation-specific parameters. These constants supplement the constants defined by the OpenSHMEM 1.6 specification.

| Constant | Description |
|---|---|
| `SHMEM_DEVICE_HOST_INIT` | Option to `shmem_init_thread` that requests GPU-aware communication support. When this option is provided, the implementation shall establish the PE-to-GPU association and prepare the runtime for GPU-aware operations on the GPU symmetric heap. An implementation may support `SHMEM_DEVICE_HOST_INIT`, `SHMEM_DEVICE_KERNEL_INIT`, both, or neither.|
| `SHMEM_DEVICE_KERNEL_INIT` | Option to `shmem_init_thread` that requests GPU-centric communication support. When this option is provided, the implementation shall prepare the runtime for communication operations invoked from within GPU kernels. An implementation may support `SHMEM_DEVICE_HOST_INIT`, `SHMEM_DEVICE_KERNEL_INIT`, both, or neither.|
| `SHMEM_DEVICE_CTX` | Context creation option that specifies the communication context shall support GPU-centric operations. A context created with this option may be used from within GPU execution contexts. Contexts created with `SHMEM_DEVICE_CTX` shall not be used for GPU-aware operations, and contexts created without this option shall not be used for GPU-centric operations. This option may be combined with other context creation options defined in OpenSHMEM 1.6, such as `SHMEM_CTX_SERIALIZED` or `SHMEM_CTX_PRIVATE`. |
| `SHMEM_DEVICE_MALLOC_HOST_INIT` | Hint to `shmem_malloc_with_hints` that specifies the allocated memory from the GPU symmetric heap will be used primarily by GPU-aware communication operations. Programs should use this hint when the majority of operations on the allocated memory are initiated from the host. The implementation may use this hint to optimize performance; if it cannot, the behavior shall be the same as an allocation without this hint. |
| `SHMEM_DEVICE_MALLOC_KERNEL_INIT` | Hint to `shmem_malloc_with_hints` that specifies the allocated memory from the GPU symmetric heap will be used primarily by GPU-centric communication operations invoked from within GPU kernels. Programs should use this hint when the majority of operations on the allocated memory are initiated from GPU execution contexts. The implementation may use this hint to optimize performance; if it cannot, the behavior shall be the same as an allocation without this hint. |

---

## Library Handles

The OpenSHMEM GPU specification provides a set of predefined named constant handles. All named constants may be used in initialization expressions or assignments. These handles supplement the handles defined by the OpenSHMEM 1.6 specification.

| Handle | Description |
|---|---|
| `SHMEM_DEVICE_TEAM_WORLD` | Handle of type `shmem_team_t` that corresponds to a team containing all PEs in the OpenSHMEM program that have a valid PE-to-GPU association. `SHMEM_DEVICE_TEAM_WORLD` shall be a subset of or equal to `SHMEM_TEAM_WORLD`. This handle may be used in collective operations and team-based communication routines that operate on the GPU symmetric heap. |
| `SHMEM_DEVICE_TEAM_SHARED` | Handle of type `shmem_team_t` that corresponds to a team of PEs that share a GPU memory domain. `SHMEM_DEVICE_TEAM_SHARED` may or may not correspond to the same set of PEs as `SHMEM_TEAM_SHARED`.|
| `SHMEM_DEVICE_CTX_DEFAULT` | Handle of type `shmem_ctx_t` that corresponds to the default communication context for GPU-centric operations. All GPU-centric communication operations and synchronizations that do not specify a context shall be performed on this default device context. `SHMEM_DEVICE_CTX_DEFAULT` shall not be used for GPU-aware operations. |

---

## Environment Variables

The OpenSHMEM GPU specification provides a set of environment variables that allows users to configure GPU-related aspects of the OpenSHMEM implementation. These variables supplement the environment variables defined by the OpenSHMEM 1.6 specification. Implementations are free to define additional GPU-related environment variables.

| Variable | Value | Description |
|---|---|---|
| `SHMEM_DEVICE_SYMMETRIC_SIZE` | Non-negative integer or floating-point value with an optional character suffix | Specifies the size (in bytes) of the GPU symmetric heap per PE. The GPU symmetric heap is allocated from GPU-attached memory on the GPU selected by the PE prior to library initialization. The resulting size is implementation-defined and shall be at least as large as the integer ceiling of the product of the numeric prefix and the scaling factor. The allowed character suffixes are: **k** or **K** ($2^{10}$, kibibytes), **m** or **M** ($2^{20}$, mebibytes), **g** or **G** ($2^{30}$, gibibytes), **t** or **T** ($2^{40}$, tebibytes). For example, the string "20m" is equivalent to the integer value 20971520, or 20 mebibytes. An invalid value for `SHMEM_DEVICE_SYMMETRIC_SIZE` is an error, which the OpenSHMEM library shall report by either returning a nonzero value from the initialization routine or causing program termination. |
| `SHMEM_DEVICE_MAX_CTX` | Non-negative integer | Specifies the maximum number of device communication contexts that may be created per PE. The implementation shall support at least the specified number of device contexts. If the value is zero, the implementation may limit device-initiated communication to the default device context (`SHMEM_DEVICE_CTX_DEFAULT`). An invalid value is an error, which the OpenSHMEM library shall report by either returning a nonzero value from the initialization routine or causing program termination. |

---

## Initialization and Memory Management

The routines in this section provide initialization, memory management, and query operations on the GPU symmetric heap.

> **Prerequisite:** Except for `shmem_init_thread`, all routines in this and subsequent sections require that the OpenSHMEM library has been initialized with GPU support by passing `SHMEM_DEVICE_HOST_INIT`, `SHMEM_DEVICE_KERNEL_INIT`, or both to `shmem_init_thread`, and that the corresponding capability was returned in `provided`. Calling any `shmemg_` routine without the required GPU initialization results in **undefined behavior**.

### shmem_init_thread

Initializes the OpenSHMEM library with support for the requested thread level and GPU communication capabilities.

#### Synopsis

```c
int shmem_init_thread(int requested, int *provided);
```

#### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `requested` | The thread level and GPU support requested by the application. The value is a bitwise OR of a thread level constant and zero or more GPU support constants. |
| OUT | `provided` | The thread level and GPU support provided by the implementation. |

The thread level portion of `requested` and `provided` shall be one of `SHMEM_THREAD_SINGLE`, `SHMEM_THREAD_FUNNELED`, `SHMEM_THREAD_SERIALIZED`, or `SHMEM_THREAD_MULTIPLE`, as defined in OpenSHMEM 1.6.

The GPU support portion of `requested` and `provided` may include one or both of the following constants, combined with the thread level using bitwise OR:

- `SHMEM_DEVICE_HOST_INIT` — requests GPU-aware communication support
- `SHMEM_DEVICE_KERNEL_INIT` — requests GPU-centric communication support

#### Description

`shmem_init_thread` is extended to accept GPU support options in the `requested` argument. When `SHMEM_DEVICE_HOST_INIT` is included in `requested`, the implementation shall establish the PE-to-GPU association and initialize the GPU symmetric heap for GPU-aware communication. When `SHMEM_DEVICE_KERNEL_INIT` is included, the implementation shall additionally prepare the runtime for GPU-centric communication operations invoked from within GPU kernels.

The `provided` argument returns the thread level and GPU support actually provided by the implementation. The GPU support bits in `provided` shall reflect only the capabilities that the implementation has successfully initialized. An implementation may provide a subset of the requested GPU support. For example, an application may request both `SHMEM_DEVICE_HOST_INIT` and `SHMEM_DEVICE_KERNEL_INIT`, but the implementation may provide only `SHMEM_DEVICE_HOST_INIT`.

If no GPU support constants are included in `requested`, the behavior of `shmem_init_thread` is unchanged from OpenSHMEM 1.6.

The application shall select the GPU for association with the PE prior to calling `shmem_init_thread`. The implementation shall use the GPU that has been made current by the execution environment at the time of the call.

All PEs shall provide the same GPU support constants in `requested`. If differing values are used, the behavior is undefined.

#### Return Values

`shmem_init_thread` returns 0 upon success; otherwise, it returns a nonzero value.

#### Notes

> **Important:** The application should compare the GPU support bits in `provided` against the requested bits to determine whether the desired GPU capabilities are available:
> - If `SHMEM_DEVICE_HOST_INIT` is **not** set in `provided` → do not use GPU-attached memory buffers in OpenSHMEM operations
> - If `SHMEM_DEVICE_KERNEL_INIT` is **not** set in `provided` → do not invoke OpenSHMEM routines from GPU kernels

### Memory Management

#### shmemg_malloc

Collectively allocate a block of memory from the GPU symmetric heap.

##### Synopsis

```c
void *shmemg_malloc(size_t size);
```

##### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `size` | The size, in bytes, of a block to be allocated from the GPU symmetric heap. |

##### Description

The `shmemg_malloc` routine is a collective operation on the world team that returns the symmetric address of a block of at least `size` bytes from the GPU symmetric heap. The returned address shall be suitably aligned so that it may be assigned to a pointer to any type of object. The allocated memory resides in GPU-attached memory on the GPU associated with the calling PE.

When `size` is zero, the routine performs no action and returns a null pointer. Otherwise, `shmemg_malloc` calls a procedure that is semantically equivalent to `shmem_barrier_all` on exit. This ensures that all PEs participate in the memory allocation, and that the memory on other PEs can be used as soon as the local PE returns.

The value of the `size` argument must be identical on all PEs; otherwise, the behavior is undefined.

##### Return Values

`shmemg_malloc` returns the symmetric address of the allocated space; otherwise, it returns a null pointer.

---

#### shmemg_calloc

Collectively allocate a zeroed block of memory from the GPU symmetric heap.

##### Synopsis

```c
void *shmemg_calloc(size_t count, size_t size);
```

##### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `count` | The number of elements to allocate. |
| IN | `size` | The size, in bytes, of each element to allocate. |

##### Description

The `shmemg_calloc` routine is a collective operation on the world team that allocates a region of remotely accessible memory from the GPU symmetric heap for an array of `count` objects of `size` bytes each. The returned pointer refers to the lowest byte address of the allocated memory. The space is initialized to all bits zero. The allocated memory resides in GPU-attached memory on the GPU associated with the calling PE.

If the allocation succeeds, the returned pointer shall be suitably aligned so that it may be assigned to a pointer to any type of object. If the allocation does not succeed, or either `count` or `size` is 0, the return value is a null pointer.

The values of `count` and `size` shall each be equal across all PEs; otherwise, the behavior is undefined.

When `count` or `size` is 0, the routine returns without performing a barrier. Otherwise, `shmemg_calloc` calls a procedure that is semantically equivalent to `shmem_barrier_all` on exit.

##### Return Values

`shmemg_calloc` returns a pointer to the lowest byte address of the allocated space; otherwise, it returns a null pointer.

---

#### shmemg_align

Collectively allocate a block of memory with a specified alignment from the GPU symmetric heap.

##### Synopsis

```c
void *shmemg_align(size_t alignment, size_t size);
```

##### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `alignment` | Byte alignment of the block allocated from the GPU symmetric heap. |
| IN | `size` | The size, in bytes, of a block to be allocated from the GPU symmetric heap. |

##### Description

The `shmemg_align` routine is a collective operation on the world team that allocates a block from the GPU symmetric heap with a byte alignment specified by the `alignment` argument. The value of `alignment` shall be a multiple of `sizeof(void *)` that is also a power of two; otherwise, the behavior is undefined. The allocated memory resides in GPU-attached memory on the GPU associated with the calling PE.

When `size` is zero, the routine performs no action and returns a null pointer. Otherwise, `shmemg_align` calls a procedure that is semantically equivalent to `shmem_barrier_all` on exit.

The values of `alignment` and `size` must be identical on all PEs; otherwise, the behavior is undefined.

##### Return Values

`shmemg_align` returns an aligned symmetric address whose value is a multiple of `alignment`; otherwise, it returns a null pointer.

---

#### shmemg_free

Collectively deallocate memory from the GPU symmetric heap.

##### Synopsis

```c
void shmemg_free(void *ptr);
```

##### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ptr` | Symmetric address of an object in the GPU symmetric heap. |

##### Description

The `shmemg_free` routine is a collective operation on the world team that deallocates the block to which `ptr` points, making it available for further allocation. If `ptr` is a null pointer, no action is performed; otherwise, `shmemg_free` calls a procedure that is semantically equivalent to `shmem_barrier_all` on entry.

It is the application's responsibility to ensure that no communication operations involving the given memory block are pending on any communication context prior to calling `shmemg_free`.

The value of `ptr` must be identical on all PEs; otherwise, the behavior is undefined.

##### Return Values

None.

## GPU-Aware Communication

The OpenSHMEM RMA, AMO, signaling, and collective routines defined in OpenSHMEM 1.6 may be used with GPU-attached memory buffers as operands. The routine interfaces are unchanged. The tables below specify the allowed memory locations for each argument.

The operations in this section are invoked from the host PE. The OpenSHMEM library shall have been initialized with `SHMEM_DEVICE_HOST_INIT` and the corresponding capability shall have been returned in the `provided` argument of `shmem_init_thread`.

The following terms identify the memory locations referenced in this section:

| Term | Description |
|---|---|
| Default symmetric heap | Memory allocated by `shmem_malloc`, `shmem_calloc`, `shmem_align`, or `shmem_malloc_with_hints` from the default (CPU-attached) symmetric heap. |
| GPU symmetric heap | Memory allocated by `shmemg_malloc`, `shmemg_calloc`, or `shmemg_align` from the GPU symmetric heap. |
| Static/global data | Symmetric data objects defined with static or global storage duration (e.g., C static or file-scope variables). |
| Local CPU memory | Private (non-symmetric) CPU-attached memory, including stack, heap, and data segments. |
| Local GPU memory | Private (non-symmetric) GPU-attached memory, including GPU memory allocated by the GPU runtime (e.g., `cudaMalloc`, `hipMalloc`) that is not part of the GPU symmetric heap. |

### Remote Memory Access (RMA)

The RMA routines defined in OpenSHMEM 1.6 transfer data between a local data object and a symmetric data object on a remote PE. The tables below specify the allowed memory locations for source and destination arguments.

#### Blocking Put

Copies data from a contiguous local data object to a data object on a specified PE.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `source` | IN | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

#### Scalar Put

Copies one data item to a remote PE. The `value` argument is passed by value; no memory location restriction applies.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

#### Strided Put

Copies strided data to a specified PE.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `source` | IN | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

#### Nonblocking Put

The nonblocking put routines provide a method for copying data from a contiguous local data object to a data object on a specified PE.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `source` | IN | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

The `source` data object shall not be modified until the operation has been completed by a call to `shmem_quiet` or `shmem_pe_quiet`, as specified in OpenSHMEM 1.6.

#### Blocking Get

Copies data from a specified PE.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` | OUT | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `source` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

#### Scalar Get

Copies one data item from a remote PE. The return value is passed by value; no memory location restriction applies.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `source` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

#### Strided Get

Copies strided data from a specified PE.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` | OUT | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `source` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

#### Nonblocking Get

The nonblocking get routines provide a method for copying data from a contiguous remote data object on the specified PE to the local data object.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` | OUT | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `source` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

The `dest` data object shall not be accessed until the operation has been completed by a call to `shmem_quiet` or `shmem_pe_quiet`, as specified in OpenSHMEM 1.6.

### Atomic Memory Operations (AMO)

An AMO is a one-sided communication mechanism that combines memory read, update, or write operations with atomicity guarantees. The AMOs are performed only on symmetric objects. Two types of AMO routines are defined: fetching routines, which return the original value of the remote data object, and non-fetching routines, which update the remote data object without returning a value.

The `value`, `cond`, and `cmp_value` arguments are passed by value; no memory location restriction applies.

#### Non-fetching AMOs

Atomically update a remote data object.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

#### Fetching AMOs

Atomically fetch or update a remote data object and return the prior value.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` or `source` | IN/OUT | Default symmetric heap, GPU symmetric heap, static/global data |

The return value is passed by value; no memory location restriction applies.

#### Nonblocking AMOs

The nonblocking AMO routines provide a method for atomically fetching or updating a remote data object without waiting for the operation to complete.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `dest` or `source` | IN/OUT | Default symmetric heap, GPU symmetric heap, static/global data |
| `fetch` | OUT | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |

The `fetch` data object shall not be accessed until the operation has been completed by a call to `shmem_quiet`, as specified in OpenSHMEM 1.6.

### Signaling Operations

The put-with-signal routines provide a method for copying data from a contiguous local data object to a data object on a specified PE and subsequently updating a remote flag to signal completion. The signal-fetch routine provides a method for reading the signal object.

#### Put-with-Signal

Copies data from a contiguous local data object to a data object on a specified PE and subsequently updates a remote flag to signal completion.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `source` | IN | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |
| `sig_addr` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

The `signal` and `sig_op` arguments are passed by value; no memory location restriction applies.

#### Nonblocking Put-with-Signal

The nonblocking put-with-signal routines copy data from a contiguous local data object to a data object on a specified PE and subsequently update a remote flag to signal completion.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `source` | IN | Local CPU memory, local GPU memory, default symmetric heap, GPU symmetric heap, static/global data |
| `dest` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |
| `sig_addr` | OUT | Default symmetric heap, GPU symmetric heap, static/global data |

The `source` data object shall not be modified until the operation has been completed by a call to `shmem_quiet`, as specified in OpenSHMEM 1.6.

#### Signal Fetch

Fetches the signal update on a local data object.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `sig_addr` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

### Point-to-Point Synchronization

The point-to-point synchronization routines provide a mechanism for synchronization between two PEs based on the value of a symmetric data object.

#### Wait-Until

Wait for a variable on the local PE to change.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `ivar` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

The `cmp` and `cmp_value` arguments are passed by value; no memory location restriction applies.

#### Wait-Until (Array Variants)

Wait on an array of variables on the local PE until the specified wait condition is met.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `ivars` | IN | Default symmetric heap, GPU symmetric heap, static/global data |
| `status` | IN | Local CPU memory, default symmetric heap, static/global data |
| `indices` | OUT | Local CPU memory, default symmetric heap, static/global data |

The `status` and `indices` arguments shall reside in CPU-attached memory; using GPU-attached memory for these arguments results in undefined behavior.

#### Test

Indicate whether a variable on the local PE meets a specified test condition.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `ivar` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

#### Test (Array Variants)

Indicate whether variables within an array on the local PE meet a specified test condition.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `ivars` | IN | Default symmetric heap, GPU symmetric heap, static/global data |
| `status` | IN | Local CPU memory, default symmetric heap, static/global data |
| `indices` | OUT | Local CPU memory, default symmetric heap, static/global data |

The `status` and `indices` arguments shall reside in CPU-attached memory; using GPU-attached memory for these arguments results in undefined behavior.

#### Signal-Wait-Until

Wait for a variable on the local PE to change from a signaling operation.

| Argument | Direction | Allowed Locations |
|---|---|---|
| `sig_addr` | IN | Default symmetric heap, GPU symmetric heap, static/global data |

The `cmp` and `cmp_value` arguments are passed by value; no memory location restriction applies.

#### Memory Ordering

##### shmem_fence

Ensures ordering of delivery of put, AMO, memory store, and put-with-signal operations on symmetric data objects when GPU-aware communication is enabled.

###### Synopsis

```c
void shmem_fence(void);
void shmem_ctx_fence(shmem_ctx_t ctx);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on the default context. |

###### Description

The `shmem_fence` routine ensures ordering of delivery of put, AMO, memory store, and put-with-signal operations on symmetric data objects. All such operations on symmetric data objects issued to a particular PE on the given context prior to the call to `shmem_fence` are guaranteed to be delivered before any subsequent such operations to the same PE on the same context. `shmem_fence` guarantees order of delivery, not completion. It does not guarantee order of delivery of nonblocking get or values fetched by nonblocking AMO routines.

Memory store operations include direct stores to symmetric data objects performed through local pointers returned by `shmem_ptr` or `shmem_team_ptr`. When the target symmetric data object resides in the GPU symmetric heap, a direct store through such a pointer constitutes a memory store to the GPU symmetric heap. These memory stores are subject to the same ordering semantics as put and AMO operations.

When GPU-aware communication is enabled, `shmem_fence` retains the per-target-PE ordering semantics defined in OpenSHMEM 1.6. However, when two operations issued by the same PE target different memory domains on the same target PE, the two operations may travel through separate ordering or coherency paths. A memory store to the GPU symmetric heap through a pointer returned by `shmem_ptr` traverses the local memory subsystem, whereas a put to the default symmetric heap traverses the network interface. Visibility ordering across distinct memory domains would require additional blocking on the sender side, inducing unnecessary latency overhead when both operations target the same PE. `shmem_fence` does not provide cross-domain visibility guarantees.

If `ctx` has the value `SHMEM_CTX_INVALID`, no operation is performed.

###### Return Values

None.

###### Notes

`shmem_fence` only provides per-PE ordering guarantees and does not guarantee completion of delivery. When GPU-aware communication is in use, `shmem_fence` is sufficient to order operations that target the same memory domain on the same PE. It is not sufficient to guarantee visibility when two operations target different memory domains on the same PE.

The `shmem_quiet` routine should be called if completion of put, AMO, memory store, or put-with-signal operations on symmetric data objects is desired when operations target different memory domains or when multiple target PEs are involved.

###### Example

The following example illustrates a potentially problematic use of `shmem_fence` when two operations target different memory domains on the same PE:

| PE:0 | PE:1 |
|---|---|
| Put to device symmetric heap on PE:1 | Wait for update to the default symmetric heap from PE:0 and then consume data from the device symmetric heap into either host or device attached buffer |
| `shmem_fence` | |
| Put to default symmetric heap on PE:1 | |

In this pattern, PE:0 issues a first operation to the GPU symmetric heap on PE:1 and then calls `shmem_fence` before issuing a second operation to the default symmetric heap on PE:1. Because the two operations target different memory domains on the same PE, `shmem_fence` does not guarantee that the first operation is visible at the GPU symmetric heap before the second operation arrives at the default symmetric heap. PE:1 may observe the second operation before the first is visible. Accessing data from the first operation before it is visible results in undefined behavior.

The same concern applies when the first operation is a memory store through a pointer returned by `shmem_ptr` to a GPU symmetric heap object within `SHMEM_DEVICE_TEAM_SHARED`. Because the memory store traverses the local memory subsystem while the second operation traverses the network interface, `shmem_fence` does not guarantee cross-domain visibility between them.

##### shmem_quiet

Waits for completion of all outstanding put, AMO, memory store, and put-with-signal operations on symmetric data objects issued by a PE when GPU-aware communication is enabled.

###### Synopsis

```c
void shmem_quiet(void);
void shmem_ctx_quiet(shmem_ctx_t ctx);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on the default context. |

###### Description

The `shmem_quiet` routine ensures completion of all outstanding put, AMO, memory store, and put-with-signal operations on symmetric data objects issued by the calling PE on the given context. All such operations are guaranteed to be complete and visible to all PEs when `shmem_quiet` returns.

Memory store operations include direct stores to symmetric data objects performed through local pointers returned by `shmem_ptr` or `shmem_team_ptr`. When the target symmetric data object resides in the GPU symmetric heap, a direct store through such a pointer constitutes a memory store to the GPU symmetric heap. `shmem_quiet` ensures completion and visibility of such memory stores alongside put, AMO, and put-with-signal operations.

When GPU-aware communication is enabled, `shmem_quiet` ensures completion and visibility of all prior operations to both the default symmetric heap and the GPU symmetric heap at their respective targets. When `shmem_quiet` returns, all prior operations are guaranteed to be visible at their targets, regardless of whether the operations target different memory domains or different PEs. The receiving PE shall perform appropriate host-device synchronization after observing data that indicates completion before accessing data from a prior operation that resides in GPU-attached memory.

If `ctx` has the value `SHMEM_CTX_INVALID`, no operation is performed.

###### Return Values

None.

###### Notes

`shmem_quiet` is most useful as a way of ensuring completion of several put, AMO, memory store, or put-with-signal operations on symmetric data objects initiated by the calling PE. For example, one might use `shmem_quiet` to await delivery of a block of data to the GPU symmetric heap before issuing another put routine, which sets a completion flag on another PE. `shmem_quiet` is not usually needed if `shmem_barrier_all` or `shmem_barrier` are called. The barrier routines wait for the completion of outstanding operations to symmetric data objects on all PEs.

There is a subtle difference between `shmem_fence` and `shmem_quiet`, in that, `shmem_quiet` guarantees completion of all operations on symmetric data objects which makes the updates visible to all other PEs across all memory domains, including the GPU symmetric heap and the default symmetric heap. `shmem_fence` provides only per-PE ordering within a single memory domain and does not guarantee cross-domain visibility.

###### Example

The following example illustrates the correct use of `shmem_quiet` when two operations target different memory domains or different PEs:

| PE:0 | PE:2 |
|---|---|
| Put to device symmetric heap on PE:1 | Wait for update to the default symmetric heap from PE:0 and then consume data from the device symmetric heap on PE:1 into either host or device attached buffer |
| `shmem_quiet` | |
| Put to default symmetric heap on PE:2 | |

In this pattern, PE:0 issues a first operation to the GPU symmetric heap on PE:1 and then calls `shmem_quiet`. When `shmem_quiet` returns, visibility of the first operation on PE:1 is guaranteed. PE:0 then issues a second operation to the default symmetric heap on PE:2. When PE:2 observes the second operation and performs proper host-device synchronization, the data from the first operation on PE:1 is available for consumption.

##### shmem_put_signal

Copies data from a contiguous local data object to a data object on a specified PE and subsequently updates a remote flag to signal completion. The put-with-signal routines guarantee ordering between the data delivery and the signal update within a single operation, including when the data and the signal target different memory domains.

###### Synopsis

```c
void shmem_put_signal(TYPE *dest, const TYPE *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
void shmem_ctx_put_signal(shmem_ctx_t ctx, TYPE *dest, const TYPE *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on the default context. |
| OUT | `dest` | Symmetric address of the data object to be updated on the remote PE. |
| IN | `source` | Local address of the data object containing the data to be copied. |
| IN | `nelems` | Number of elements in the `dest` and `source` arrays. |
| OUT | `sig_addr` | Symmetric address of the signal data object to be updated on the remote PE as a signal. |
| IN | `signal` | Unsigned 64-bit value that is used for updating the remote `sig_addr` signal data object. |
| IN | `sig_op` | Signal operator that represents the type of update to be performed on the remote `sig_addr` signal data object. |
| IN | `pe` | PE number of the remote PE. |

###### Description

The put-with-signal routines provide a method for copying data from a contiguous local data object to a data object on a specified PE and subsequently updating a remote flag to signal completion. The completion of the signal update on the remote PE indicates the delivery of the corresponding `dest` data words into the data object on the remote PE.

When GPU-aware communication is enabled, the `dest` data object and the `sig_addr` signal data object may reside in different memory domains on the same target PE. The `dest` data object may reside in the GPU symmetric heap and the `sig_addr` signal data object may reside in the default symmetric heap, or the reverse. The put-with-signal routine guarantees that the data is delivered to the `dest` data object before the signal update is visible at the `sig_addr` signal data object, regardless of whether the two objects reside in the same or different memory domains.

This cross-domain ordering guarantee is specific to the put-with-signal routine. It does not extend to ordering between a put-with-signal routine and other independent operations. Without a memory-ordering operation, there is no implied ordering between the signal update of a put-with-signal routine and another data transfer.

###### Return Values

None.

###### Notes

The `dest` and `sig_addr` data objects must both be remotely accessible. The `sig_addr` and `dest` may be of different kinds; one may be allocated on the GPU symmetric heap and the other on the default symmetric heap.

Unlike the case where two independent operations target different memory domains, the put-with-signal routine provides cross-domain ordering between its data delivery and signal update as a single atomic-like operation. `shmem_fence` does not provide equivalent cross-domain ordering for two independent operations.

The completion of the signal update in a sequence consisting of a put routine followed by a put-with-signal routine does not imply delivery of the put routine's data.

###### Example

The following example illustrates the use of `shmem_put_signal` when the data and signal target different memory domains on the same PE:

| PE:0 | PE:1 |
|---|---|
| `shmem_put_signal`: data to device symmetric heap on PE:1, signal to default symmetric heap on PE:1 | Wait for signal update to the default symmetric heap from PE:0 and then consume data from the device symmetric heap |

In this pattern, PE:0 issues a put-with-signal where the `dest` data object resides in the GPU symmetric heap on PE:1 and the `sig_addr` signal data object resides in the default symmetric heap on PE:1. When PE:1 observes the signal update, the data is guaranteed to be delivered to the GPU symmetric heap. PE:1 shall perform appropriate host-device synchronization before accessing the data in GPU-attached memory.

##### Global Synchronization

###### Synopsis

```c
void shmem_barrier_all(void);
void shmem_barrier(int PE_start, int logPE_stride, int PE_size, long *pSync);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `PE_start` | The lowest PE number of the active set of PEs. |
| IN | `logPE_stride` | The log (base 2) of the stride between consecutive PE numbers in the active set. |
| IN | `PE_size` | The number of PEs in the active set. |
| IN | `pSync` | Symmetric address of a work array of size at least `SHMEM_BARRIER_SYNC_SIZE`. |

###### Description

The `shmem_barrier_all` routine registers the arrival of a PE at a barrier and blocks the calling PE until all PEs in the world team have called `shmem_barrier_all`. The `shmem_barrier` routine performs the same operation with respect to a subset of PEs defined by the active set.

Prior to synchronizing with other PEs, `shmem_barrier_all` ensures completion of all previously issued memory stores and remote memory updates issued on the default context. This includes put, AMO, memory store, and put-with-signal operations on symmetric data objects. `shmem_barrier` ensures that all previously issued stores and remote memory updates done by any of the PEs in the active set on the default context are complete before returning.

When GPU-aware communication is enabled, the implicit completion semantics of `shmem_barrier_all` and `shmem_barrier` are equivalent to calling `shmem_quiet` on the default context prior to synchronization. All prior operations to both the default symmetric heap and the GPU symmetric heap are guaranteed to be complete and visible to all PEs when the barrier returns, regardless of whether the operations target different memory domains or different PEs.

###### Return Values

None.

###### Notes

The `shmem_barrier_all` routine is equivalent to calling `shmem_ctx_quiet` on the default context followed by calling `shmem_team_sync` on the world team.

Calls to `shmem_ctx_quiet` can be performed prior to calling the barrier routine to ensure completion of operations issued on additional contexts.

The `shmem_team_sync` routine, in contrast with the barrier routines, only ensures completion and visibility of previously issued memory stores and does not ensure completion of remote memory updates issued through OpenSHMEM routines. Applications that require completion of remote memory updates before synchronization should call `shmem_ctx_quiet` on the desired context before calling `shmem_team_sync`.

## GPU-Centric Communication

This section defines routines that shall be invoked from within GPU device kernels. These routines shall not be called from the host.

The OpenSHMEM library shall have been initialized with `SHMEM_DEVICE_KERNEL_INIT` and the corresponding capability shall have been returned in the `provided` argument of `shmem_init_thread`. Calling any routine in this section without the required initialization results in **undefined behavior**.

All routines in this section use the `shmemg_` prefix and operate on symmetric data objects allocated from the GPU symmetric heap. A symmetric address and a target PE identifier are used to address remote data objects. Unless otherwise noted, any GPU thread within a device kernel may call these routines.

### Library Setup and Query

The routines in this section return the PE number of the calling PE and the total number of PEs in the program.

#### shmemg_my_pe

Returns the PE number of the calling PE.

##### Synopsis

```c
__device__ int shmemg_my_pe(void);
```

##### Arguments

None.

##### Description

The `shmemg_my_pe` routine returns the PE number of the calling PE. The value is an integer between 0 and `npes - 1`, where `npes` is the total number of PEs in the program. The returned value is identical to the value returned by `shmem_my_pe` on the host for the same PE.

##### Return Values

Integer — between 0 and `npes - 1`.

##### Notes

All threads within a kernel launched by the same PE shall observe the same return value.

---

#### shmemg_n_pes

Returns the number of PEs in the OpenSHMEM program.

##### Synopsis

```c
__device__ int shmemg_n_pes(void);
```

##### Arguments

None.

##### Description

The `shmemg_n_pes` routine returns the total number of PEs in the OpenSHMEM program. The returned value is identical to the value returned by `shmem_n_pes` on the host.

##### Return Values

Integer — total number of PEs in the program.

##### Notes

All threads within a kernel launched by the same PE shall observe the same return value.

### Context Management

Only communication contexts associated with `SHMEM_DEVICE_TEAM_WORLD` or teams created from `SHMEM_DEVICE_TEAM_WORLD` through `shmem_team_split_strided` and `shmem_team_split_2d` routines are capable of performing GPU-centric communication operations from within GPU kernels. Using a context associated with any other team for GPU-centric operations results in **undefined behavior**.

`SHMEM_DEVICE_CTX_DEFAULT` is a predefined communication context of type `shmem_ctx_t` associated with `SHMEM_DEVICE_TEAM_WORLD`. All GPU-centric RMA and AMO operations that do not specify a context shall be performed on `SHMEM_DEVICE_CTX_DEFAULT`. GPU threads may pass `SHMEM_DEVICE_CTX_DEFAULT` to any device-callable routine that accepts a context argument. The implementation shall initialize `SHMEM_DEVICE_CTX_DEFAULT` during library initialization when `SHMEM_DEVICE_KERNEL_INIT` is provided to `shmem_init_thread` and the corresponding capability is returned in `provided`. `SHMEM_DEVICE_CTX_DEFAULT` is usable from within GPU device kernels without additional context creation.

Explicit device contexts are created on the host using `shmem_team_create_ctx` with the `SHMEM_DEVICE_CTX` option. The team argument shall be `SHMEM_DEVICE_TEAM_WORLD` or a team derived from `SHMEM_DEVICE_TEAM_WORLD`. Once created, these contexts may be passed to device-callable routines from within GPU kernels. Device contexts shall not be created or destroyed from within GPU kernels.

Using a device context for GPU-aware (host-initiated) operations, or using a non-device context (including `SHMEM_CTX_DEFAULT`) for GPU-centric operations, results in **undefined behavior**.

### Communication Operations

The source and destination buffers for all data movement operations and the symmetric data objects for all synchronization operations in this section shall reside in the GPU symmetric heap. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as source, destination, or synchronization operands for GPU-centric communication operations results in **undefined behavior**.

Each communication routine is provided at three thread granularities:

| Suffix | Granularity | Description |
|---|---|---|
| *(none)* | Thread | A single GPU thread initiates the operation. Any GPU thread may call the routine independently. |
| `_tg` | Thread group | All threads in a thread group collectively initiate the operation. A thread group is the set of threads that execute a single instance of a GPU kernel invocation, such as a thread block or workgroup. All threads in the thread group shall call the routine with identical arguments. |
| `_htg` | Hardware thread group | All threads in a hardware thread group collectively initiate the operation. A hardware thread group is a fixed-size grouping of threads that execute in lockstep on the GPU, such as a warp or wavefront. All threads in the hardware thread group shall call the routine with identical arguments. |

The thread group (`_tg`) and hardware thread group (`_htg`) variants are collective across the threads in the specified group. All participating threads shall call the routine with the same arguments. If any thread in the group does not participate, or if arguments differ across threads, the behavior is undefined. An implementation may leverage the parallelism of the thread group or hardware thread group to improve the performance of the operation.

#### Remote Memory Access (RMA)

The RMA routines defined in this section transfer data between a local data object and a symmetric data object on a remote PE. The operations are one-sided: the initiating GPU thread provides all communication parameters and the remote PE need not participate.

The PE that initiates a call is the origin PE and the PE targeted by the operation is the destination PE. The `source` and `dest` designators refer to the data objects that an operation reads from and writes to. For put operations, the origin PE provides the `source` data object and the destination PE provides the `dest` data object.

The destination PE is specified as an integer PE number relative to the team associated with the communication context. If no context argument is provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT` and the PE number is relative to `SHMEM_DEVICE_TEAM_WORLD`. If the PE number is invalid — negative or greater than or equal to the size of the team — the behavior is undefined.

Each routine has two variants. In the context-explicit variant, the context handle `ctx` is passed as an argument and the operation is performed on the specified context. If `ctx` does not correspond to a valid device context, the behavior is undefined. In the implicit-context variant, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`.

##### Blocking Put

Copies data from a contiguous local data object to a data object on a specified PE.

###### Synopsis

```c
__device__ void shmemg_putmem(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_putmem(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Thread group variants:

```c
__device__ void shmemg_putmem_tg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_putmem_tg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Hardware thread group variants:

```c
__device__ void shmemg_putmem_htg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_putmem_htg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Symmetric address of the destination data object. |
| IN | `source` | Local address of the data object containing the data to be copied. The `source` data object shall reside in the GPU symmetric heap. |
| IN | `nelems` | Number of bytes to be copied. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The routines return after the data has been copied out of the `source` array on the local PE. Delivery of data into the `dest` data object on the destination PE may occur in any order. Two successive put routines may deliver data out of order unless a call to `shmemg_fence` is introduced between the two calls.

The `source` and `dest` data objects shall reside in the GPU symmetric heap.

###### Return Values

None.

---

##### Nonblocking Put

Initiates a nonblocking copy of data from a contiguous local data object to a data object on a specified PE.

###### Synopsis

```c
__device__ void shmemg_putmem_nbi(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_putmem_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Thread group variants:

```c
__device__ void shmemg_putmem_nbi_tg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_putmem_nbi_tg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Hardware thread group variants:

```c
__device__ void shmemg_putmem_nbi_htg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_putmem_nbi_htg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Symmetric address of the destination data object. |
| IN | `source` | Local address of the object containing the data to be copied. The `source` data object shall reside in the GPU symmetric heap. |
| IN | `nelems` | Number of bytes to be copied. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The routines return after initiating the operation. The operation is considered complete after a subsequent call to `shmemg_quiet`. At the completion of `shmemg_quiet`, the data has been copied into the `dest` array on the destination PE. Delivery of data into the `dest` data object on the destination PE may occur in any order. Two successive put routines may deliver data out of order unless a call to `shmemg_fence` is introduced between the two calls.

The `source` and `dest` data objects shall reside in the GPU symmetric heap.

###### Return Values

None.

---

##### Blocking Get

Copies a contiguous symmetric data object from a specified PE.

###### Synopsis

```c
__device__ void shmemg_getmem(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_getmem(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Thread group variants:

```c
__device__ void shmemg_getmem_tg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_getmem_tg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Hardware thread group variants:

```c
__device__ void shmemg_getmem_htg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_getmem_htg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Local address of the data object to be updated. The `dest` data object shall reside in the GPU symmetric heap. |
| IN | `source` | Symmetric address of the source data object. |
| IN | `nelems` | Number of bytes to be copied. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The routines copy a contiguous symmetric data object from PE `pe` to the local `dest` data object. The routines return after the data has been delivered to the `dest` array on the local PE.

The `source` and `dest` data objects shall reside in the GPU symmetric heap.

###### Return Values

None.

---

##### Nonblocking Get

Initiates a nonblocking copy of a contiguous symmetric data object from a specified PE.

###### Synopsis

```c
__device__ void shmemg_getmem_nbi(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_getmem_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Thread group variants:

```c
__device__ void shmemg_getmem_nbi_tg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_getmem_nbi_tg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

Hardware thread group variants:

```c
__device__ void shmemg_getmem_nbi_htg(void *dest, const void *source, size_t nelems, int pe);
__device__ void shmemg_ctx_getmem_nbi_htg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Local address of the data object to be updated. The `dest` data object shall reside in the GPU symmetric heap. |
| IN | `source` | Symmetric address of the source data object. |
| IN | `nelems` | Number of bytes to be copied. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The routines initiate a copy of a contiguous symmetric data object from PE `pe` to the local `dest` data object. The routines return after initiating the operation. The operation is considered complete after a subsequent call to `shmemg_quiet`. At the completion of `shmemg_quiet`, the data has been delivered to the `dest` array on the local PE.

The `source` and `dest` data objects shall reside in the GPU symmetric heap.

###### Return Values

None.

---

#### Atomic Memory Operations (AMO)

The AMO routines defined in this section perform atomic read, update, or write operations on symmetric data objects in the GPU symmetric heap. Two types are defined: non-fetching routines update the remote data object without returning a value, and fetching routines return the value of the remote data object prior to the update.

The `dest` data object for all AMO routines in this section shall reside in the GPU symmetric heap. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as the `dest` operand results in **undefined behavior**.

The `value`, `cond`, and `cmp_value` arguments are passed by value; no memory location restriction applies.

All AMO routines operate at single-thread granularity. No thread group or hardware thread group variants are defined.

Each routine has two variants: a context-explicit variant where the context handle `ctx` is passed as an argument, and an implicit-context variant where the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`.

##### Non-fetching AMOs

Atomically updates a symmetric data object on a specified PE.

###### Synopsis

```c
__device__ void shmemg_TYPENAME_atomic_set(TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_set(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_add(TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_add(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_inc(TYPE *dest, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_inc(shmem_ctx_t ctx, TYPE *dest, int pe);

__device__ void shmemg_TYPENAME_atomic_and(TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_and(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_or(TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_or(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_xor(TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_xor(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);
```

where TYPE is one of the standard AMO types defined in OpenSHMEM 1.6.

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Symmetric address of the data object to be updated on the remote PE. The `dest` data object shall reside in the GPU symmetric heap. |
| IN | `value` | The operand to the atomic operation. Not used by `shmemg_atomic_inc`. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The non-fetching AMO routines perform an atomic update to the data object at address `dest` on PE `pe`. The operations are:

| Routine | Operation |
|---|---|
| `shmemg_atomic_set` | Atomically sets the value at `dest` to `value`. |
| `shmemg_atomic_add` | Atomically adds `value` to the value at `dest`. |
| `shmemg_atomic_inc` | Atomically increments the value at `dest` by one. |
| `shmemg_atomic_and` | Atomically performs a bitwise AND of `value` with the value at `dest`. |
| `shmemg_atomic_or` | Atomically performs a bitwise OR of `value` with the value at `dest`. |
| `shmemg_atomic_xor` | Atomically performs a bitwise XOR of `value` with the value at `dest`. |

The routines return after the atomic update has been issued. The update to `dest` on the remote PE is guaranteed to be atomic with respect to other atomic operations on the same data object. Two successive non-fetching AMO routines may update the remote data object out of order unless a call to `shmemg_fence` is introduced between the two calls.

The `dest` data object shall reside in the GPU symmetric heap.

###### Return Values

None.

---

##### Fetching AMOs

Atomically fetches or updates a symmetric data object on a specified PE and returns the prior value.

###### Synopsis

```c
__device__ TYPE shmemg_TYPENAME_atomic_fetch(const TYPE *source, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_fetch(shmem_ctx_t ctx, const TYPE *source, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_swap(TYPE *dest, TYPE value, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_swap(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_compare_swap(TYPE *dest, TYPE cond, TYPE value, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_compare_swap(shmem_ctx_t ctx, TYPE *dest, TYPE cond, TYPE value, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_fetch_add(TYPE *dest, TYPE value, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_fetch_add(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_fetch_inc(TYPE *dest, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_fetch_inc(shmem_ctx_t ctx, TYPE *dest, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_fetch_and(TYPE *dest, TYPE value, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_fetch_and(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_fetch_or(TYPE *dest, TYPE value, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_fetch_or(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);

__device__ TYPE shmemg_TYPENAME_atomic_fetch_xor(TYPE *dest, TYPE value, int pe);
__device__ TYPE shmemg_ctx_TYPENAME_atomic_fetch_xor(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe);
```

where TYPE is one of the standard AMO types defined in OpenSHMEM 1.6.

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` or `source` | Symmetric address of the data object on the remote PE. The data object shall reside in the GPU symmetric heap. For `shmemg_atomic_fetch`, this is a read-only source operand. |
| IN | `value` | The operand to the atomic operation. Not used by `shmemg_atomic_fetch` and `shmemg_atomic_fetch_inc`. |
| IN | `cond` | The operand to be compared with the remote value. Used only by `shmemg_atomic_compare_swap`. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The fetching AMO routines perform an atomic read or update to the data object at address `dest` on PE `pe` and return the prior value. The operations are:

| Routine | Operation |
|---|---|
| `shmemg_atomic_fetch` | Atomically fetches the value at `source` on the remote PE. |
| `shmemg_atomic_swap` | Atomically swaps the value at `dest` with `value` and returns the prior value. |
| `shmemg_atomic_compare_swap` | Atomically compares the value at `dest` with `cond` and, if equal, replaces it with `value`. Returns the prior value. |
| `shmemg_atomic_fetch_add` | Atomically adds `value` to the value at `dest` and returns the prior value. |
| `shmemg_atomic_fetch_inc` | Atomically increments the value at `dest` by one and returns the prior value. |
| `shmemg_atomic_fetch_and` | Atomically performs a bitwise AND of `value` with the value at `dest` and returns the prior value. |
| `shmemg_atomic_fetch_or` | Atomically performs a bitwise OR of `value` with the value at `dest` and returns the prior value. |
| `shmemg_atomic_fetch_xor` | Atomically performs a bitwise XOR of `value` with the value at `dest` and returns the prior value. |

The routines return after the fetched value has been delivered to the calling GPU thread. The update to `dest` on the remote PE is guaranteed to be atomic with respect to other atomic operations on the same data object.

The `dest` or `source` data object shall reside in the GPU symmetric heap.

###### Return Values

The value of the remote data object at `dest` or `source` prior to the atomic operation, of type TYPE.

---

##### Nonblocking Fetching AMOs

Initiates a nonblocking atomic fetch or update on a symmetric data object on a specified PE.

###### Synopsis

```c
__device__ void shmemg_TYPENAME_atomic_fetch_nbi(TYPE *fetch, const TYPE *source, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_fetch_nbi(shmem_ctx_t ctx, TYPE *fetch, const TYPE *source, int pe);

__device__ void shmemg_TYPENAME_atomic_swap_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_swap_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_compare_swap_nbi(TYPE *fetch, TYPE *dest, TYPE cond, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_compare_swap_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE cond, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_fetch_add_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_fetch_add_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_fetch_inc_nbi(TYPE *fetch, TYPE *dest, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_fetch_inc_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, int pe);

__device__ void shmemg_TYPENAME_atomic_fetch_and_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_fetch_and_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_fetch_or_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_fetch_or_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe);

__device__ void shmemg_TYPENAME_atomic_fetch_xor_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe);
__device__ void shmemg_ctx_TYPENAME_atomic_fetch_xor_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe);
```

where TYPE is one of the standard AMO types defined in OpenSHMEM 1.6.

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `fetch` | Local address of the data object to be updated with the fetched value. The `fetch` data object shall reside in the GPU symmetric heap. |
| OUT | `dest` or `source` | Symmetric address of the data object on the remote PE. The data object shall reside in the GPU symmetric heap. For `shmemg_atomic_fetch_nbi`, this is a read-only source operand. |
| IN | `value` | The operand to the atomic operation. Not used by `shmemg_atomic_fetch_nbi` and `shmemg_atomic_fetch_inc_nbi`. |
| IN | `cond` | The operand to be compared with the remote value. Used only by `shmemg_atomic_compare_swap_nbi`. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The nonblocking fetching AMO routines initiate an atomic fetch or update to the data object at address `dest` on PE `pe`. The routines return after initiating the operation. The `fetch` data object shall not be accessed until the operation has been completed by a subsequent call to `shmemg_quiet`. Upon completion of `shmemg_quiet`, the prior value of the remote data object has been written to `fetch` and the atomic update, if any, has been performed.

The `fetch`, `dest`, and `source` data objects shall reside in the GPU symmetric heap.

###### Return Values

None.

---

#### Signaling Operations

The signaling routines defined in this section copy data from a contiguous local data object to a data object on a specified PE and subsequently update a remote signal data object to indicate delivery. The signal-fetch routine reads a local signal value.

All signaling operations are performed on a signal data object, a remotely accessible symmetric object of type `uint64_t`. A signal operator in the put-with-signal routine is a library constant that determines the type of update to be performed on the signal data object.

All signaling operations on the signal data object complete as if performed atomically with respect to:

- other blocking or nonblocking variant of the put-with-signal routine that updates the signal data object using the same signal update operator;
- signal-fetch routine that fetches the signal data object; and
- any point-to-point synchronization routine that accesses the signal data object.

The following signal operators are available:

| Constant | Description |
|---|---|
| `SHMEM_SIGNAL_SET` | An update to the signal data object is an atomic set operation. It writes an unsigned 64-bit value as a signal into the signal data object on a remote PE as an atomic operation. |
| `SHMEM_SIGNAL_ADD` | An update to the signal data object is an atomic add operation. It adds an unsigned 64-bit value as a signal into the signal data object on a remote PE as an atomic operation. |

The `dest`, `sig_addr`, and `source` data objects for all signaling routines in this section shall reside in the GPU symmetric heap. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as operands results in **undefined behavior**.

##### Put-with-Signal

Copies data from a contiguous local data object to a data object on a specified PE and subsequently updates a remote signal data object.

###### Synopsis

```c
__device__ void shmemg_putmem_signal(void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
__device__ void shmemg_ctx_putmem_signal(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

Thread group variants:

```c
__device__ void shmemg_putmem_signal_tg(void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
__device__ void shmemg_ctx_putmem_signal_tg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

Hardware thread group variants:

```c
__device__ void shmemg_putmem_signal_htg(void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
__device__ void shmemg_ctx_putmem_signal_htg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Symmetric address of the destination data object to be updated on the remote PE. |
| IN | `source` | Local address of the data object containing the data to be copied. The `source` data object shall reside in the GPU symmetric heap. |
| IN | `nelems` | Number of bytes to be copied. |
| OUT | `sig_addr` | Symmetric address of the signal data object to be updated on the remote PE as a signal. |
| IN | `signal` | Unsigned 64-bit value that is used for updating the remote `sig_addr` signal data object. |
| IN | `sig_op` | Signal operator that represents the type of update to be performed on the remote `sig_addr` signal data object. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The routines copy data from the `source` data object to the `dest` data object on PE `pe` and subsequently update the signal data object at `sig_addr` on the remote PE. The routines return after the data has been copied out of the `source` array on the local PE.

The `sig_op` signal operator determines the type of update to be performed on the remote `sig_addr` signal data object. Completion of the signal update on the remote PE indicates delivery of the corresponding `dest` data into the data object on the remote PE.

An update to the `sig_addr` signal data object through a put-with-signal routine completes as if performed atomically.

The `dest`, `source`, and `sig_addr` data objects shall reside in the GPU symmetric heap. `sig_addr` and `dest` shall not overlap in memory.

###### Return Values

None.

###### Notes

Completion of the signal update on the remote PE indicates only the delivery of the corresponding `dest` data. Without a memory-ordering operation, there is no implied ordering between the signal update of a put-with-signal routine and another data transfer.

---

##### Nonblocking Put-with-Signal

Initiates a nonblocking copy of data to a specified PE with a subsequent signal update.

###### Synopsis

```c
__device__ void shmemg_putmem_signal_nbi(void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
__device__ void shmemg_ctx_putmem_signal_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

Thread group variants:

```c
__device__ void shmemg_putmem_signal_nbi_tg(void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
__device__ void shmemg_ctx_putmem_signal_nbi_tg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

Hardware thread group variants:

```c
__device__ void shmemg_putmem_signal_nbi_htg(void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
__device__ void shmemg_ctx_putmem_signal_nbi_htg(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |
| OUT | `dest` | Symmetric address of the destination data object to be updated on the remote PE. |
| IN | `source` | Local address of the data object containing the data to be copied. The `source` data object shall reside in the GPU symmetric heap. |
| IN | `nelems` | Number of bytes to be copied. |
| OUT | `sig_addr` | Symmetric address of the signal data object to be updated on the remote PE as a signal. |
| IN | `signal` | Unsigned 64-bit value that is used for updating the remote `sig_addr` signal data object. |
| IN | `sig_op` | Signal operator that represents the type of update to be performed on the remote `sig_addr` signal data object. |
| IN | `pe` | PE number of the remote PE relative to the team associated with the given `ctx` when provided, or `SHMEM_DEVICE_TEAM_WORLD` otherwise. |

###### Description

The routines initiate a copy of data from the `source` data object to the `dest` data object on PE `pe` and subsequently update the signal data object at `sig_addr` on the remote PE. The routines return after initiating the operation. The operation is considered complete after a subsequent call to `shmemg_quiet`. Upon completion of `shmemg_quiet`, the data has been copied out of the `source` array on the local PE and delivered into the `dest` array on the destination PE.

Completion of the signal update on the remote PE indicates only the delivery of the corresponding `dest` data. Two successive nonblocking put-with-signal routines, or a nonblocking put-with-signal routine with another data transfer, may deliver data out of order unless a call to `shmemg_fence` is introduced between the two calls.

The `sig_op` signal operator determines the type of update to be performed on the remote `sig_addr` signal data object. An update to the `sig_addr` signal data object through a nonblocking put-with-signal routine completes as if performed atomically.

The `dest`, `source`, and `sig_addr` data objects shall reside in the GPU symmetric heap. `sig_addr` and `dest` shall not overlap in memory.

###### Return Values

None.

---

##### Signal-Fetch

Fetches the value of a local signal data object.

###### Synopsis

```c
__device__ uint64_t shmemg_signal_fetch(const uint64_t *sig_addr);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `sig_addr` | Local address of the remotely accessible signal variable. The `sig_addr` data object shall reside in the GPU symmetric heap. |

###### Description

`shmemg_signal_fetch` returns the value of the signal data object at address `sig_addr` on the calling PE. Access to `sig_addr` at the calling PE satisfies the atomicity guarantees described in the signaling operations introduction.

###### Return Values

The value of the signal data object at `sig_addr` on the calling PE.

---

#### Point-to-Point Synchronization

The point-to-point synchronization routines defined in this section block or test until a symmetric data object on the local PE satisfies a specified condition. All routines in this section operate at single-thread granularity.

The `ivar` or `sig_addr` data object for all routines in this section shall reside in the GPU symmetric heap. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as the synchronization operand results in **undefined behavior**.

The `cmp` argument is a comparison operator from the set of OpenSHMEM comparison constants. The `cmp_value` argument is passed by value; no memory location restriction applies.

##### Wait-Until

Blocks until a symmetric data object on the local PE satisfies a condition.

###### Synopsis

```c
__device__ void shmemg_TYPENAME_wait_until(TYPE *ivar, int cmp, TYPE cmp_value);
```

where TYPE is one of the point-to-point synchronization types defined in OpenSHMEM 1.6.

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ivar` | Symmetric address of the source data object. The `ivar` data object shall reside in the GPU symmetric heap. |
| IN | `cmp` | The comparison operator that compares `ivar` with `cmp_value`. |
| IN | `cmp_value` | The value against which the object pointed to by `ivar` will be compared. |

###### Description

`shmemg_wait_until` blocks until the value of `ivar` at the calling PE satisfies the condition implied by `cmp` and `cmp_value`. The supported values of `cmp` are: `SHMEM_CMP_EQ`, `SHMEM_CMP_NE`, `SHMEM_CMP_GT`, `SHMEM_CMP_GE`, `SHMEM_CMP_LT`, and `SHMEM_CMP_LE`.

The routine shall not return until `ivar` on the calling PE satisfies the specified condition. If no PE ever updates `ivar` to satisfy the condition, the routine shall not return.

The `ivar` data object shall reside in the GPU symmetric heap.

###### Return Values

None.

---

##### Test

Tests whether a symmetric data object on the local PE satisfies a condition.

###### Synopsis

```c
__device__ int shmemg_TYPENAME_test(TYPE *ivar, int cmp, TYPE cmp_value);
```

where TYPE is one of the point-to-point synchronization types defined in OpenSHMEM 1.6.

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ivar` | Symmetric address of the source data object. The `ivar` data object shall reside in the GPU symmetric heap. |
| IN | `cmp` | The comparison operator that compares `ivar` with `cmp_value`. |
| IN | `cmp_value` | The value against which the object pointed to by `ivar` will be compared. |

###### Description

`shmemg_test` tests whether the value of `ivar` at the calling PE satisfies the condition implied by `cmp` and `cmp_value`. The test is performed once and returns without blocking.

The supported values of `cmp` are: `SHMEM_CMP_EQ`, `SHMEM_CMP_NE`, `SHMEM_CMP_GT`, `SHMEM_CMP_GE`, `SHMEM_CMP_LT`, and `SHMEM_CMP_LE`.

The `ivar` data object shall reside in the GPU symmetric heap.

###### Return Values

1 if the condition is satisfied; 0 otherwise.

---

##### Signal-Wait-Until

Blocks until a local signal data object satisfies a condition.

###### Synopsis

```c
__device__ uint64_t shmemg_signal_wait_until(uint64_t *sig_addr, int cmp, uint64_t cmp_value);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `sig_addr` | Local address of the remotely accessible signal variable. The `sig_addr` data object shall reside in the GPU symmetric heap. |
| IN | `cmp` | The comparison operator that compares `sig_addr` with `cmp_value`. |
| IN | `cmp_value` | The value against which the object pointed to by `sig_addr` will be compared. |

###### Description

`shmemg_signal_wait_until` blocks until the value of the signal data object at `sig_addr` satisfies the condition implied by `cmp` and `cmp_value`. The supported values of `cmp` are: `SHMEM_CMP_EQ`, `SHMEM_CMP_NE`, `SHMEM_CMP_GT`, `SHMEM_CMP_GE`, `SHMEM_CMP_LT`, and `SHMEM_CMP_LE`.

The routine shall not return until `sig_addr` on the calling PE satisfies the specified condition. If no PE ever updates `sig_addr` to satisfy the condition, the routine shall not return.

Access to `sig_addr` at the calling PE satisfies the atomicity guarantees described in the signaling operations introduction.

The `sig_addr` data object shall reside in the GPU symmetric heap.

###### Return Values

The value of the signal data object at `sig_addr` that satisfies the wait condition.

---

#### Memory Ordering

The memory ordering routines defined in this section order or complete outstanding put, AMO, and put-with-signal operations issued from within a GPU device kernel.

All memory ordering routines operate at single-thread granularity. Each routine has two variants: a context-explicit variant where the context handle `ctx` is passed as an argument, and an implicit-context variant where the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`.

##### shmemg_fence

Ensures ordering of delivery of put, AMO, and put-with-signal operations to symmetric data objects.

###### Synopsis

```c
__device__ void shmemg_fence(void);
__device__ void shmemg_ctx_fence(shmem_ctx_t ctx);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |

###### Description

`shmemg_fence` ensures ordering of delivery of put, AMO, and put-with-signal operations to symmetric data objects. All such operations issued to a particular remote PE on the given context prior to the call to `shmemg_fence` are guaranteed to be delivered before any subsequent such operations to the same PE on the same context.

`shmemg_fence` guarantees order of delivery, not completion. It does not guarantee order of delivery of nonblocking get operations or values fetched by nonblocking AMO routines.

If `ctx` has the value `SHMEM_CTX_INVALID`, no operation is performed.

###### Return Values

None.

###### Notes

`shmemg_fence` provides per-target-PE ordering guarantees on a given context. It is sufficient to order successive operations that target the same PE. `shmemg_fence` does not ensure completion or global visibility; use `shmemg_quiet` when completion is required.

---

##### shmemg_quiet

Waits for completion of all outstanding put, AMO, and put-with-signal operations to symmetric data objects.

###### Synopsis

```c
__device__ void shmemg_quiet(void);
__device__ void shmemg_ctx_quiet(shmem_ctx_t ctx);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `ctx` | A context handle specifying the context on which to perform the operation. When this argument is not provided, the operation is performed on `SHMEM_DEVICE_CTX_DEFAULT`. |

###### Description

`shmemg_quiet` ensures completion of all outstanding put, AMO, and put-with-signal operations to symmetric data objects issued by the calling GPU thread on the given context. All such operations are guaranteed to be complete and visible to all PEs when `shmemg_quiet` returns.

`shmemg_quiet` also guarantees that any nonblocking operations initiated on the given context have fully completed. In particular, the `fetch` data object of a nonblocking fetching AMO and the `dest` data object of a nonblocking get contain the fetched values upon return.

If `ctx` has the value `SHMEM_CTX_INVALID`, no operation is performed.

###### Return Values

None.

###### Notes

`shmemg_quiet` ensures completion on a single context. Outstanding operations on other contexts are not affected.

---

#### Collective Operations

The collective routines defined in this section synchronize across all PEs in a team. These routines are provided at the same three thread granularities as the communication operations: thread, thread group (`_tg`), and hardware thread group (`_htg`).

All PEs in the specified team shall participate in the collective operation. If any PE in the team does not call the routine, the behavior is undefined.

##### shmemg_sync_all

Registers the arrival of a PE at a synchronization point and blocks until all PEs in `SHMEM_DEVICE_TEAM_WORLD` have arrived.

###### Synopsis

```c
__device__ void shmemg_sync_all(void);
```

Thread group variant:

```c
__device__ void shmemg_sync_all_tg(void);
```

Hardware thread group variant:

```c
__device__ void shmemg_sync_all_htg(void);
```

###### Arguments

None.

###### Description

`shmemg_sync_all` is a collective synchronization routine over `SHMEM_DEVICE_TEAM_WORLD`. The routine blocks until all PEs in `SHMEM_DEVICE_TEAM_WORLD` have called `shmemg_sync_all`.

`shmemg_sync_all` ensures completion and visibility of previously issued memory store operations but does not ensure completion of remote memory updates issued via OpenSHMEM routines. To ensure completion of remote operations before synchronizing, `shmemg_quiet` shall be called prior to `shmemg_sync_all`.

`shmemg_sync_all` is equivalent to calling `shmemg_team_sync` on `SHMEM_DEVICE_TEAM_WORLD`.

###### Return Values

None.

---

##### shmemg_team_sync

Registers the arrival of a PE at a synchronization point and blocks until all PEs in the specified team have arrived.

###### Synopsis

```c
__device__ int shmemg_team_sync(shmem_team_t team);
```

Thread group variant:

```c
__device__ int shmemg_team_sync_tg(shmem_team_t team);
```

Hardware thread group variant:

```c
__device__ int shmemg_team_sync_htg(shmem_team_t team);
```

###### Arguments

| Direction | Name | Description |
|---|---|---|
| IN | `team` | The team over which to perform the synchronization. |

###### Description

`shmemg_team_sync` is a collective synchronization routine over an existing OpenSHMEM team. The routine blocks until all PEs in the specified team have called `shmemg_team_sync`. All PEs in the team shall participate in the operation.

`shmemg_team_sync` ensures completion and visibility of previously issued memory store operations but does not ensure completion of remote memory updates issued via OpenSHMEM routines. To ensure completion of remote operations before synchronizing, `shmemg_quiet` shall be called prior to `shmemg_team_sync`.

If `team` compares equal to `SHMEM_TEAM_INVALID` or is otherwise invalid, the behavior is undefined.

###### Return Values

Zero on successful synchronization; otherwise, a nonzero value.

---

# Annex A Writing OpenSHMEM GPU Program

---

# Annex B Compiling and Running OpenSHMEM GPU Program

---

# Annex C Undefined Behavior in OpenSHMEM GPU Support

This annex consolidates the conditions that result in undefined behavior when using the OpenSHMEM GPU support extensions. These conditions are also stated in their respective sections throughout this specification.

1. Calling any `shmemg_` routine without first initializing the OpenSHMEM library with the required GPU support constant (`SHMEM_DEVICE_HOST_INIT`, `SHMEM_DEVICE_KERNEL_INIT`, or both) passed to `shmem_init_thread` and the corresponding capability returned in `provided`.
2. Calling any GPU-centric routine (Section: GPU-Centric Communication) without the `SHMEM_DEVICE_KERNEL_INIT` capability having been requested and returned.
3. Providing different values for the `requested` GPU support constants across PEs in `shmem_init_thread`.
4. Using a device context (created with `SHMEM_DEVICE_CTX` or `SHMEM_DEVICE_CTX_DEFAULT`) for GPU-aware (host-initiated) operations.
5. Using a non-device context (including `SHMEM_CTX_DEFAULT`) for GPU-centric (device kernel) operations.
6. Using a context associated with a team other than `SHMEM_DEVICE_TEAM_WORLD` or a team derived from `SHMEM_DEVICE_TEAM_WORLD` for GPU-centric operations.
7. Passing an invalid device context handle (`ctx` does not correspond to a valid device context) to a GPU-centric routine.
8. Concurrent atomic operations on the same memory location using communication contexts from different atomicity domains (e.g., a context derived from `SHMEM_DEVICE_TEAM_WORLD` and a context derived from `SHMEM_TEAM_WORLD`).
9. Calling `shmemg_malloc` with a `size` value that differs across PEs.
10. Calling `shmemg_calloc` with `count` or `size` values that differ across PEs.
11. Calling `shmemg_align` with an `alignment` value that is not a multiple of `sizeof(void *)` or is not a power of two.
12. Calling `shmemg_align` with `alignment` or `size` values that differ across PEs.
13. Calling `shmemg_free` with a `ptr` value that differs across PEs.
14. Using GPU-attached memory for the `status` or `indices` arguments of the array variants of wait-until and test (these shall reside in CPU-attached memory).
15. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as source, destination, or synchronization operands for any GPU-centric RMA, AMO, signaling, or synchronization operation (all operands shall reside in the GPU symmetric heap).
16. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as the `dest` operand of a GPU-centric AMO routine.
17. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as `dest`, `sig_addr`, or `source` operands of a GPU-centric signaling routine.
18. Using local GPU memory, local CPU memory, or memory from the default symmetric heap as the `ivar` or `sig_addr` synchronization operand of a GPU-centric point-to-point synchronization routine.
19. Calling a thread group (`_tg`) or hardware thread group (`_htg`) variant without all threads in the group participating in the call.
20. Calling a `_tg` or `_htg` variant with arguments that differ across threads in the group.
21. Passing an invalid PE number (negative, or greater than or equal to the size of the associated team) to a GPU-centric communication routine.
22. Accessing data from a prior operation to the GPU symmetric heap before that operation is visible, when the sender used `shmem_fence` between two operations targeting different memory domains on the same PE (`shmem_fence` does not provide cross-domain visibility guarantees).
23. Calling `shmemg_sync_all`, `shmemg_team_sync`, or their `_tg`/`_htg` variants without all PEs in the specified team participating.
24. Calling `shmemg_team_sync` with a `team` argument that compares equal to `SHMEM_TEAM_INVALID` or is otherwise invalid.

---

# Annex D History of GPU Support in OpenSHMEM

Several vendor-specific implementations extended the OpenSHMEM API to GPU architectures and informed the design of this specification.

- **NVSHMEM.** NVIDIA's OpenSHMEM implementation for CUDA.

- **rocSHMEM.** AMD's OpenSHMEM implementation for HIP (formerly ROC_SHMEM).

- **Intel SHMEM (ISHMEM).** Intel's OpenSHMEM implementation for SYCL.

The GPU-centric routines in this specification adopt a vendor-neutral naming convention (`shmemg_`) and a generalized thread granularity model (thread, thread group, hardware thread group) derived from patterns established by these implementations.

---

# Annex E Changes to this Document

---

# Index
