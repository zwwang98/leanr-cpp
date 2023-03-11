## [1.4 - Variable assignment and initialization](https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/)

1. There are 6 basic ways to initialize variables in C++:
   ```C++
   int a;         // no initializer (default initialization)
   int b = 5;     // initializer after equals sign (copy initialization)
   int c( 6 );    // initializer in parenthesis (direct initialization)
   
   // List initialization methods (C++11)
   int d { 7 };   // initializer in braces (direct list initialization)
   int e = { 8 }; // initializer in braces after equals sign (copy list initialization)
   int f {};      // initializer is empty braces (value initialization)
   ```

2. Direct list initialization should be preferred. Spacing is personal preference.
   ```C++
   int d { 7 };   // initializer in braces (direct list initialization)
   ```

3. Default Initialization & Value Initialization

|     Initialization     |                                                                                                                                           What is x?                                                                                                                                           |     Initial Value of Vairable      |
|:----------------------:|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:----------------------------------:|
| Default Initialization |                                             When no initialization value is provided (such as for variable a above), this is  called default initialization. In most cases, default initialization leaves a  variable with an indeterminate value                                              |        Indeterminate Value         |
|  Value Initialization  | When a variable is initialized with empty braces, value initialization takes place. In most cases, value initialization will initialize the variable to zero (or empty, if that’s more appropriate for a given type). In such cases where zeroing occurs,  this is called zero initialization. | zero(or empty if more appropriate) |

```c++
int a;         // no initializer (default initialization)
int f {};      // initializer is empty braces (value initialization)
```

## [1.5 — Introduction to iostream: cout, cin, and endl](https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/)

1. Output a new line whenever a line is completed - using either `std::endl` or `\n`.
2. `std::cout is buffered`  
   When you send data into `std::cout`, that data is typically not sent to the console(or other destination)
   immediately. Instead, the data is queued and is stored into a region of memory - buffer. Periodically, the buffer is
   flushed.
3. `std::endl` vs `\n`
    1. `std::endl` could be inefficient, as it actually does two jobs:
        1. move the cursor to next line
        2. flush the buffer
    2. When writing text to the console, we typically don’t need to flush the buffer at the end of each line. It’s more
       efficient to let the system flush itself periodically (which it has been designed to do efficiently).
    3. Therefore, using `\n` is preferred than using `std::endl`.
4. When using `std::cin` to get user keyboard input and store the data into a varibale, the best practice is to always
   initialize the variable first - value initialization(zero initialization) is prefered.
5. New programmers often mix up `std::cin`, `std::cout`, the insertion operator (`<<`) and the extraction
   operator (`>>`). Here’s an easy way to remember:
    1. `std::cin` and `std::cout` always go on the left-hand side of the statement.
    2. `std::cout` is used to output a value (cout = character output)
    3. `std::cin` is used to get an input value (cin = character input)
    4. `<<` is used with `std::cout`, and shows the direction that data is moving (if `std::cout` represents the
       console, the output data is moving from the variable to the console). `std::cout << 4` moves the value of `4` to
       the console
    5. `>>` is used with `std::cin`, and shows the direction that data is moving (if `std::cin` represents the keyboard,
       the input data is moving from the keyboard to the variable). `std::cin >> x` moves the value the user entered
       from the keyboard into `x`
6. Discussions about handling invalid input for `std::cin` will be discussed
   in [7.16 -- std::cin and handling invalid input](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/).
   Here are some examples:
    ```c++
    #include <iostream>  // for std::cout and std::cin
    int main()
    {
    std::cout << "Enter a number: "; // ask user for a number
    int x{}; // define variable x to hold user input
    std::cin >> x; // get number from keyboard and store it in variable x
    std::cout << "You entered " << x << '\n';
    return 0;
    }
   ```
    - Enter a letter, output will be `You entered 0`.
    - Enter a word, like "hello", output will be `You entered 0`.
    - Enter a huge number (at least 3 billion), you are most likely to get the number 2147483647. This happens because x
      can only hold numbers up to a certain size. If you enter a value larger than the largest number x can hold, it
      will be set to the largest number that x can hold (which is probably 2147483647, but might be different on your
      system). We discuss this further in lesson 4.4 -- Signed integers.
    - Enter a small number followed by some letters, such as 123abc, x gets the numeric value (e.g. 123). We’ll cover
      this case in more detail in lesson 7.16 -- std::cin and handling invalid input.

## [1.6 — Uninitialized variables and undefined behavior](https://www.learncpp.com/cpp-tutorial/uninitialized-variables-and-undefined-behavior/)

1. Uninitialized variables
    1. Unlike some programming languages, C/C++ does not initialize most variables to a given value (such as zero)
       automatically. Thus when a variable is given a memory address to use to store data, the default value of that
       variable is whatever (garbage) value happens to already be in that memory address! A variable that has not been
       given a known value (usually through initialization or assignment) is called an uninitialized variable.
    2. Using the values of uninitialized variables can lead to unexpected results. Consider the following short program:
         ```c++
         #include <iostream>
         
         int main()
         {
         // define an integer variable named x
         int x; // this variable is uninitialized because we haven't given it a value
         
             // print the value of x to the screen
             std::cout << x << '\n'; // who knows what we'll get, because x is uninitialized
         
             return 0;
         }
         ```
2. Work-around for uninitialized variables on compiler  
   If your compiler won’t let you compile and run the above program (e.g. because it treats the issue as an error), here
   is a possible solution to get around this issue:
    ```c++
    #include <iostream>
   
    void doNothing(int&) // Don't worry about what & is for now, we're just using it to trick the compiler into thinking variable x is used
    {
    }
   
    int main()
    {
        // define an integer variable named x
        int x; // this variable is uninitialized
    
        doNothing(x); // make the compiler think we're assigning a value to this variable
    
        // print the value of x to the screen (who knows what we'll get, because x is uninitialized)
        std::cout << x << '\n';
    
        return 0;
    }
    ```

## [1.7 — Keywords and naming identifiers](https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/)

### 1.7.1 Naming Convention Best Practice

1. it is a convention in C++ that variable names should begin with a lowercase letter. If the variable name is one word,
   the whole thing should be written in lowercase letters.
2. Most often, function names are also started with a lowercase letter. We’ll follow this convention, since function
   main (which all programs must have) starts with a lowercase letter, as do all of the functions in the C++ standard
   library.
3. If the variable or function name is multi-word, there are two common conventions:
    1. words separated by underscores, called snake_case,
    2. or intercapped (sometimes called camelCase, since the capital letters stick up like the humps on a camel).  
       the C++ standard library uses the underscore method for both variables and functions. Sometimes you’ll see a mix
       of the two: underscores used for variables and intercaps used for functions.
4. you should avoid naming your identifiers starting with an underscore, as these names are typically reserved for OS,
   library, and/or compiler use.
5. a good rule of thumb is to make the length of an identifier proportional to how widely it is used. An identifier with
   a trivial use can have a short name (e.g. such as i). An identifier that is used more broadly (e.g. a function that
   is called from many different places in a program) should have a longer and more descriptive name (e.g. instead of
   open, try openFileOnDisk).
6. In any case, avoid abbreviations (unless they are common/unambiguous). Although they reduce the time you need to
   write your code, they make your code harder to read. Code is read more often than it is written, the time you saved
   while writing the code is time that every reader, including the future you, wastes when reading it. If you’re looking
   to write code faster, use your editor’s auto-complete feature.
7. Finally, a clarifying comment can go a long way. For example, say we’ve declared a variable named numberOfChars that
   is supposed to store the number of characters in a piece of text. Does the text “Hello World!” have 10, 11, or 12
   characters? It depends on whether we’re including whitespace or punctuation. Rather than naming the variable
   numberOfCharsIncludingWhitespaceAndPunctuation, which is rather lengthy, a well placed comment on the declaration
   line should help the user figure it out:
    ```c++
    // holds number of chars in a piece of text -- including whitespace and punctuation!
    int numberOfChars;
    ```

## [1.8 - Whitespace and basic formatting](https://www.learncpp.com/cpp-tutorial/whitespace-and-basic-formatting/)

### 1.8.1 - Basic Formatting

1. Indentation
   spaces or tabs, both are fine.
2. Function braces
    3. google C++ style guide prefer putting the opening curly brace on the same line as the function signature. Since
       it
       could reduce the amount of lines and thus fit more code into screen, with the hope to make it easier to
       understand
    4. the [learncpp.com](learncpp.com) prefer putting the opening curly brace on its own line. In this way, all pairs
       of
       curly braces are at the same column, it is very easy if there is some missing pairs.
3. Each statement within curly braces should start one tab in from the opening brace of the function it belongs to.
4. Lines should not be too long. Typically, 80 characters is the maximum length a line should be. Split if too long.
5. If a long line is split with an operator (eg. << or +), the operator should be placed at the beginning of the next
   line, not the end of the current line
6. Use whitespace to make your code easier to read by aligning values or comments or adding spacing between blocks of
   code.
    1. align values example
       ```c++
       cost = 57;
       pricePerItem = 24;
       value = 5;
       numberOfItems = 17;
 
       cost          = 57;
       pricePerItem  = 24;
       value         = 5;
       numberOfItems = 17;      
       ```

    2. align comments example
       ```c++
       std::cout << "Hello world!\n"; // cout lives in the iostream library
       std::cout << "It is very nice to meet you!\n"; // these comments make the code hard to read
       std::cout << "Yeah!\n"; // especially when lines are different lengths
 
       std::cout << "Hello world!\n";                    // cout lives in the iostream library
       std::cout << "It is very nice to meet you!\n";    // these comments make the code hard to read
       std::cout << "Yeah!\n";                           // especially when lines are different lengths
       ```

    3. adding space example
       ```c++
       // cout lives in the iostream library
       std::cout << "Hello world!\n";
       // these comments make the code hard to read
       std::cout << "It is very nice to meet you!\n";
       // especially when all bunched together
       std::cout << "Yeah!\n";
 
       // cout lives in the iostream library
       std::cout << "Hello world!\n";
       
       // these comments are easier to read
       std::cout << "It is very nice to meet you!\n";
       
       // when separated by whitespace
       std::cout << "Yeah!\n";
       ```
7. When working with someone else's codebase, follow their style.

## [1.9 - Introduction to literals and operators](https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/)

### 1.9.1 - Literals

A literal (also known as a literal constant) is a fixed value that has been inserted directly into the source code. For
example:

```c++
std::cout << "Hello world!";
int x{ 5 };
```

### 1.9.2 - Operator

1. Terms
    - operations
      a mathematical calculation involving zero or more inputs(call operands)
    - operand
      the input value for mathematical calculations
    - operator
      the symbol denoted for specific operation
    - arity
      The number of operands that an operator takes as input is called the operator's arity
2. operators could be symbols(like `+`, `-`, `*`, `/`) or keyword(like `new`, `delete`, or `throw`).
3. operators in C++ come in 4 different arities:
    - Unary operators act on one operand. An example of a unary operator is the - operator. For example, given -5,
      `operator-` takes literal operand 5 and flips its sign to produce new output value -5.
    - Binary operators act on two operands (often called left and right, as the left operand appears on the left side of
      the operator, and the right operand appears on the right side of the operator). An example of a binary operator is
      the + operator. For example, given 3 + 4, operator+ takes the left operand 3 and the right operand 4 and applies
      mathematical addition to produce new output value 7. The insertion (<<) and extraction (>>) operators are binary
      operators, taking std::cout or std::cin on the left side, and the value to output or variable to input to on the
      right side.
    - Ternary operators act on three operands. There is only one of these in C++ (the conditional operator), which we’ll
      cover later.
    - Nullary operators act on zero operands. There is also only one of these in C++ (the throw operator), which we’ll
      also cover later.
    - Note that some operators have more than one meaning depending on how they are used. For example, operator- has two
      contexts. It can be used in unary form to invert a number’s sign (e.g. to convert 5 to -5, or vice versa), or it
      can be used in binary form to do subtraction (e.g. 4 - 3).

### 1.9.3 - Return Values, Side Effects, and Chaining Operators

1. Most operators in C++ just use their operands to calculate return values.
   A few operators that do not produce return values(such as `delete` and `throw`).
2. An operator that has some observable effect beyond producing a return value is said to have a **side effect**. For
   example,
    - When `x = 5` is evaluated, the assignment operator has the side effect of assigning the value 5 to variable `x`.
      The changed value of x is observable (e.g. by printing the value of x) even after the operator has finished
      executing.
    - `std::cout << 5` has the side effect of printing 5 to the console. We can observe the fact that 5 has been printed
      to the console even after std::cout << 5 has finished executing.
3. Operators with side effects are usually called for the behavior of the side effect rather than for the return value (
   if any) those operators produce.
4. The returned values for operators that we call primarily for side effects are just the **left parts** of those
   operators.
   This is done so that these operators can be chained.
   For example,
    - `x = y = 5` evaluates as `x = (y = 5)`. First `y = 5` assigns `5` to `y`. This operation then returns `y`, which
      can then be assigned to `x`.
    - `std::cout << "Hello " << "world"` evaluates as `(std::cout << "Hello ") << "world!"`. This first
      prints `"Hello "` to the console. This operation returns `std::cout`, which can then be used to print `"world!"`
      to the console as well.

## [1.10 - Introduction to expressions](https://www.learncpp.com/cpp-tutorial/introduction-to-expressions/)
