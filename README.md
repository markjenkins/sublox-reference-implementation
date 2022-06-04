This is a reference implementation for sublox1, a sub-variant of the Lox programming language used in the book Crafting Interpreters by Bob Nystrom.
https://craftinginterpreters.com/

sublox1 is intended to be more easilly boostrappable than the full Lox language by just having a subset of features that are practically sufficient for further bootstrapping.

This reference implementation is not easilly boostrappable as it needs a reasonably featured C compiler. The ongoing effort to implement a boostrappable version is at:
https://github.com/markjenkins/lox_compiler_scheme

The point of the reference implementation is for use while developing sublox1 programs. It provides better performance, a basic REPL, and more friendly error handling.

The reference implementation is derived from the code provided in Nystrom's book
https://github.com/munificent/craftinginterpreters
Chapter 24 (functions/calls) was taken as the starting point. Code from chapter 25 (closures), chapter 26 (garbage collection), and chapter 27 (classes) are found in the "original" branch.

The sublox1 sub-variant includes the following features:
 * integers (the book uses double)
 * arithmetic operators
 * negation
 * parentheses
 * strings
 * nil
 * true, false
 * equality, inequality, comparison operators
 * print statement
 * variable declaration statements (global and local)
 * local variable re-assignments
 * curly bracket {} block scope statements and block scope for local vars
 * boolean negation, logical AND "and" and OR "or"
 * if, if-else and while control-flow statements (no for loop)
 * global functions without lexical closure, but still as first class objects

In addition, the following features were not in the book, but have been added to the runtime:
 * DOUBLE_QUOTE, a global string consisting of the double quote character '"', which it is not possible to form in Lox strings which are double quote deliminated without escape sequences

 * a global pair(a, b) function and accessor functions pair_first(p) and pair_second(p)

Input is supported using the following python3 tool that generates a lox file with an INPUT global variable:
https://gist.github.com/markjenkins/1a39e62537de9f08648aaf0c82e7d689
Python3 is also not easilly bootrappable, but the same tool can be easilly re-written in a bootstrappable form.

Garbage collection is a feature that still needs to be back-ported. (it appeared after closures in the book, but this sub-variant doesn't include them). That and other TODO items are mentioned in the TODO file.

There is also a sublox2 sub-variant with more features that is found in the sublox2 branch. A goal is to eventualy use the sublox1 sub-variant to build a compiler for the sublox2 variant that can be interpretted with https://github.com/markjenkins/lox_compiler_scheme . With a boostrappable sublox2, the full Lox features (and extensions) could also be added and in turn the full Lox language used to handle even more complicated boostrap tasks.

A LALR(1) parser generator is currently [in progress](https://gist.github.com/markjenkins/4229efe7fe36365ea8d5fd392bea33b8) and being written with the sublox1 sub-variant. That project also include some generally useful libraries and a basic concatentation based module/dependency system.
