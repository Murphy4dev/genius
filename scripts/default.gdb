target remote localhost:1234

break HardFault_Handler
commands
    print/x $r0
    print/x $r1
    x/10x $sp
end

catch signal SIGINT
commands
    bt
    print/x $r0
end