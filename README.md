This is a reference implementation for sublox2, a sub-variant of the Lox programming language used in the book Crafting Interpreters by Bob Nystrom.
https://craftinginterpreters.com/

It has more features than the sublox1 sub-variant (mainline branch), which has a subset of features that are practically sufficient for further bootstrapping.

This reference implementation is not easilly boostrappable as it needs a reasonably featured C compiler. The ongoing effort to implement a boostrappable version is at:
https://github.com/markjenkins/lox_compiler_scheme

The point of the reference implementation is for use while developing sublox1 programs. It provides better performance, a basic REPL, and more friendly error handling.

The reference implementation is derived from the code provided in Nystrom's book
https://github.com/munificent/craftinginterpreters

The sublox2 sub-variant includes the following features that sublox1 has as well
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

sublox2 also adds back the for loop and has support for the dot operator "." to get and set object properties.

Additional features not in the book
 * DOUBLE_QUOTE, a global string consisting of the double quote character '"', which it is not possible to form in Lox strings which are double quote deliminated without escape sequences

 * a built-in empty class OBJECT {}, which you can instantiate as OBJECT() and set and get properties on using the dot operator.

The pair(), pair_first(), and pair_second() functions are not built-in to the sublox2 interpreter runtime like they are with sublox1. You can simply just include pair.lox in your code where these are functions are defined by using OBJECT(), and get/set operations with the dot (".") operator.

Input is supported using the following python3 tool that generates a lox file with an INPUT global variable:
https://gist.github.com/markjenkins/1a39e62537de9f08648aaf0c82e7d689
Python3 is also not easilly bootrappable, but the same tool can be easilly re-written in a bootstrappable form.

Garbage collection is a feature that still needs to be back-ported. (it appeared after closures in the book, but this sub-variant doesn't include them). That and other TODO items are mentioned in the TODO file.

A goal is to eventualy use the sublox1 sub-variant to build a compiler for the sublox2 variant that can be interpretted with https://github.com/markjenkins/lox_compiler_scheme . With a boostrappable sublox2, the full Lox features (and extensions) could also be added and in turn the full Lox language used to handle even more complicated boostrap tasks.

A LALR(1) parser generator is currently in progress and being written with the sublox1 sub-variant. That project also include some generally useful libraries and a basic concatentation based module/dependency system.
