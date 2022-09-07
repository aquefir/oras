# comment
## doc comment
### normal comment

.globl farcode

.include "blah.inc"

.2byte 0xFFFF

main:
	MOV PC, LR
	LDR R0, =~pool
	LSL R1, R1, #0x10
	LDR R2, =farcode

~pool:
	0xBBBB

# abc
.set name, 0x1
.set blah, name << 16
.set yeap, (blah - 1) << 112

# they can be used with conditionals
.if name

#...

.endif # name

# they can form part of emitting statements
# this ARM pseudo-op will emit the value of blah into a literal pool
LDR R0, =blah

.byte 127
.byte 0x7F
.2byte 0o777
.4byte 12345678
# yup, this works
.8byte (1 << 64) - 1
.16byte 1 << 126

# four in literal sequence
.byte 0, 0, 0, 0

# repeat an arbitrary number of times
# this one does the same as above
.byter 4, 0
# 16 bytes of Thumb-1 NOP
.2byter 8, 0xC046
# like the normal emitters, these are also variadic
# the first parameter quantifies how many times the whole set is repeated
# this becomes 4 repetitions of the byte sequence [ 78 56 34 12 DD CC BB AA ]
.4byter 4, 0x12345678, 0xAABBCCDD
# yes, this works too. 64 bytes of all ones
.16byter 4, (1 << 128) - 1
