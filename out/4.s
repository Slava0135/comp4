.globl main

.text

main:

li	t0,100
sw	t0,0(sp)
li	t0,0
sw	t0,-4(sp)
j	LABEL1

LABEL2:
li	t0,0
sw	t0,-8(sp)
j	LABEL3

LABEL4:
lw	t0,0(sp)
sw	t0,-12(sp)
lw	t0,-4(sp)
lw	t1,-12(sp)
add	t0,t1,t0
sw	t0,-12(sp)
lw	t0,-8(sp)
lw	t1,-12(sp)
sub	t0,t1,t0
sw	t0,0(sp)
lw	t0,-8(sp)
sw	t0,-12(sp)
li	t0,1
lw	t1,-12(sp)
add	t0,t1,t0
sw	t0,-8(sp)

LABEL3:
lw	t0,-8(sp)
li	t1,5
blt	t0,t1,LABEL4
lw	t0,-4(sp)
sw	t0,-8(sp)
li	t0,1
lw	t1,-8(sp)
add	t0,t1,t0
sw	t0,-4(sp)

LABEL1:
lw	t0,-4(sp)
li	t1,5
blt	t0,t1,LABEL2

li	a0, 10
ecall
