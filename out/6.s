.globl main

.text

main:

li	t0,0
sw	t0,0(sp)
li	t0,0
sw	t0,-4(sp)
j	LABEL1

LABEL2:
lw	t0,-4(sp)
sw	t0,-8(sp)
li	t0,10
lw	t1,-8(sp)
add	t0,t1,t0
sw	t0,-4(sp)
lw	t0,0(sp)
sw	t0,-8(sp)
li	t0,1
lw	t1,-8(sp)
add	t0,t1,t0
sw	t0,0(sp)

LABEL1:
lw	t0,-4(sp)
li	t1,0
ble	t0,t1,LABEL2
li	t0,0
sw	t0,-4(sp)
j	LABEL3

LABEL4:
lw	t0,-4(sp)
sw	t0,-8(sp)
li	t0,10
lw	t1,-8(sp)
sub	t0,t1,t0
sw	t0,-4(sp)
lw	t0,0(sp)
sw	t0,-8(sp)
li	t0,1
lw	t1,-8(sp)
add	t0,t1,t0
sw	t0,0(sp)

LABEL3:
lw	t0,-4(sp)
li	t1,0
bge	t0,t1,LABEL4

li	a0, 10
ecall
