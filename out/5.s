.globl main

.text

main:

li	t0,0
sw	t0,0(sp)
j	LABEL1

LABEL2:
li	t0,1
sw	t0,0(sp)

LABEL1:
li	t0,42
li	t1,42
blt	t0,t1,LABEL2
j	LABEL3

LABEL4:
li	t0,2
sw	t0,0(sp)

LABEL3:
li	t0,42
li	t1,42
bgt	t0,t1,LABEL4
j	LABEL5

LABEL6:
li	t0,3
sw	t0,0(sp)

LABEL5:
li	t0,42
li	t1,42
bne	t0,t1,LABEL6

li	a0, 10
ecall
