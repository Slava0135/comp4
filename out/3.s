.globl main

.text

main:

li	t0,100
sw	t0,0(sp)
li	t0,2
sw	t0,-4(sp)
li	t0,1
sw	t0,-8(sp)
j	LABEL1

LABEL2:
lw	t0,-8(sp)
sw	t0,-16(sp)
li	t0,1
lw	t1,-16(sp)
sub	t0,t1,t0
sw	t0,-16(sp)
lw	t0,-8(sp)
sw	t0,-20(sp)
li	t0,1
lw	t1,-20(sp)
sub	t0,t1,t0
lw	t1,-16(sp)
mul	t0,t1,t0
sw	t0,-12(sp)
lw	t0,0(sp)
sw	t0,-16(sp)
lw	t0,-4(sp)
sw	t0,-20(sp)
lw	t0,-12(sp)
lw	t1,-20(sp)
mul	t0,t1,t0
lw	t1,-16(sp)
add	t0,t1,t0
sw	t0,0(sp)
lw	t0,-8(sp)
sw	t0,-16(sp)
li	t0,1
lw	t1,-16(sp)
add	t0,t1,t0
sw	t0,-8(sp)

LABEL1:
lw	t0,-8(sp)
li	t1,10
ble	t0,t1,LABEL2

li	a0, 10
ecall
