# 0.5 - Introduction to the compiler, linker, and libraries
The material makes note of *makefiles as a file that describes how to build a program (e.g. which files to compile and link or otherwise process in various ways)*, but they are not part of the core C++ language. HOWEVER, they are a big part of ROS and should be learned elsewhere.

# 0.6 - IDEs
I'm using Visual Studio Code on my Ubuntu machine. Follow [these instructions](https://code.visualstudio.com/docs/cpp/config-linux) to install the extension and compiler. The System76 with Ubuntu 18 has the following g++ --version output:
```
g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
```
With Ubuntu 20, the System76 has the following output:
```
gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04) 
```

# 0.7 - Compiling Your First Program
Follow the [hello world instructions](https://code.visualstudio.com/docs/cpp/config-linux) at the bottom of the VS Code + Linux config tutorial to check that everything is set up. 
- The tasks.json file created by going to "Terminal > Configure Default Build Task" and selecting "C/C++: g++ build active file" points to the g++ compiler.

- *Ctrl + Shift + B* builds the runs the build task when "isDefault":true. Note: the task in the example builds the active file, so make sure the file you want to build is active.
- First, "Run > Add Configuration > C++ (GDb/LLDB) > g++ build and debug active file" which creates launch.json. Then, F5 to debug

To do later: read up on the [VS Code User Interface](https://code.visualstudio.com/docs/getstarted/userinterface) and [VS Code User Guide](https://code.visualstudio.com/docs/editor/codebasics) docs.

# 0.8 - A few common C++ problems
Disable compiler extensions by adding the following command to tasks.json to avoid writing compiler-specific code.
```
"args": [
            ...,
            "-pedantic-errors"
        ],
```

# 0.11 - Configuring your compiler: Warning and error levels
Increase warning levels in gcc by adding the following arg to tasks.json
```
"args": [
            ...,
            "-Werror"
        ],

```

# 0.12 - Configuring your compiler: Choosing a language standard
To configure the language standard in gcc, pass one of the compiler flags (-std=c++11, -std=c++14, -std=c++17, -std=c++2a) for C++11/14/17/2a support, respectively.
```
"args": [
            ...,
            "-std=c++17"
        ],

```

