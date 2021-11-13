.globl main

.text

main:

li	t0,10
sw	t0,0(sp)
lw	t0,0(sp)
sw	t0,-8(sp)
li	t0,5
sw	t0,-12(sp)
li	t0,5
lw	t1,-12(sp)
div	t0,t1,t0
lw	t1,-8(sp)
sub	t0,t1,t0
sw	t0,-4(sp)
li	t0,2
sw	t0,-12(sp)
lw	t0,0(sp)
neg	t0,t0
sw	t0,-16(sp)
li	t0,31
neg	t0,t0
sw	t0,-20(sp)
lw	t0,-4(sp)
sw	t0,-24(sp)
lw	t0,-4(sp)
lw	t1,-24(sp)
mul	t0,t1,t0
lw	t1,-20(sp)
add	t0,t1,t0
lw	t1,-16(sp)
add	t0,t1,t0
lw	t1,-12(sp)
add	t0,t1,t0
sw	t0,-8(sp)
lw	t0,0(sp)
sw	t0,-16(sp)
lw	t0,0(sp)
lw	t1,-16(sp)
mul	t0,t1,t0
sw	t0,-16(sp)
li	t0,1
sw	t0,-20(sp)
li	t0,2
sw	t0,-24(sp)
li	t0,3
lw	t1,-24(sp)
mul	t0,t1,t0
lw	t1,-20(sp)
add	t0,t1,t0
sw	t0,-20(sp)
li	t0,4
lw	t1,-20(sp)
add	t0,t1,t0
sw	t0,-20(sp)
li	t0,5
lw	t1,-20(sp)
sub	t0,t1,t0
sw	t0,-20(sp)
li	t0,1
sw	t0,-24(sp)
li	t0,1
lw	t1,-24(sp)
add	t0,t1,t0
lw	t1,-20(sp)
div	t0,t1,t0
lw	t1,-16(sp)
add	t0,t1,t0
sw	t0,-12(sp)

li	a0, 10
ecall
