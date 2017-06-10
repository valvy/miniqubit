# Contributing to MiniQbt
Thank you for considering to contributing to MiniQbt. Please before you start remember:
1. Be friendly
2. Be respectfull

## Table of contents
[How Can I Contribute?](#how-can-i-contribute)
  * [Using MiniQbt](#using-miniqbt)
  * [Reporting Bugs](#reporting-bugs)
  * [Suggesting Enhancements](#suggesting-enhancements)
  * [Pull Requests](#pull-requests)
[Styleguides](#styleguides)
  * [c++](#c++)

## How Can I Contribute?
### Using miniqbt
Using MiniQbt in your own projects will increase interest in the project

### Reporting Bugs
Bugs are tracked with github issues, When you found a bug please submit the following information
* A clear and descriptive title
* Exact steps to reproduce the bug
* If applicable an sample of code that bugs
* Information such as compiler, operating system, python version etc

### Suggesting Enchancements
Suggestions and enchancements are tracked with github issues. If you have a suggestion please give the following
* A clear and descriptive title
* Step by step description of the suggested enhancement
* Provide snippets and or examples of the suggestion
* Explain why it is usefull

### Pull Requests
I welcome pull requests, but keep in mind the following:
* Give a description what you changed
* Pros of the change
* If applicable the cons
* The change complies with the style guide

## Styleguides
### c++
All c++ code must be written using modern day standards using version 14.
Specific wishes:
* Don't use raw pointers if you don't have to, instead use smart pointers introduced in c++11
* Allways use brackets in a if/while/for statements with a single expression.
* Platform depended code is a no go unless no alternative exists.
* Code must have unit tests associated with them.
* Do not use #Define but instead use the c++11 Constexpr 
* All headers in c++ use the file extension .hpp
* All c++ source files use the file extension .cpp
