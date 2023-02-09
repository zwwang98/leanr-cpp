## [3.1 — Syntax and semantic errors](https://www.learncpp.com/cpp-tutorial/syntax-and-semantic-errors/)

1. Syntax Error
    - A syntax error occurs when you write a statement that is not valid according to the grammar of the C++ language.
    - Fortunately, the compiler will generally catch syntax errors and generate warnings or errors, so you easily
      identify and fix the problem.
2. Semantic Error
    - A semantic error occurs when a statement is syntactically valid, but does not do what the programmer intended.
    - In most cases, the compiler will not be able to catch most of these types of problems, because the compiler is
      designed to enforce grammar, not intent. In most non-trivial programs, semantic errors are not easy to find by
      eyeballing the code.

## [3.2 — The debugging process](https://www.learncpp.com/cpp-tutorial/the-debugging-process/)

All bugs stem from a simple premise: Something that you thought was correct, isn’t.

### A general approach to debugging

Once a problem has been identified, debugging the problem generally consists of five steps:

1. Find the root cause of the problem (usually the line of code that’s not working)
2. Ensure you understand why the issue is occurring
3. Determine how you’ll fix the issue
4. Repair the issue causing the problem
5. Retest to ensure the problem has been fixed and no new problems have emerged

## [3.3 — A strategy for debugging](https://www.learncpp.com/cpp-tutorial/a-strategy-for-debugging/)

When debugging a program, in most cases the vast majority of your time will be spent trying to find where the error
actually is. Once the issue is found, the remaining steps (fixing the issue and validating that the issue was fixed) are
often trivial in comparison.

In this lesson, we’ll start exploring how to find errors.

Two ways to find where the error actually is:

1. via code inspections
2. by running programs

### 3.3.1 - via code inspections

However, as programs get more complex, finding issues by code inspection becomes more complex
as well. First, there are a lot code to inspect. Second, it is almost impossible to virtual locate the bug caused by
bad assumption.

### 3.3.2 - by running programs

This approach can be generalized as:

1. Figure out how to reproduce the problem
2. Run the program and gather information to narrow down where the problem is
3. Repeat the prior step until you find the problem

## [3.4 — Basic debugging tactics](https://www.learncpp.com/cpp-tutorial/basic-debugging-tactics/)

In the previous lesson, we explored a strategy for finding issues by running our programs and using guesswork to home in
on where the problem is.

In this lesson, we’ll explore some basic tactics for actually making those guesses and
collecting information to help find issues.

### 3.4.1 - Debugging tactic #1: Commenting out your code

If your program is exhibiting erroneous behavior, one way to reduce the amount of code you have to search through is to
comment some code out and see if the issue persists. If the issue remains, the commented out code wasn’t responsible.

### 3.4.2 - Debugging tactic #2: Validating your code flow

Another problem common in more complex programs is that the program is calling a function too many or too few times (
including not at all).

In such cases, it can be helpful to place statements at the top of your functions to print the function’s name. That
way, when the program runs, you can see which functions are getting called.

### 3.4.3 - Debugging tactic #3: Printing values

With some types of bugs, the program may be calculating or passing the wrong value.

We can also output the value of variables (including parameters) or expressions to ensure that they are correct.

The third-party library [dbg-macro](https://github.com/sharkdp/dbg-macro) can help make debugging using print statements
easier. Check it out if this is something you find yourself doing a lot.

However, debug using printing statements isn't greate:

1. Debug statements clutter your code.
2. Debug statements clutter the output of your program.
3. Debug statements must be removed after you’re done with them, which makes them non-reusable.
4. Debug statements require modification of your code to both add and to remove, which can introduce new bugs.

We can do better. We’ll explore how in future lessons.

## [3.5 — More debugging tactics](https://www.learncpp.com/cpp-tutorial/more-debugging-tactics/)

In the previous lesson (3.4 -- Basic debugging tactics), we started exploring how to manually debug problems. In that
lesson, we offered some criticisms of using statements to print debug text:

1. Debug statements clutter your code.
2. Debug statements clutter the output of your program.
3. Debug statements require modification of your code to both add and to remove, which can introduce new bugs.
4. Debug statements must be removed after you’re done with them, which makes them non-reusable.

We can mitigate some of these issues. In this lesson, we’ll explore some basic techniques for doing so.

### 3.5.1 - Conditionalizing your debugging code

When you’re done with the debugging statement, you’ll either need to remove them, or comment them out. Then if you want
them again later, you’ll have to add them back, or uncomment them.

One way to make it easier to disable and enable debugging throughout your program is to make your debugging statements
conditional using preprocessor directives:

```c++
#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
#ifdef ENABLE_DEBUG
std::cerr << "getUserInput() called\n";
#endif
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
#ifdef ENABLE_DEBUG
std::cerr << "main() called\n";
#endif
    int x{ getUserInput() };
    std::cout << "You entered: " << x;

    return 0;
}
```

Pros:

1. Now we can enable debugging simply by commenting / uncommenting #define ENABLE_DEBUG. This allows us to reuse
   previously added debug statements and then just disable them when we’re done with them, rather than having to
   actually remove them from the code.
2. If this were a multi-file program, the #define ENABLE_DEBUG would go in a header file that’s included into all code
   files so we can comment / uncomment the #define in a single location and have it propagate to all code files.

Cons:

1. This addresses the issue with having to remove debug statements and the risk in doing so, but at the cost of even
   more code clutter.
2. Another downside of this approach is that if you make a typo (e.g. misspell “DEBUG”) or forget to include the header
   into a code file, some or all of the debugging for that file may not be enabled.

So although this is better than the unconditionalized version, there’s still room to improve.

### 3.5.2 - Using a logger

An alternative approach to conditionalized debugging via the preprocessor is to send your debugging information to a log
file. A **log file** is a file (normally stored on disk) that records events that occur in software. The process of
writing information to a log file is called **logging**. Most applications and operating systems write log files that
can be used to help diagnose issues that occur.

Pros

1. Because the information written to a log file is separated from your program’s output, you can avoid the clutter
   caused by mingling your normal output and debug output.
2. Log files can also be easily sent to other people for diagnosis -- so if someone using your software has an issue,
   you can ask them to send you the log file, and it might help give you a clue where the issue is.
3. Conditional compilation directives are also not required using this method, as most loggers have a method to
   reduce/eliminate writing output to the log. This makes the code a lot easier to read, as the conditional compilation
   lines add a lot of clutter.

## [3.6 — Using an integrated debugger: Stepping](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-stepping/)

In previous lessons, we explored various ways to alter your code to help with debugging, including printing diagnostic
information or using a logger. These are simple methods for examining the state of a program while it is running.

Although these can be effective if used properly, they still have downsides:

1. they require altering your code, which
   takes time and can introduce new bugs, and they clutter your code, making the existing code harder to understand.
2. Behind the techniques we’ve shown so far is an unstated assumption: that once we run the code, it will run to
   completion (only pausing to accept input) with no opportunity for us to intervene and inspect the results of the
   program at whatever point we want.

### 3.6.1 - The debugger

A **debugger** is a computer program that allows the programmer to control how another program executes and examine the
program state while that program is running.

The power behind the debugger is twofold: the ability to precisely control execution of the program, and the ability to
view (and modify, if desired) the program’s state.

1. Early Debuggers
    - Early debuggers, such as gdb, were separate programs that had command-line interfaces, where the programmer had to
      type arcane commands to make them work.
    - Later debuggers (such as early versions of Borland’s turbo debugger) were
      still standalone, but came with their own “graphical” front ends to make working with them easier.
2. Integrated Debuggers
   Many modern IDEs available these days have an integrated debugger -- that is, a debugger uses the same interface as
   the code editor, so you can debug using the same environment that you use to write your code (rather than having to
   switch programs).

### 3.6.2 - How to use the debugger

**Stepping** is the name for a set of related debugger features that let us execute (step through) our code statement
by statement.

#### 3.6.2.1 - Step into

The **step into** command executes the next statement in the normal execution path of the program, and then pauses
execution of the program so we can examine the program’s state using the debugger. If the statement being executed
contains a function call, step into causes the program to jump to the top of the function being called, where it will
pause.

#### 3.6.2.2 - Step over

Like step into, The **step over** command executes the next statement in the normal execution path of the program.
However, whereas step into will enter function calls and execute them line by line, step over will execute an entire
function without stopping and return control to you after the function has been executed.

The step over command provides a convenient way to skip functions when you are sure they already work or are not
interested in debugging them right now.

#### 3.6.2.3 - Step out

Unlike the other two stepping commands, Step out does not just execute the next line of code. Instead, it executes all
remaining code in the function currently being executed, and then returns control to you when the function has returned.

#### 3.6.2.4 - Step back(Not widely supported at the time writing)

When stepping through a program, you can normally only step forward. It’s very easy to accidentally step past (overstep)
the place you wanted to examine.

If you step past your intended destination, the usual thing to do is stop debugging and restart debugging again, being a
little more careful not to pass your target this time.

Some debuggers (such as Visual Studio Enterprise Edition and GDB 7.0) have introduced a stepping capability generally
referred to as step back or reverse debugging. The goal of a step back is to rewind the last step, so you can return the
program to a prior state. This can be useful if you overstep, or if you want to re-examine a statement that just
executed.

## 3.7 -[3.7 — Using an integrated debugger: Running and breakpoints](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-running-and-breakpoints/)

### 3.7.1 - Run to cursor

The first useful command is commonly called Run to cursor. This Run to cursor command executes the program until
execution reaches the statement selected by your cursor. Then it returns control to you so you can debug starting at
that point. This makes for an efficient way to start debugging at a particular point in your code, or if already
debugging, to move straight to some place you want to examine further.

### 3.7.2 - Continue

Once you’re in the middle of a debugging session, you may want to just run the program from that point forward. The
easiest way to do this is to use the continue command. The continue debug command simply continues running the program
as per normal, either until the program terminates, or until something triggers control to return back to you again (
such as a breakpoint, which we’ll cover later in this lesson).

### 3.7.3 - Start

The continue command has a twin brother named start. The start command performs the same action as continue, just
starting from the beginning of the program. It can only be invoked when not already in a debug session.

### 3.7.4 - Breakpoints

The last topic we are going to talk about in this section is breakpoints. A breakpoint is a special marker that tells
the debugger to stop execution of the program at the breakpoint when running in debug mode.

### 3.7.5 - Set next statement

The set next statement command allows us to change the point of execution to some other statement (sometimes informally
called jumping). This can be used to jump the point of execution forwards and skip some code that would otherwise
execute, or backwards and have something that already executed run again.

## [3.8 — Using an integrated debugger: Watching variables](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-watching-variables/)

In the previous lessons (3.6 -- Using an integrated debugger: Stepping and 3.7 -- Using an integrated debugger: Running
and breakpoints), you learned how to use the debugger to watch the path of execution through your program. However,
stepping through a program is only half of what makes the debugger useful. The debugger also lets you examine the value
of variables as you step through your code, all without having to modify your code.

1. Watching a variable is the process of inspecting the value of a variable while the program is executing in debug
   mode. Most debuggers provide several ways to do this.

2. **The watch window** is a window where you can add variables you would like to continually inspect, and these
   variables will be updated as you step through your program.

3. The watch window can evaluate expressions too

## [3.9 — Using an integrated debugger: The call stack](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-the-call-stack/)

When your program calls a function, you already know that it bookmarks the current location, makes the function call,
and then returns. How does it know where to return to? The answer is that it keeps track in the call stack.

The call stack is a list of all the active functions that have been called to get to the current point of execution. The
call stack includes an entry for each function called, as well as which line of code will be returned to when the
function returns. Whenever a new function is called, that function is added to the top of the call stack. When the
current function returns to the caller, it is removed from the top of the call stack, and control returns to the
function just below it.

Conclusion

Congratulations, you now know the basics of using an integrated debugger! Using **stepping, breakpoints, watches, and
the call stack window**, you now have the fundamentals to be able to debug almost any problem. Like many things,
becoming good at using a debugger takes some practice and some trial and error. But again, we’ll reiterate the point
that the time devoted to learning how to use an integrated debugger effectively will be repaid many times over in time
saved debugging your programs!

## [3.10 — Finding issues before they become problems](https://www.learncpp.com/cpp-tutorial/finding-issues-before-they-become-problems/)

### 3.10.1 - Don’t make errors

Well, the best thing is to not make errors in the first place. Here’s an incomplete list of things that can help avoid
making errors:

- Follow best practices
- Don’t program when tired
- Understand where the common pitfalls are in a language (all those things we warn you not to do)
- Keep your programs simple
- Don’t let your functions get too long
- Prefer using the standard library to writing your own code, when possible
- Comment your code liberally

### 3.10.2 - Refactoring your code

1. Long functions are complex and hard to understand. Frequently refactor long functions into shorter ones.
2. So how long is too long for a function?
    - A function that takes up one vertical screen worth of code is generally regarded as far too long -- if you have to
      scroll to read the whole function, the function’s comprehensibility drops significantly.
    - But the shorter the better -- functions less than ten lines are good. Functions that are less than five lines are
      even better.

### 3.10.3 - An introduction to defensive programming

Defensive programming is a practice whereby the programmer tries to anticipate all of the ways the software could be
misused, either by end-users, or by other developers (including the programmer themselves) using the code. These misuses
can often be detected and then mitigated (e.g. by asking a user who entered bad input to try again).

### 3.10.4 - Other

1. Unit testing
2. static analysis tools(sometimes informally called linters) are programs that analyze your code to identify specific
   semantic issues (in this context, static means that these tools analyze the source code).  
   [List of static analysis tools](https://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis#C,_C++).

## 3.11 - Summary
