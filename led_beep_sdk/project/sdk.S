.global _start
_start :
    mrs r0, cpsr
    bic r0, #0x1f
    mov r0, #0x13
    msr r0, cpsr

    ldr sp, 0x82000000
    b main 