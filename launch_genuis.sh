#!/bin/bash
make --directory=build clean && make --directory=build 
CURRENT=$(cd "$(dirname "$0")"; pwd)
ELF_FILE="$CURRENT/output/genius.elf"
TOOL_DIR="$CURRENT/tools"

TERMINAL="gnome-terminal"
QEMU_CMD="qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel $ELF_FILE -monitor none -nographic -serial stdio -s -S"
# start qemu
$TERMINAL -- bash -c "echo '$QEMU_CMD';$QEMU_CMD; exec bash"

# start gdb
sleep 1
$TERMINAL -- bash -c "gdb-multiarch $ELF_FILE -x $TOOL_DIR/default.gdb; exec bash"