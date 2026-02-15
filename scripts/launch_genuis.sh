#!/bin/bash
ELF_FILE="/home/murphy/workspace/genius/output/genius.elf"
TERMINAL="gnome-terminal"
QEMU_CMD="qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel $ELF_FILE -monitor none -nographic -serial stdio -s -S"
# start qemu
$TERMINAL -- bash -c "echo '$QEMU_CMD';$QEMU_CMD; exec bash"

# start gdb
sleep 1
$TERMINAL -- bash -c "gdb-multiarch $ELF_FILE -x default.gdb; exec bash"