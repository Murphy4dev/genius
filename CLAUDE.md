# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and Run

```bash
# Build (from repo root)
make --directory=build

# Or from build directory
cd build && make

# Run on QEMU with GDB stub (launches in gnome-terminal)
./tools/launch_genuis.sh
```

**Toolchain**: `arm-none-eabi-gcc` for ARM Cortex-M3 (`-mcpu=cortex-m3 -mthumb`).

**VS Code** includes pre-configured tasks (`Build QEMU`, `Run QEMU`) and a launch config that attaches GDB to `localhost:1234`.

The build outputs go to `output/` (ELF, object files, .d dependency files, .map). `output/` is gitignored.

## Architecture

This is a **FreeRTOS** embedded project targeting an **ARM Cortex-M3** (MPS2-AN385 board), run via QEMU.

### Directory map

| Directory | Purpose |
|---|---|
| `kernel/source/` | FreeRTOS kernel source (tasks, queue, timers, event_groups, stream_buffer) |
| `kernel/source/portable/GCC/ARM_CM3/` | FreeRTOS port layer (port.c, portmacro.h) |
| `kernel/source/portable/MemMang/` | Memory management — **heap_4.c** is used |
| `kernel/include/` | FreeRTOSConfig.h and CMSIS headers |
| `kernel/include/TraceRecorderConfig/` | Percepio TraceRecorder configuration |
| `kernel/trace/` | Percepio TraceRecorder source (streaming + snapshot trace) |
| `platform/CM3/` | BSP: startup_gcc.c (vector table, Reset_Handler, fault handlers), driver/ (UART, printf-stdarg), cpu/ (RegTest) |
| `platform/include/` | BSP public headers (uart.h) |
| `application/` | Application entry points — see below |
| `build/` | Makefile, config.mk, linker script (genius.ld) |
| `tools/` | launch script + GDB init (default.gdb) |

### Startup flow

```
Reset_Handler (platform/CM3/startup_gcc.c)
  → platform_init(): trace_init() + prvUARTInit()
  → xTaskCreate(vMainTask, "main", 1024, NULL, 1, NULL)
  → vTaskStartScheduler()
      → vMainTask() calls main() from the selected application
```

`main()` runs as a **FreeRTOS task**, not bare-metal. The vector table ISR entries for SVCall, PendSV, and SysTick are wired to FreeRTOS handlers.

### Application selection

Edit `build/config.mk` to choose which application to build:

```makefile
CONFIG_HELLO_WORLD = no    # Sets no (not built)
CONFIG_LIST_WORLD = yes    # Sets yes (currently active)
```

- **hello_world**: Creates a task that prints a welcome message every 500ms
- **list_world**: Minimal `main()` — incrementing count, currently a skeleton

### FreeRTOS config highlights

- Static allocation enabled (`configSUPPORT_STATIC_ALLOCATION = 1`), so `vApplicationGetIdleTaskMemory` and `vApplicationGetTimerTaskMemory` must be provided (they are, in `application/hook_world/hook.c`)
- `heap_4.c` used for dynamic allocations (60KB heap). Standard `malloc()` is intentionally trapped — all allocations must use `pvPortMalloc()`
- Trace facility enabled (`configUSE_TRACE_FACILITY = 1`) with Percepio TraceRecorder
- CPU clock: 25 MHz, tick rate: 1 kHz

### Memory layout (genius.ld)

- **Flash**: 0x00000000, 4MB — ISR vectors, .text, .rodata
- **RAM**: 0x20000000, 4MB — .data, .bss, heap, stack

### Debug and trace

GDB init (tools/default.gdb) sets a hardware breakpoint on HardFault_Handler that dumps registers, and on SIGINT dumps the trace buffer to `trace.bin`:

```
dump binary value trace.bin *RecorderDataPtr
```

Percepio Tracealyzer can read `trace.bin`.

## Code conventions

- The project builds `-Wall -Wextra -Wshadow` — warnings are errors in practice, keep the build clean
- Platform code uses `prv` prefix for private functions, matching FreeRTOS naming conventions
- All memory allocation goes through `pvPortMalloc()`, never raw `malloc()`
