# Compiler

1. Scanner - Converts a stream of characters into tokens
2. Parser - Converts the tokens into a parse tree

## How to Run
1. `make`
2. `./frontEnd filename`

## Deterministic Finite Automaton
![Deterministic Finite Automaton](assets/deterministic-finite-automaton.png)

To edit import `assets/deterministic-finite-automaton.json` at https://merfoo.github.io/fsm/


## State Transition Table

The following table is located at `src/scanner/state_transition_table/state_transition_table.cpp`.

The function corresponding to the finite automaton driver is `Scanner::read()` in `src/scanner/scanner.cpp`.

To edit import `assets/state-transition-table.csv` into your favorite spreadsheet program.

| 0-9         | !            | + - * / < > = | : # . ( ) , { } ; [ ] | a-z         | A-Z         | EoF          | White Space  | 
|-------------|--------------|---------------|-----------------------|-------------|-------------|--------------|--------------| 
| 1           | 9            | 10            | 11                    | 12          | Error       | EoF          | 0            | 
| 3           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 2           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 4           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 5           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 6           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 7           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 8           | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| Error       | Integer      | Integer       | Integer               | Integer     | Integer     | Integer      | Integer      | 
| 9           | 0            | 9             | 9                     | 9           | 9           | 9            | 9            | 
| Operator    | Operator     | Operator      | Operator              | Operator    | Operator    | Operator     | Operator     | 
| Delimiter   | Delimiter    | Delimiter     | Delimiter             | Delimiter   | Delimiter   | Delimiter    | Delimiter    | 
| 13          | Identifier   | Identifier    | Identifier            | 13          | 13          | Identifier   | Identifier   | 
| 14          | Identifier   | Identifier    | Identifier            | 14          | 14          | Identifier   | Identifier   | 
| 15          | Identifier   | Identifier    | Identifier            | 15          | 15          | Identifier   | Identifier   | 
| 16          | Identifier   | Identifier    | Identifier            | 16          | 16          | Identifier   | Identifier   | 
| 17          | Identifier   | Identifier    | Identifier            | 17          | 17          | Identifier   | Identifier   | 
| 18          | Identifier   | Identifier    | Identifier            | 18          | 18          | Identifier   | Identifier   | 
| 19          | Identifier   | Identifier    | Identifier            | 19          | 19          | Identifier   | Identifier   | 
| Error       | Identifier   | Identifier    | Identifier            | Error       | Error       | Identifier   | Identifier   | 

## BNF

<S> -> **program** <vars> <block>

<block> -> **start** <vars> <stats> **end**

<vars> -> **var** **Identifier** <vars> | **empty**

<expr> -> <H> **+** <expr> | <H> **-** <expr> | <H> **/** <expr> | <H> **\*** <expr> | <H>

<H> -> **#** <R> | <R>

<R> -> ( <expr> ) | **Identifier** | **Integer**

<stats> -> <stat> <m_stat>

<m_stat> -> <stats> | **empty**

<stat> -> <in> **,** | <out> **,** | <block> **,** | <ifstat> **,** | <loop> **,** | <assign> **,**

<in> -> **read** **Identifier**

<out> -> **print** <expr>

<ifstat> -> **if** **(** <expr> <O> <expr> **)** <stat>

<loop> -> **iter** **(** <expr> <O> <expr> **)** <stat>

<assign> -> **let** **Identifier** **=** <expr>

<O> -> **<** | **>** | **:**
