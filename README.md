# Postfix-Precision-Processor
#            OR
# Reverse Polish Notation (RPN) calculator

## Overview
This project implements a Reverse Polish Notation (RPN) calculator in C that allows for the evaluation of postfix mathematical expressions. RPN calculators are known for their efficient and straightforward computation methodology, eliminating the need for parentheses to denote operation precedence.

## Features
1) Dynamic Input Reading: Handles large input sizes by dynamically allocating memory for the input string.
2) Support for Basic Operations: The calculator supports addition (+), subtraction (-), multiplication (*), modulo (%), and correctly handles precedence and associativity inherent to postfix notation.
3) Error Handling: Provides basic handling for common errors such as stack underflows and invalid tokens.

## Implementation Details
* Stack Data Structure: Utilizes a stack to push and pop operands as per the RPN calculation requirements. The stack is implemented with a fixed size, and operations check for stack overflow and underflow conditions.
* Dynamic Input Handling: Reads input dynamically into a buffer that expands as needed to accommodate large expressions.
* Tokenization: Splits the input string into tokens that are either operators or operands. The evaluation function decides the action (push to stack or perform an operation) based on the type of token.
