# Oración assembly syntax

Recommended file extension: `.os`

Oración assembly interfaces: `.osi`

Absolute assembly files (label-free): `.osa`

-----

## Comments

`oras` provides two kinds of line comments, although a naive lexer could treat them as one:

1. Normal line comments, beginning with a single hash `#` but not two or more
2. Doc line comments, beginning with two or more hashes `##`

All source characters in an assembly file must be ASCII, unless they are on a line whose first non-whitespace characters are the string `##`. This allows non-Latin scripts as inline documentation without excessively burdening the lexer (it is encoding agnostic).

`oras` does not provide a "block comment", although it does provide a C-style "nesting block comment" using directives to block out code:

## Conditional emission

```
.if 0

#...

.endif
```

`oras` provides comprehensive conditionals for evaluating both expressions and existence of identifiers in order to effect conditional emission.

## File inclusion

```
.include "file.osi"
```

## Emission of raw data

```
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
```

## Expressions and variables

All of these exist ethereally within the assembly and will not exist in the output program unless they form the part of an emitting statement.

Variables should not be confused with symbols, described below. The two cannot be used together directly at all.

```
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
```

## Labels, symbols and locations

A label is the definitive declaration of a symbol anchored to the syntax of the assembly.

A "global" is the declaration of a symbol defined elsewhere, using the `.globl` directive.

```
.globl farcode

# a normal label:
main:
	#...
	LDR R0, =farcode
	BL ~veneer

# a local label:
~veneer:
	MOV LR, PC
	BX R0
```

Oracion does not "emit" symbols like other assemblers do, because it does not generate object code of any kind. Rather, these symbols are made available in the text format of the file for humans and programmatically using the ANSI C API reference, through which they can be reasoned about or ultimately resolved into addresses or offsets for a machine.

`oras` assembly does not directly deal with resolving the real locations of any symbols, instead leaving this to the "Gordian" desymboliser tool. That program follows a linker script that provides architectural context and additional symbols for resolving and linking assembly output.
