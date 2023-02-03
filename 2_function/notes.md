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


