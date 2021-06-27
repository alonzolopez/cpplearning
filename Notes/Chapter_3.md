# [3.1 - Syntax and Semantic Errors](https://www.learncpp.com/cpp-tutorial/syntax-and-semantic-errors/)
There are two general categories of erros: syntax and semantic (logic) errors.

Syntax errors are often caught by the compiler, but semantic errors are not. Fortunately, this is where debugging techniques come in handy.

# [3.2 - The Debugging Process](https://www.learncpp.com/cpp-tutorial/the-debugging-process/)
Just walks through the debugging thought process.

# [3.3 - A Strategy for Debugging](https://www.learncpp.com/cpp-tutorial/a-strategy-for-debugging/)

The majority of time spent debugging is spent trying to find the source of the problem. The general approach of trying to find problems is:

1. Figure out how to reproduce the problem.
2. Run the program and gather information to narrow down where the problem is.
3. Repeat the prior step until you find the source of the problem.

Be aware that the problem may not be reproduced 100% of the time.

# [3.4 - Commenting Out Your Code](https://www.learncpp.com/cpp-tutorial/basic-debugging-tactics/)
Here are a few useful debugging tactics:

1. **Comment out code** to identify the source of the error.
2. **Validate your code flow** with print statements. **Tip:** use **std::cerr** instead of of std::cout because std::cerr is not buffered and prints immediately, whereas std::cout is buffered and hence may crash before printing to the console.
    * Ensure that functions are getting called in the order you expect, or at all.
3. **Print values.**
    * Using print or debug statements is a useful rudimentary technique, but it clutters your code and console output and must be removed later. Additionally, the modification to add/remove may introduce more bugs. We have better debugging tactics than inserting print statements.

# [3.5 - More Debugging Tactics](https://www.learncpp.com/cpp-tutorial/more-debugging-tactics/)
To avoid using print statements everywhere, we can:
1. Conditionalize debugging code.
2. Use a logger.

## Conditionalizing Code
This is a slight improvement on normal print statements. 
```cpp
#include <iostream>

#define ENABLE_DEBUG

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

Then we only need to comment or uncomment `#define ENABLE_DEBUG` to run the debug print statements. You can do this across files in a multi-file program and just include `#define ENABLE_DEBUG` in the top-level header file. This is nice, but one con is that you'll have to include these print statements throughout all the files in your program, which could be hard in a large project.

## Using a Logger
You can write debugging info to a log file. Rather than write this log functionality yourself, you can use one of the many existing loggers including [plog](https://github.com/SergiusTheBest/plog). You just have to download and unzip the source files onto anywhere in your drive and then include the `<anywhere>\plog-<version>\include\` directory as an INCLUDE directory in your IDE.

# [3.6 - Using an Integrated Debugger: Stepping](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-stepping/)
At any point in time, your program keeps track of the **program state** including information like variables, what functions have been called, and the current point of execution. What if you could control the way a program is executed and examine the program state while the program is running? Enter the **debugger**.

## The Debugger
You can use VSCode's debugger to examine code line by line. Make sure your project is compiled using a debug build configuration (see [0.9 - Configuring your compiler: Build Configurations](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-build-configurations/)). Repeating the instructions to set up debugging in your project, 

1. click "Run > Add Configuration > C++ (GDb/LLDB) > g++ build and debug active file" which creates launch.json. 
2. If you'd like to step through the code, in your `launch.json` change `"stopAtEntry": true` to `"stopAtEntry": false`.
3. Then, F5 to debug. 

## Stepping
**Stepping** is the name for a set of debugger features that let us step through our code statement by statement.

**Step into** executes the next statement in the normal execution path of the program, and then pauses execution of the program so we can examine the program's state using the debugger.

**Step over** executes the next statement in the normal execution path of the program and will execute an entire function without stopping and return control after the function has been executed.

**Step out** executes all remaining code in the function currently being executed, and then returns control to you when the function has returned.

Stepping too far usually means you have to restart the debugging process and have to restart the process.

# [3.7 - Using an Integrated Debugger: Running and Breakpoints](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-running-and-breakpoints/)

While stepping is useful, it may take a long time to get to points in the code for large programs. For that reason we have **Run to Cursor** and **Breakpoints**.

## Run To Cursor
The **Run to Cursor** command executes the program until execution reaches the statement selected by the cursor. 

In VSCode, you can *run to cursor* by first entering debug mode with F5 (only works when the Keychron is in MAC OS mode), then right clicking a statement in your code and choosing *Run to Cursor*, or by pressing the CTRL+F10 keys (CTRL+F10 doesn't work with the Keychron).

## Continue
The **continue** debug command simply continues running the program as per normal either until the program terminates or something triggers control to return to you back again (e.g. a breakpoint).

You can *continue* by pressing the F5 shortcut while already in debug mode.

## Start
The **start** command runs from the beginning of the program all the way until either the program terminates or something triggers control to return back to you again (e.g. a breakpoint).

## Breakpoints
A **breakpoint** is a special marker that tells the debugger to stop execution of the program at the breakpoint when running in debug mode.

In VSCode, you can set a breakpoint by clicking on the line to use as a breakpoint, then clicking **Run** > **Toggle Breakpoint** or by clicking on the line then hitting the F9 shortcut key.

A red circle will appear to mark the breakpoint.

Breakpoints have a few advantages or just different features compared to run to cursor:

1. A breakpoint will cause the debugger to return control every time they are encountered. Run to cursor will only run to the cursor once, e.g. in a function.
2. Breakpoints will persist until you remove them.

Note that breakpoints not placed in the execution path will not cause the debugger to halt execution of the code. 

## Set Next Statement
The **set next statement** command allows to change the point of execution to some other statement (i.e. jumping). You can jump forwards or backwards.

This seems like a more advanced technique that warrants some more looking into.

# [3.8 - Using an Integrated Debugger: Watching Variables](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-watching-variables/)
The debugger lets you examine the value of variables as you step through code, all without having to modify your code.

## Watching Variables
**Watching a variable** is the process of inspecting the value of a variable while the program is executing in debug mode.

To view the value of variables as the program executes, either hover over the variable or look in the watch window (in the left while in debug mode for me by default).

## Local Watches
You can also inspect the value of local variables inside a function while debugging by looking under **Variables** > **Locals** in the left hand side.

# [3.9 - Using an Integrated Debugger: The Call Stack](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-the-call-stack/)
The call stack is a list of all the active functions that have been called to get to the current point of execution. The call stack includes an entry for each function called as well as which line of code will be returned to when the function returns. Whenever a new function is called, that function is added to the top of the call stack. When the current function returns to the caller, it is removed from the top of the call stack and control returns to the function just below it.

# [3.10 - Finding Issues Before They Become Problems](https://www.learncpp.com/cpp-tutorial/finding-issues-before-they-become-problems/)

Don't make errors.

Don't write functions that are too long. A one-page-long function is way too long.

Practice defensive programming.

If you do make errors, find them quickly before you get too far in your coding.

Write test functions, or practice **unit testing**.

Enforce constraints (more on this later with [7.17 - Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/)).

# [3.x - Chapter 3 Summary and Quiz](https://www.learncpp.com/cpp-tutorial/chapter-3-summary-and-quiz/)
