## [2.1 — Introduction to functions](https://www.learncpp.com/cpp-tutorial/introduction-to-functions/)

1. A **function** is a reusable sequence of statements designed to do a particular job.

2. A **function call** is an expression that tells the CPU to interrupt the current function and execute another
   function. The CPU “puts a bookmark” at the current point of execution, and then calls (executes) the function named
   in the function call. When the called function ends, the CPU returns back to the point it bookmarked, and resumes
   execution.

3. The function initiating the function call is the **caller**, and the function being called is the **callee** or
   called
   function.

4. Nested functions are not supported.

## [2.2 — Function return values (value-returning functions)](https://www.learncpp.com/cpp-tutorial/function-return-values-value-returning-functions/)

1. C++ disallows calling the main function explicitly.

2. For now, you should also define your main function at the bottom of your code file, below other functions.

3. A value-returning function can only return a single value back to the caller each time it is called.  
   There are various ways to work around the limitation of functions only being able to return a single value, which
   we’ll cover in future lessons.

4. Because of the wide variety of possibilities here, it’s a good idea to document your function with a comment
   indicating what the return values mean. For example:
    ```c++
    // Function asks user to enter a value
    // Return value is the integer entered by the user from the keyboard
    int getValueFromUser()
    {
        std::cout << "Enter an integer: ";
        int input{};
        std::cin >> input;
        return input; // return the value the user entered back to the caller
    }
    ```

5. DRY stands for “Don’t Repeat Yourself”. It is a practice that involves writing your code in such a way so as to
   minimize redundancy. This makes your programs more concise, less error prone, and more maintainable.

## [2.3 — Void functions (non-value returning functions)](https://www.learncpp.com/cpp-tutorial/void-functions-non-value-returning-functions/)

1. Functions are not required to return a value back to the caller. To tell the compiler that a function does not return
   a value, a return type of **void** is used. A function that does not return a value is called a **non-value returning
   function** (or a **void function**).
2. Trying to return a value from a non-value returning function will result in a compilation error.

## [2.4 — Introduction to function parameters and arguments](https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/)

1. A **function parameter** is a variable used in the header of a function. Function parameters work almost identically
   to variables defined inside the function, but with one difference: they are initialized with a value provided by the
   caller of the function.
    ```c++
    // This function takes no parameters
    
    // It does not rely on the caller for anything
    void doPrint()
    {
      std::cout << "In doPrint()\n";
    }
    
    // This function takes one integer parameter named x
    // The caller will supply the value of x
    void printValue(int x)
    {
      std::cout << x  << '\n';
    }
    
    // This function has two integer parameters, one named x, and one named y
    // The caller will supply the value of both x and y
    int add(int x, int y)
    {
      return x + y;
    }
    ```

2. An **argument** is a value that is passed from the caller to the function when a function call is made.
    ```c++
    doPrint(); // this call has no arguments
    printValue(6); // 6 is the argument passed to function printValue()
    add(2, 3); // 2 and 3 are the arguments passed to function add()
    ```

3. Function parameters and return values are the key mechanisms by which functions can be written in a reusable way, as
   it allows us to write functions that can perform tasks and return retrieved or calculated results back to the caller
   without knowing what the specific inputs or outputs are ahead of time.

## [2.5 — Introduction to local scope](https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/)

1. Function parameters, as well as variables defined inside the function body, are called **local variables** (as
   opposed to global variables, which we’ll discuss in a future chapter).

2. Function parameters are created and initialized when the function is entered, and variables within the function body
   are created and initialized at the point of definition.
    ```c++
    int add(int x, int y) // x and y created and initialized here
    {
      int z{ x + y }; // z created and initialized here
      return z;
    }   
   ```

   Local variables are destroyed in the opposite order of creation at the end of the set of curly braces in which it is
   defined (or for a function parameter, at the end of the function).
    ```c++
    int add(int x, int y)
    {
      int z{ x + y };
      return z;
    } // z, y, and x destroyed here
    ```

3. Much like a person’s lifetime is defined to be the time between their birth and death, an object’s **lifetime** is
   defined to be the time between its creation and destruction. Note that variable creation and destruction happen when
   the program is running (called runtime), not at compile time. Therefore, lifetime is a runtime property.

4. An identifier’s scope determines where the identifier can be accessed within the source code. When an identifier can
   be accessed, we say it is in scope. When an identifier can not be accessed, we say it is out of scope. Scope is a
   compile-time property, and trying to use an identifier when it is not in scope will result in a compile error.

5. Local variables inside the function body should be defined as close to their first use as reasonable.

## [2.6 — Why functions are useful, and how to use them effectively](https://www.learncpp.com/cpp-tutorial/why-functions-are-useful-and-how-to-use-them-effectively/)

## [2.7 — Forward declarations and definitions](https://www.learncpp.com/cpp-tutorial/forward-declarations/)

### 2.7.1 - The Problem

### 2.7.2 - Forward Declaration

1. A **forward declaration** allows us to tell the compiler about the existence of an identifier before actually
   defining the identifier.
2. To write a forward declaration for a function, we use a **function declaration** statement (also called a **function
   prototype**). The function declaration consists of the function’s return type, name, and parameter types, terminated
   with a semicolon. The names of the parameters can be optionally included. The function body is not included in the
   declaration.
   ```c++
      #include <iostream>
      
      int add(int x, int y); // forward declaration of add() (using a function declaration)
      
      int main()
      {
         std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // this works because we forward declared add() above
         return 0;
      }
      
      int add(int x, int y) // even though the body of add() isn't defined until here
      {
         return x + y;
      }
   ```
3. If a function is forward-declared but is never called, it will be ok.
   If a function is forward-declared and is called, the compiler will not complain, but the linker will.

### 2.7.3 - Why Forward Declaration

1. Use Case in Multi-File Program
   Most often, forward declarations are used to tell the compiler about the existence of some function that has been
   defined in a different code file. Reordering isn’t possible in this scenario because the caller and the callee are in
   completely different files! We’ll discuss this in more detail in the next lesson (2.8 -- Programs with multiple code
   files).

2. Function Definitions in an Order-Agnostic Manner
   Forward declarations can also be used to define our functions in an order-agnostic manner. This allows us to define
   functions in whatever order maximizes organization (e.g. by clustering related functions together) or reader
   understanding.

3. Resolve Circular Dependencies
   Less often, there are times when we have two functions that call each other. Reordering isn’t possible in this case
   either, as there is no way to reorder the functions such that each is before the other. Forward declarations give us
   a way to resolve such circular dependencies.

### 2.7.4 - Definition & Declaration

#### 2.7.4.1 - Definition

A **definition** actually implements (for functions or types) or instantiates (for variables) the identifier. Here are
some
examples of definitions:

```c++
int add(int x, int y) // implements function add()
{
int z{ x + y }; // instantiates variable z

    return z;
}
```

A definition is needed to satisfy the **linker**. If you use an identifier without providing a definition, the linker
will error.

#### 2.7.4.2 - Declaration

A **declaration** is a statement that tells the compiler about the existence of an identifier and its type information.
Here are some examples of declarations:

```c++
int add(int x, int y); // tells the compiler about a function named "add" that takes two int parameters and returns an
int. No body!
int x; // tells the compiler about an integer variable named x
```

A declaration is all that is needed to satisfy the compiler. This is why we can use a forward declaration to tell the
compiler about an identifier that isn’t actually defined until later.

## [2.8 — Programs with multiple code files](https://www.learncpp.com/cpp-tutorial/programs-with-multiple-code-files/)

### 2.8.1 A Multi-File Example

1. Below are code for this example.   
   `add.cpp`:
   ```c++
   int add(int x, int y)
   {
     return x + y;
   }
   ```

   `main.cpp`:

   ```c++
   #include <iostream>
   
   int add(int x, int y);
   
   int main()
   {
     std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // compile error
     return 0;
   }
   ```

2. The compiler compiles each file individually. It does not know about the contents of other code files,
   or remember anything it has seen from previously compiled code files.

3. By using a forward declaration in `main.cpp`, when the compiler is compiling `main.cpp`, it will know what identifier
   `add` is and be satisfied. The linker will connect the function call to `add` in `main.cpp` to the definition of
   function `add` in `add.cpp`. Using this method, we can give files access to functions that live in another file.

4. Do not `#include “add.cpp”` from `main.cpp`. This will cause the preprocessor to insert the contents of `add.cpp`
   directly into `main.cpp` instead of treating them as separate files.

5. Summary
    1. When the compiler compiles a multi-file program, it may compile the files in any order.
    2. Additionally, it compiles each file individually, with no knowledge of what is in other files.

## [2.9 — Naming collisions and an introduction to namespaces](https://www.learncpp.com/cpp-tutorial/naming-collisions-and-an-introduction-to-namespaces/)

### 2.9.1 - What is Naming Collisions

1. **Naming Collision** or **Naming Conflict**
   Similarly, C++ requires that all identifiers be non-ambiguous. If two identical identifiers are introduced into the
   same program in a way that the compiler or linker can’t tell them apart, the compiler or linker will produce an
   error. This error is generally referred to as a naming collision (or naming conflict).

2. `Most naming collisions occur in two cases:
    - Two (or more) identically named functions (or global variables) are introduced into separate files belonging to
      the same program. This will result in a linker error, as shown above.
    - Two (or more) identically named functions (or global variables) are introduced into the same file. This will
      result in a compiler error.

   In other words,
    - If the colliding identifiers are introduced into the same file, the result will be a compiler error.
    - If the colliding identifiers are introduced into separate files belonging to the same program, the result will be
      a linker error.

### 2.9.2 - namespace

1. A namespace is a region that allows you to declare names inside of it for the purpose of disambiguation. The
   namespace provides a scope region (called namespace scope) to the names declared inside of it -- which simply means
   that any name declared inside the namespace won’t be mistaken for identical names in other scopes.

2. Within a namespace, all names must be unique, otherwise a naming collision will result.

3. In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of an
   implicitly defined namespace called the **global namespace** (sometimes also called the **global scope**).

4. Only declarations and definition statements can appear in the global namespace. This means we can define variables in
   the global namespace, though this should generally be avoided (we cover global variables in lesson 6.4 --
   Introduction to global variables). This also means that other types of statements (such as expression statements)
   cannot be placed in the global namespace (initializers for global variables being an exception).

5. When you use an identifier that is defined inside a namespace (such as the std namespace), you have to tell the
   compiler that the identifier lives inside the namespace.

### 2.9.2 - Specify namespace

Several major ways:

#### 2.9.2.1 - Explicit namespace qualifier - Use Explicit Namespace Prefix

The most straightforward way to tell the compiler that we want to use something in some namespace is explicitly
using`{namespace}::` prefix.

The :: symbol is an operator called the **scope resolution operator**. The identifier to the left of the ::
symbol identifies the namespace that the name to the right of the :: symbol is contained within. If no identifier
to the left of the :: symbol is provided, the global namespace is assumed.

#### 2.9.2.2 - Using namespace std (and why to avoid it)

Another way to access identifiers inside a namespace is to use a using directive statement. Here’s our original
“Hello world” program with a using directive:

```c++
#include <iostream>

using namespace std; // this is a using directive that allows us to access names in the std namespace with no namespace prefix

int main()
{
   cout << "Hello world!";
   return 0;
}
```

A using directive allows us to access the names in a namespace without using a namespace prefix. So in the above
example, when the compiler goes to determine what identifier cout is, it will match with std::cout, which, because of
the using directive, is accessible as just cout.

When using a using-directive in this manner, any identifier we define may conflict with any identically named identifier
in the std namespace. Even worse, while an identifier name may not conflict today, it may conflict with new identifiers
added to the std namespace in future language revisions.

## [2.10 — Introduction to the preprocessor](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/)

1. Prior to compilation, each code (.cpp) file goes through a **preprocessing** phase. In this phase, a program called
   the
   **preprocessor** makes various changes to the text of the code file. The preprocessor does not actually modify the
   original code files in any way -- rather, all changes made by the preprocessor happen either temporarily in-memory or
   using temporary files.

2. When the preprocessor runs, it scans through the code file (from top to bottom), looking for preprocessor directives.
   **Preprocessor directives** (often just called directives) are instructions that start with a # symbol and end with a
   newline (NOT a semicolon). These directives tell the preprocessor to perform certain text manipulation tasks. Note
   that the preprocessor does not understand C++ syntax -- instead, the directives have their own syntax (which in some
   cases resembles C++ syntax, and in other cases, not so much).

### 2.10.1 - Common Preprocessor Directives

- `#include`
- `define` macro
    - function-like macros (avoid)
    - object-like macros with substitution text
    - object-like macros without substitution text
- Conditional compilation(`ifdef`, `ifndef`, `endif`)
    - `#if 0`

#### 2.10.1.1 -  `#include`

When you #include a file, the preprocessor replaces the #include directive with the contents of the included file. The
included contents are then preprocessed (along with the rest of the file), and then compiled.

#### 2.10.1.2 - Macro defines - `#define`

The `#define` directive can be used to create a macro. In C++, a **macro** is a rule that defines how input text is
converted into replacement output text.

There are two basic types of macros: object-like macros, and function-like macros.

Function-like macros act like functions, and serve a similar purpose. We will not discuss them here, because their use
is generally considered dangerous, and almost anything they can do can be done by a normal function.

Object-like macros can be defined in one of two ways:

```c++
#define identifier
#define identifier substitution_text
```

The top definition has no substitution text, whereas the bottom one does. Because these are preprocessor directives (not
statements), note that neither form ends with a semicolon.

##### Object-like macros with substitution text

When the preprocessor encounters this directive, any further occurrence of the identifier is replaced by
substitution_text. The identifier is traditionally typed in all capital letters, using underscores to represent spaces.

Object-like macros with substitution text were used (in C) as a way to assign names to literals. This is no longer
necessary, as better methods are available in C++. Object-like macros with substitution text should generally now only
be seen in legacy code.

We recommend avoiding these kinds of macros altogether, as there are better ways to do this kind of thing. We discuss
this more in lesson 4.13 -- Const variables and symbolic constants.

##### Object-like macros without substitution text

Object-like macros can also be defined without substitution text.

Macros of this form work like you might expect: any further occurrence of the identifier is removed and replaced by
nothing!

Unlike object-like macros with substitution text, macros of this form are generally considered acceptable to use.

#### 2.10.1.3 - Conditional compilation

The **conditional compilation preprocessor directives** allow you to specify under what conditions something will or
won’t
compile. There are quite a few different conditional compilation directives, but we’ll only cover the three that are
used by far the most here: `#ifdef`, `#ifndef`, and `#endif`.

1. The `#ifdef` preprocessor directive allows the preprocessor to check whether an identifier has been
   previously `#define`d. If so, the code between the `#ifdef` and matching `#endif` is compiled. If not, the code is
   ignored.

2. `#ifndef` is the opposite of `#ifdef`, in that it allows you to check whether an identifier has NOT been `#define`d
   yet.

3. One more common use of conditional compilation involves using `#if 0` to exclude a block of code from being
   compiled (as if it were inside a comment block):
   ```c++
   #include <iostream>
   
   int main()
   {
      std::cout << "Joe\n";
   
      #if 0 // Don't compile anything starting here
      std::cout << "Bob\n";
      std::cout << "Steve\n";
      #endif // until this point
   
      return 0;
   }
   ```
   This also provides a convenient way to “comment out” code that contains multi-line comments (which can’t be commented
   out using another multi-line comment due to multi-line comments being non-nestable).

### 2.10.2 - Object-like macros don’t affect other preprocessor directives

Macros only cause text substitution for normal code. Other preprocessor commands are ignored.

### 2.10.3 - The scope of `#defines`

Directives are resolved before compilation, from top to bottom on a file-by-file basis.

Once the preprocessor has finished, all defined identifiers from that file are discarded. This means that directives are
only valid from the point of definition to the end of the file in which they are defined. Directives defined in one code
file do not have impact on other code files in the same project.

Consider the following example:

function.cpp:

```c++
#include <iostream>

void doSomething()
{
   #ifdef PRINT
   std::cout << "Printing!\n";
   #endif
   #ifndef PRINT
   std::cout << "Not printing!\n";
   #endif
}
```

main.cpp:

```c++
void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();
   
    return 0;

}
```

The above program will print:

```commandline
Not printing!
```

Even though PRINT was defined in main.cpp, that doesn’t have any impact on any of the code in function.cpp (PRINT is
only #defined from the point of definition to the end of main.cpp). This will be of consequence when we discuss header
guards in a future lesson.

## [2.11 — Header files](https://www.learncpp.com/cpp-tutorial/header-files/)

### 2.11.1 - Headers, and their purposes

**Header files** usually have a `.h` extension, but you will occasionally see them with a .hpp extension or no extension
at all. The primary purpose of a header file is to propagate declarations to code files.

As programs grow larger (and make use of more files), it becomes increasingly tedious to have to forward declare every
function you want to use that is defined in a different file. Wouldn’t it be nice if you could put all your forward
declarations in one place and then import them when you need them? We could use header files to do that.

When it comes to functions and variables, it’s worth keeping in mind that header files typically only contain function
and variable declarations, not function and variable definitions (otherwise a violation of the one definition rule could
result).

### 2.11.2 - How to write header files

Writing a header file is surprisingly easy, as header files only consist of two parts:

- A header guard, which we’ll discuss in more detail in the next lesson (2.12 -- Header guards).
- The actual content of the header file, which should be the forward declarations for all of the identifiers we want
  other files to be able to see.

### 2.11.3 - Include header in the source file

Header files are often paired with code files, with the header file providing forward declarations for the corresponding
code file. If a header file is paired with a code file (e.g. add.h with add.cpp), they should both have the same base
name (add).

In C++, it is a best practice for code files to #include their paired header file (if one exists).

This allows the compiler to catch certain kinds of errors at compile time instead of link time. For example:

`something.h`:

```c++
int something(int); // return type of forward declaration is int
something.cpp:

#include "something.h"

void something(int) // error: wrong return type
{
}
```

Because `something.cpp` `#include`s `something.h`, the compiler will notice that function `something()` has a mismatched
return type and give us a compile error. If `something.cpp` did not `#include` `something.h`, we’d have to wait until
the linker discovered the discrepancy, which wastes time.

### 2.11.4 - Angled Brackets vs Double Quotes

Our use of angled brackets vs double quotes helps give the preprocessor a clue as to where it should look for header
files.

- When we use angled brackets, we’re telling the preprocessor that this is a header file we didn’t write ourselves. The
  preprocessor will search for the header only in the directories specified by the **include directories**. The include
  directories are configured as part of your project/IDE settings/compiler settings, and typically default to the
  directories containing the header files that come with your compiler and/or OS. The preprocessor will not search for
  the header file in your project’s source code directory.
- When we use double-quotes, we’re telling the preprocessor that this is a header file that we wrote. The preprocessor
  will first search for the header file in the current directory. If it can’t find a matching header there, it will then
  search the include directories.

In other words,

- Use double quotes to include header files that you’ve written or are expected to be found in the current directory.
- Use angled brackets to include headers that come with your compiler, OS, or third-party libraries you’ve installed
  elsewhere on your system.

### 2.11.5 - Why `<iostream` do not have `.h` suffix

History reason.

1. At first, there was a `iostream.h`.
2. Later, they decide

### 2.11.6 - Recommended Way to Include Files from other Directories

One simple but bad way is to use the relative path. One of the cons is that if you modify the project structure, it
could crash.

A better method is to tell you compiler or IDE that you have a bunch of header files at some locations. They will go to
those places if they can't find them in the current directory. This can generally be done by setting an include path or
search directory in your IDE project settings.

### 2.11.7 - Transitive Includes and Why to Avoid it

When your code file #includes the first header file, you’ll also get any other header files that the first header file
includes (and any header files those include, and so on). These additional header files are sometimes called
**transitive includes**, as they’re included implicitly rather than explicitly.

Although the content in these transitive includes are available, you'd better not rely on them. You should always
explicitly include everything you need.

### 2.11.8 - The `#include` order of headers

Best practice

To maximize the chance that missing includes will be flagged by compiler, order your #includes as follows:

The paired header file
Other headers from your project
3rd party library headers
Standard library headers
The headers for each grouping should be sorted alphabetically.

### 2.11.9 - Best Practices of Headers

- Always include header guards (we’ll cover these next lesson).
- Do not define variables and functions in header files (global constants are an exception -- we’ll cover these later)
- Give a header file the same name as the source file it’s associated with (e.g. grades.h is paired with grades.cpp).
- Each header file should have a specific job, and be as independent as possible. For example, you might put all your
  declarations related to functionality A in A.h and all your declarations related to functionality B in B.h. That way
  if you only care about A later, you can just include A.h and not get any of the stuff related to B.
- Be mindful of which headers you need to explicitly include for the functionality that you are using in your code files
- Every header you write should compile on its own (it should #include every dependency it needs)
- Only #include what you need (don’t include everything just because you can).
- Do not #include .cpp files.

## [2.12 — Header guards](https://www.learncpp.com/cpp-tutorial/header-guards/)

### 2.12.1 - The Duplicate Definitions Problem

Duplicate definitions included is not uncommon when your project includes lots of headers.

Here is an example:
square.h:

```c++
// We generally shouldn't be defining functions in header files
// But for the sake of this example, we will
int getSquareSides()
{
return 4;
}
```

geometry.h:

```c++
#include "square.h"
```

main.cpp:

```c++
#include "square.h"
#include "geometry.h"

int main()
{
  return 0;
}
```

After resolving all of the #includes, main.cpp ends up looking like this:

```c++
int getSquareSides()  // from square.h
{
    return 4;
}

int getSquareSides() // from geometry.h (via square.h)
{
    return 4;
}

int main()
{
    return 0;
}
```

Duplicate definitions and a compile error.

### 2.12.2 - Header Guards

#### 2.12.2.1 - What is Header Guard and How it works

With the help of **conditional compilation preprocessor directives**, we could avoid duplicate includes, hence this
mechanism is called **header guard**.

```c++
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```

How it works:

1. When this header is #included, the preprocessor checks whether SOME_UNIQUE_NAME_HERE has been previously defined.
2. If this is the first time we’re including the header, `SOME_UNIQUE_NAME_HERE` will not have been defined.
   Consequently, it `#define`s `SOME_UNIQUE_NAME_HERE` and includes the contents of the file.
3. If the header is included again into the same file, `SOME_UNIQUE_NAME_HERE` will already have been defined from the
   first time the contents of the header were included, and the contents of the header will be ignored (thanks to
   the `#ifndef`).

#### 2.12.2.2 - Naming Convention

By convention, the name of header guard is set to the full filename of the header file, typed in all caps, using
underscores for spaces or punctuation. For example

| Header File Name | Header Guard Macro Name |
|------------------|-------------------------|
| square.h         | SQUARE_H                |
| iostream         | _IOSTREAM_              |

In large projects, two separate header files with same name is not uncommon. So only use the header file as the header
guard name may not be sufficient.

Because of this possibility for guard name conflicts, many developers recommend using a more complex/unique name in your
header guards. Some good suggestions are a naming convention of <PROJECT>_<PATH>_<FILE>_H , <FILE>_<LARGE RANDOM NUMBER>
_H, or <FILE>_<CREATION DATE>_H

### 2.12.3 - `#pragma once`

1. `#pragma once` serves the same purpose as header guards: to avoid a header file from being included multiple times.
   With traditional header guards, the developer uses preprocessor directives to guard the header. With `#pragma once`,
   we’re asking the compiler to guard the header. How exactly it does this is a compiler-specific detail.

2. For most projects, `#pragma once` works fine, and many developers now prefer it because it is easier and less
   error-prone. Many IDEs will also auto-include #pragma once at the top of a new header file generated through the IDE.

3. However, because `pragmas` are not an official part of the C++ language (and may not be supported consistently, or at
   all on more esoteric platforms), others (such as Google) still recommend sticking with traditional header guards.

























