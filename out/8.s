.globl main

.text

main:

li	t0,10
sw	t0,0(sp)
li	t0,1
sw	t0,-4(sp)
li	t0,0
sw	t0,-8(sp)
lw	t0,-4(sp)
sw	t0,-12(sp)
j	LABEL1

LABEL2:
li	t0,5
sw	t0,-16(sp)
lw	t0,-12(sp)
sw	t0,-20(sp)
j	LABEL3

LABEL4:
li	t0,5
neg	t0,t0
sw	t0,-24(sp)
lw	t0,-4(sp)
sw	t0,-28(sp)
lw	t0,-24(sp)
lw	t1,-28(sp)
add	t0,t1,t0
sw	t0,-4(sp)
lw	t0,-20(sp)
sw	t0,-28(sp)
li	t0,1
lw	t1,-28(sp)
add	t0,t1,t0
sw	t0,-20(sp)

LABEL3:
lw	t0,-20(sp)
lw	t1,0(sp)
blt	t0,t1,LABEL4
lw	t0,-8(sp)
sw	t0,-20(sp)
lw	t0,-16(sp)
lw	t1,-20(sp)
add	t0,t1,t0
sw	t0,-8(sp)
lw	t0,-12(sp)
sw	t0,-20(sp)
li	t0,3
lw	t1,-20(sp)
add	t0,t1,t0
sw	t0,-12(sp)

LABEL1:
li	t0,10
sw	t0,-20(sp)
lw	t0,-12(sp)
lw	t2,-20(sp)
add	t0,t2,t0
li	t1,2
sw	t1,-20(sp)
li	t1,10
lw	t2,-20(sp)
mul	t1,t2,t1
sw	t1,-20(sp)
li	t1,1
lw	t2,-20(sp)
sub	t1,t2,t1
ble	t0,t1,LABEL2
j	LABEL5

LABEL6:
li	t0,100
sw	t0,0(sp)

LABEL5:
lw	t0,-4(sp)
li	t1,0
bgt	t0,t1,LABEL6
j	LABEL7

LABEL8:
li	t0,100
neg	t0,t0
sw	t0,0(sp)

LABEL7:
lw	t0,-8(sp)
li	t1,0
blt	t0,t1,LABEL8

li	a0, 10
ecall
