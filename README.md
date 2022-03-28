# Oración Assembler

This is the Git repository for the *Oración* assembler, also known as `oras`. It is released under the [Artisan Software Licence](https://aquefir.co/asl). See the `COPYING` file for more information.

## Building

Like most Aquefir software, `oras` uses the [Slick Makefiles](https://aquefir.co/adp4). Assuming you have them installed, simply run `make` (or `make -j<n>` if you like) and then `sudo make install`.

## Role

*Oración* serves a few purposes in the software compilation process, specifically:

1. defining the syntax for the *Oración* assembly language (file suffixes `.os` and `.osa`),
2. providing a lexer both to the assembler program and to related programs, chiefly *Gordian*, **and**
3. actually serialising absolute assembly code (`.osa` files) into machine code.

This diagram gives a general overview of what the compilation procees looks like:

![Compilation process](https://cdn2.arqadium.com/f/862ed60b4d474129b53bc2ee22f0df49/unknown.png)

Although nominally “files” are used to explain the model in familiar terms, they are only files in the sense that they are streams of data with certain characteristics. It is a radical departure from the UNIX model of software compilation where files are given concrete significance in the form of object files and linking. The effects achieved by linking in the UNIX model are actually done *before* assembly code is turned into machine code; we call this **desymbolisation**.
