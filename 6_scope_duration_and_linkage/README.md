# Scope, Duration, and Linkage

## [6.1 — Compound statements (blocks)](https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/)

A **compound statement** (also called a **block**, or **block statement**) is a group of zero or more statements that is
treated by the compiler as if it were a single statement.

Blocks begin with a { symbol, end with a } symbol, with the statements to be executed being placed in between. Blocks
can be used anywhere a single statement is allowed. No semicolon is needed at the end of a block.

### 6.1.1 - Blocks inside other blocks

Blocks can be nested inside other blocks.

When blocks are nested, the enclosing block is typically called the outer block and the enclosed block is called the
inner block or nested block.

### 6.1.2 - Using blocks to execute multiple statements conditionally(if statement)

Skip.

### 6.1.3 - Block nesting levels

The **nesting level** (also called the **nesting depth**) of a function is the maximum number of nested blocks you can
be inside at any point in the function (including the outer block).

The C++ standard says that C++ compilers should support 256 levels of nesting -- however not all do (e.g. as of the time
of writing, Visual Studio supports less).

It’s a good idea to keep your nesting level to 3 or less. Just as overly-long functions are good candidates for
refactoring (breaking into smaller functions), overly-nested blocks are hard to read and are good candidates for
refactoring (with the most-nested blocks becoming separate functions).

**Best practice**
Keep the nesting level of your functions to 3 or less. If your function has a need for more nested levels, consider
refactoring your function into sub-functions.

## [6.2 — User-defined namespaces and the scope resolution operator](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/)

### 6.2.1 - Defining your own namespaces

1. C++ allows us to define our own namespaces via the `namespace` keyword.
2. Namespaces that you create for your own declarations are called **user-defined namespaces**.
3. Namespaces provided by C++ (such as the global namespace) or by libraries (such as namespace std) are not considered
   user-defined namespaces.
4. Namespace identifiers are typically non-capitalized.

Here is an example of the files in the prior example rewritten using namespaces:

```c++
namespace foo // define a namespace named foo
{
    // This doSomething() belongs to namespace foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}
```

To tell the compiler which version of `doSomething()` to use, one could use `scope resolution operator` or use `using
statements`.

### 6.2.2 - Accessing a namespace with the scope resolution operator (::)

The **scope resolution operator (::)** is used to direct the compiler to search for an identifier in a specific
namespace. By using this operator, the compiler is instructed to look for the identifier specified by the right-hand
operand within the scope of the left-hand operand.

The scope resolution operator provides a clear and unambiguous way to specify which namespace to look in for an
identifier.

### 6.2.3 - Using the scope resolution operator with no name prefix(global namespace)

When the scope resolution operator is used without a namespace name in front of an identifier, such as in the form
of `::doSomething`, the identifier is searched for in the global namespace.

### 6.2.4 - Identifier resolution from within a namespace

If an identifier inside a namespace is used and no scope resolution is provided, the compiler will first try to find a
matching declaration in that same namespace. If no matching identifier is found, the compiler will then check each
containing namespace in sequence to see if a match is found, with the global namespace being checked last.

### 6.2.5 - Multiple namespace blocks are allowed

Namespace blocks can be declared in multiple locations, whether in multiple files or in the same file. All declarations
made within a namespace are considered to be a part of that namespace.

The standard library utilizes the ability to declare namespace blocks in multiple locations extensively. Each header
file in the standard library contains declarations within a namespace block named "std". This allows the standard
library to be split into multiple header files rather than being defined in a single file.

When you separate your code into multiple files, you’ll have to use a namespace in the header and source file. Below is
an example:

```c++
add.h

#ifndef ADD_H
#define ADD_H

namespace basicMath
{
    // function add() is part of namespace basicMath
    int add(int x, int y);
}

#endif
```

add.cpp

```c++
#include "add.h"

namespace basicMath
{
    // define the function add()
    int add(int x, int y)
    {
        return x + y;
    }
}
```

main.cpp

```c++
#include "add.h" // for basicMath::add()

#include <iostream>

int main()
{
    std::cout << basicMath::add(4, 3) << '\n';

    return 0;
}
```

1. If the namespace is omitted in the source file, the linker won’t find a definition of basicMath::add, because the
   source file only defines add (global namespace).
2. If the namespace is omitted in the header file, “main.cpp” won’t be
   able to use basicMath::add, because it only sees a declaration for add (global namespace).

### 6.2.6 - Nested namespaces

Namespaces can be nested inside other namespaces. For example:

```c++
#include <iostream>

namespace foo
{
    namespace goo // goo is a namespace inside the foo namespace
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}

int main()
{
    std::cout << foo::goo::add(1, 2) << '\n';
    return 0;
}
```

Since C++17, nested namespaces can also be declared this way:

```c++
#include <iostream>

namespace foo::goo // goo is a namespace inside the foo namespace (C++17 style)
{
  int add(int x, int y)
  {
    return x + y;
  }
}

int main()
{
    std::cout << foo::goo::add(1, 2) << '\n';
    return 0;
}
```

### 6.2.7 - Namespace aliases

Because typing the qualified name of a variable or function inside a nested namespace can be painful, C++ allows you to
create namespace aliases, which allow us to temporarily shorten a long sequence of namespaces into something shorter:

```c++
#include <iostream>

namespace foo::goo
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace active = foo::goo; // active now refers to foo::goo

    std::cout << active::add(1, 2) << '\n'; // This is really foo::goo::add()

    return 0;
} // The active alias ends here
```

### 6.2.8 - When you should use namespaces

1. In applications, namespaces can be used to separate application-specific code from code that might be reusable
   later (e.g. math functions). For example, physical and math functions could go into one namespace (e.g. math::).
   Language and localization functions in another (e.g. lang::).

2. When you write a library or code that you want to distribute to others, always place your code inside a namespace.
   The code your library is used in may not follow best practices -- in such a case, if your library’s declarations
   aren’t in a namespace, there’s an elevated chance for naming conflicts to occur. As an additional advantage, placing
   library code inside a namespace also allows the user to see the contents of your library by using their editor’s
   auto-complete and suggestion feature.

## [6.3 — Local variables](https://www.learncpp.com/cpp-tutorial/local-variables/)

### 6.3.1 - Local variables have block scope

Local variables have **block scope**, which means they are in scope from their point of definition to the end of the
block they are defined within.

### 6.3.2 - All variable names within a scope must be unique

### 6.3.3 - Local variables have automatic storage duration

A variable’s storage duration (usually just called duration) determines what rules govern when and how a variable will
be created and destroyed. In most cases, a variable’s storage duration directly determines its lifetime.

For example, local variables have automatic storage duration, which means they are created at the point of definition
and destroyed at the end of the block they are defined in.

### 6.3.4 - Local variables in nested blocks

Local variables can be defined inside nested blocks.

Note that nested blocks are considered part of the scope of the outer block in which they are defined. Consequently,
variables defined in the outer block can be seen inside a nested block.

### 6.3.5 - Local variables have no linkage

Identifiers have another property named linkage. An identifier’s linkage determines whether other declarations of that
name refer to the same object or not.

Local variables have no linkage, which means that each declaration refers to a unique object.

### 6.3.6 - Variables should be defined in the most limited scope

By limiting the scope of a variable, you reduce the complexity of the program because the number of active variables is
reduced. Further, it makes it easier to see where variables are used (or aren’t used). A variable defined inside a block
can only be used within that block (or nested blocks). This can make the program easier to understand.

**Best practice**

Define variables in the most limited existing scope. Avoid creating new blocks whose only purpose is to limit the scope
of variables.

## [6.4 — Introduction to global variables](https://www.learncpp.com/cpp-tutorial/introduction-to-global-variables/)

In C++, variables can also be declared outside of a function. Such variables are called **global variables**.

### 6.4.1 - Declaring and naming global variables

Conventions:

1. global variables are declared at the top of a file, below the includes, but above any code. Here’s an
   example of a global variable being defined.
2. many developers prefix non-const global variable identifiers with “g” or “g_” to indicate that they are global.

### 6.4.2 - Global variables have file scope and static duration

**Global Scope**
Global variables have file scope (also informally called **global scope** or **global namespace scope**), which means
they are visible from the point of declaration until the end of the file in which they are declared. Once declared, a
global variable can be used anywhere in the file from that point onward! In the above example, global variable g_x is
used in both functions doSomething() and main().

**Global Namespace**
Because they are defined outside of a function, global variables are considered to be part of the global namespace (
hence the term “global namespace scope”).

**Static Duration**
Global variables are created when the program starts, and destroyed when it ends. This is called static duration.
Variables with static duration are sometimes called static variables.

### 6.4.3 - Global variable initialization

Unlike local variables, which are uninitialized by default, variables with static duration are zero-initialized by
default.

### 6.4.4 - Constant global variables

Global variables can be constant. As with all constants, constant global variables must be initialized.

Use of non-constant global variables should generally be avoided altogether!

### 6.3.5 - Summary

```c++
// Non-constant global variables
int g_x;                 // defines non-initialized global variable (zero initialized by default)
int g_x {};              // defines explicitly zero-initialized global variable
int g_x { 1 };           // defines explicitly initialized global variable

// Const global variables
const int g_y;           // error: const variables must be initialized
const int g_y { 2 };     // defines initialized global constant

// Constexpr global variables
constexpr int g_y;       // error: constexpr variables must be initialized
constexpr int g_y { 3 }; // defines initialized global const
```

## [6.5 — Variable shadowing (name hiding)](https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding)

When we have a variable inside a nested block that has the same name as a variable in an outer block, the nested
variable “hides” the outer variable in areas where they are both in scope. This is called **name hiding** or **shadowing
**.

### 6.5.1 - Shadowing of local variables

Example([replit link](https://replit.com/@442584863/name-hiding))

```c++
#include <iostream>

int main()
{ // outer block
    int apples { 5 }; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        int apples{ 0 }; // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10; // this assigns value 10 to nested block apples, not outer block apples

        std::cout << apples << '\n'; // print value of nested block apples
    } // nested block apples destroyed


    std::cout << apples << '\n'; // prints value of outer block apples

    return 0;
} // outer block apples destroyed
```

### 6.5.2 - Shadowing of global variables

Example([replit link](https://replit.com/@442584863/AppropriateThoroughEntropy)):

```c++
#include <iostream>
int value { 5 }; // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}

int main()
{
    int value { 7 }; // hides the global variable value until the end of this block

    ++value; // increments local value, not global value

    std::cout << "local variable value: " << value << '\n';

    foo();

    return 0;
} // local value is destroyed
```

However, because global variables are part of the global namespace, we can use the scope operator (::) with no prefix to
tell the compiler we mean the global variable instead of the local variable.

```c++
#include <iostream>
int value { 5 }; // global variable

int main()
{
    int value { 7 }; // hides the global variable value
    ++value; // increments local value, not global value

    --(::value); // decrements global value, not local value (parenthesis added for readability)

    std::cout << "local variable value: " << value << '\n';
    std::cout << "global variable value: " << ::value << '\n';

    return 0;
} // local value is destroyed
```

### 6.5.4 - Avoid variable shadowing

Avoid variable shadowing.

## [6.6 — Internal linkage](https://www.learncpp.com/cpp-tutorial/internal-linkage/)

Global variable and functions identifiers can have either internal linkage or external linkage. We’ll cover the internal
linkage case in this lesson, and the external linkage case in lesson 6.7 -- External linkage and variable forward
declarations.

An identifier with internal linkage can be seen and used within a single file, but it is not accessible from other
files (that is, it is not exposed to the linker). This means that if two files have identically named identifiers with
internal linkage, those identifiers will be treated as independent.

### 6.6.1 - Global variables with internal linkage

Global variables with internal linkage are sometimes called **internal variables**.

To make a non-constant global variable internal, we use the static keyword.

Const and constexpr global variables have internal linkage by default (and thus don’t need the static keyword -- if it
is used, it will be ignored).

### 6.6.2 - The one-definition rule and internal linkage

In lesson 2.7 -- Forward declarations and definitions, we noted that the one-definition rule says that an object or
function can’t have more than one definition, either within a file or a program.

However, it’s worth noting that internal objects (and functions) that are defined in different files are considered to
be independent entities (even if their names and types are identical), so there is no violation of the one-definition
rule. Each internal object only has one definition.

### 6.6.3 - Functions with internal linkage

Because linkage is a property of an identifier (not of a variable), function identifiers have the same linkage property
that variable identifiers do. Functions default to external linkage (which we’ll cover in the next lesson), but can be
set to internal linkage via the static keyword.

add.cpp:

```c++
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
[[maybe_unused]] static int add(int x, int y)
{
return x + y;
}
```

main.cpp:

```c++
#include <iostream>

int add(int x, int y); // forward declaration for function add

int main()
{
std::cout << add(3, 4) << '\n';

    return 0;
}
```

This program won’t link, because function add is not accessible outside of add.cpp.

### 6.6.4 - Quick Summary

```c++
// Internal global variables definitions:
static int g_x;          // defines non-initialized internal global variable (zero initialized by default)
static int g_x{ 1 };     // defines initialized internal global variable

const int g_y { 2 };     // defines initialized internal global const variable
constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

// Internal function definitions:
static int foo() {};     // defines internal function
```

## [6.7 — External linkage and variable forward declarations](https://www.learncpp.com/cpp-tutorial/external-linkage-and-variable-forward-declarations/)

An identifier with external linkage can be seen and used both from the file in which it is defined, and from other code
files (via a forward declaration). In this sense, identifiers with external linkage are truly “global” in that they can
be used anywhere in your program!

### 6.7.1 - Functions have external linkage by default

1. Functions have external linkage by default.
2. Forward Function Declaration  
   In order to call a function defined in another file, you must place a forward declaration for the function in any
   other files wishing to use the function. The forward declaration tells the compiler about the existence of the
   function, and the linker connects the function calls to the actual function definition.

### 6.7.2 - Global variables with external linkage

1. Global variables with external linkage are sometimes called external variables.
2. To make a global variable external (and thus accessible by other files), we can use the extern keyword to do so.
3. Non-const global variables are external by default (if used, the extern keyword will be ignored).

```c++
int g_x { 2 }; // non-constant globals are external by default

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is useless, see the note in the next section)

int main()
{
    return 0;
}
```

### 6.7.3 - Variable forward declarations via the extern keyword

To actually use an external global variable that has been defined in another file, you also must place a forward
declaration for the global variable in any other files wishing to use the variable. For variables, creating a forward
declaration is also done via the extern keyword (with no initialization value).

Here is an example of using a variable forward declaration:

a.cpp:

```c++
// global variable definitions
int g_x { 2 }; // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```

main.cpp:

```c++
#include <iostream>

extern int g_x; // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << '\n'; // prints 2

    return 0;
}
```

### 6.7.4 - File scope vs. global scope

Informally, the term “file scope” is more often applied to global variables with internal linkage, and “global scope” to
global variables with external linkage.

### 6.7.5 - Quick summary

```c++
// External global variable definitions:
int g_x;                       // defines non-initialized external global variable (zero initialized by default)
extern const int g_x{ 1 };     // defines initialized const external global variable
extern constexpr int g_x{ 2 }; // defines initialized constexpr external global variable

// Forward declarations
extern int g_y;                // forward declaration for non-constant global variable
extern const int g_y;          // forward declaration for const global variable
extern constexpr int g_y;      // not allowed: constexpr variables can't be forward declared
```

## [6.8 — Why (non-const) global variables are evil](https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/)

When developers tell you that global variables are evil, they’re usually not talking about all global variables. They’re
mostly talking about non-const global variables.

### 6.8.1 - Why (non-const) global variables are evil

1. By far the biggest reason non-const global variables are dangerous is because their values can be changed by any
   function that is called, and there is no easy way for the programmer to know that this will happen.

2. One of the key reasons to declare local variables as close to where they are used as possible is because doing so
   minimizes the amount of code you need to look through to understand what the variable does. Global variables are at
   the opposite end of the spectrum -- because they can be accessed anywhere, you might have to look through the entire
   program to understand their usage.

3. Global variables also make your program less modular and less flexible. A function that utilizes nothing but its
   parameters and has no side effects is perfectly modular. Modularity helps both in understanding what a program does,
   as well as with reusability. Global variables reduce modularity significantly.

### 6.8.2 - The initialization order problem of global variables

Initialization of static variables (which includes global variables) happens as part of program startup, before
execution of the main function. This proceeds in two phases.

1. The first phase is called static initialization. In the static initialization phase, global variables with constexpr
   initializers (including literals) are initialized to those values. Also, global variables without initializers are
   zero-initialized.
2. The second phase is called dynamic initialization. This phase is more complex and nuanced, but the gist of it is that
   global variables with non-constexpr initializers are initialized.

Within a single file, global variables are generally initialized in order of definition. Given this, you need to be
careful not to have variables dependent on the initialization value of other variables that won’t be initialized until
later.

The order of initialization across different files is not defined. So never have variables dependent on other file's
variables.

### 6.8.3 - So what are very good reasons to use non-const global variables?

There aren’t many. In most cases, there are other ways to solve the problem that avoids the use of non-const global
variables. But in some cases, judicious use of non-const global variables can actually reduce program complexity, and in
these rare cases, their use may be better than the alternatives.

A good example is a log file, where you can dump error or debug information. It probably makes sense to define this as a
global, because you’re likely to only have one log in a program and it will likely be used everywhere in your program.

For what it’s worth, the std::cout and std::cin objects are implemented as global variables (inside the std namespace).

As a rule of thumb, any use of a global variable should meet at least the following two criteria: There should only ever
be one of the thing the variable represents in your program, and its use should be ubiquitous throughout your program.

### 6.8.4 - Protecting yourself from global destruction

Below are advices for non-const global variables, they can help with all global variables.

1. First, prefix all non-namespaced global variables with “g” or “g_”, or better yet, put them in a namespace (discussed
   in lesson 6.2 -- User-defined namespaces and the scope resolution operator), to reduce the chance of naming
   collisions.
2. Second, instead of allowing direct access to the global variable, it’s a better practice to “encapsulate” the
   variable. Make sure the variable can only be accessed from within the file it’s declared in, e.g. by making the
   variable static or const, then provide external global “access functions” to work with the variable.
    1. These functions can ensure proper usage is maintained (e.g. do input validation, range checking, etc…).
    2. Also, if you ever decide to change the underlying implementation (e.g. move from one database to another), you
       only have to update the access functions instead of every piece of code that uses the global variable directly.

   For example, instead of:

    ```c++
    namespace constants
    {
      extern const double gravity { 9.8 }; // has external linkage, is directly accessible by other files
    }
    ```

   Do this:
    ```c++
    namespace constants
    {
      constexpr double gravity { 9.8 }; // has internal linkage, is accessible only by this file
    }
    
    double getGravity() // this function can be exported to other files to access the global outside of this file
    {
      // We could add logic here if needed later
      // or change the implementation transparently to the callers
      return constants::gravity;
    }
    ```

3. Third, when writing an otherwise standalone function that uses the global variable, don’t use the variable directly
   in your function body. Pass it in as an argument instead. That way, if your function ever needs to use a different
   value for some circumstance, you can simply vary the argument. This helps maintain modularity.

   Instead of:

    ```c++
    #include <iostream>
    
    namespace constants
    {
        constexpr double gravity { 9.8 };
    }
    
    // This function is only useful for calculating your instant velocity based on the global gravity
    double instantVelocity(int time)
    {
        return constants::gravity * time;
    }
    
    int main()
    {
        std::cout << instantVelocity(5);
    }
    ```

   Do this:

    ```c++
    #include <iostream>
    
    namespace constants
    {
        constexpr double gravity { 9.8 };
    }
    
    // This function can calculate the instant velocity for any gravity value (more useful)
    double instantVelocity(int time, double gravity)
    {
        return gravity * time;
    }
    
    int main()
    {
        std::cout << instantVelocity(5, constants::gravity); // pass our constant to the function as a parameter
    }
    ```

## [6.9 — Sharing global constants across multiple files (using inline variables)](https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/)

### 6.9.1 - Global constants as internal variables

Prior to C++17, the following is the easiest and most common solution:

1. Create a header file to hold these constants
2. Inside this header file, define a namespace (discussed in lesson 6.2 -- User-defined namespaces and the scope
   resolution operator)
3. Add all your constants inside the namespace (make sure they’re constexpr)
4. #include the header file wherever you need it

When this header gets #included into a .cpp file, each of these variables defined in the header will be copied into that
code file at the point of inclusion. Because these variables live outside of a function, they’re treated as global
variables within the file they are included into, which is why you can use them anywhere in that file.

Because const globals have internal linkage, each .cpp file gets an independent version of the global variable that the
linker can’t see. In most cases, because these are const, the compiler will simply optimize the variables away.

### 6.9.2 - Global constants as external variables

### 6.9.3 - Global constants as inline variables(C++17)

C++17 introduced a new concept called inline variables. In C++, the term inline has evolved to mean “multiple
definitions are allowed”. Thus, an inline variable is one that is allowed to be defined in multiple files without
violating the one definition rule. Inline global variables have external linkage by default.

The linker will consolidate all inline definitions of a variable into a single variable definition (thus meeting the one
definition rule). This allows us to define variables in a header file and have them treated as if there was only one
definition in a .cpp file somewhere. Let’s say you have a normal constant that you’re #including into 10 code files.
Without inline, you get 10 definitions. With inline, the compiler picks 1 definition to be the canonical definition, so
you only get 1 definition. This means you save 9 constants worth of memory.

These variables will also retain their constexpr-ness in all files in which they are included, so they can be used
anywhere a constexpr value is required. Constexpr values can also be more highly optimized by the compiler than
runtime-const (or non-const) variables.

Inline variables have two primary restrictions that must be obeyed:

All definitions of the inline variable must be identical (otherwise, undefined behavior will result).
The inline variable definition (not a forward declaration) must be present in any file that uses the variable.

## [6.10 — Static local variables](https://www.learncpp.com/cpp-tutorial/static-local-variables/)


