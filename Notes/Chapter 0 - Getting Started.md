# 0.5 - Introduction to the compiler, linker, and libraries
The material makes note of *makefiles as a file that describes how to build a program (e.g. which files to compile and link or otherwise process in various ways)*, but they are not part of the core C++ language. HOWEVER, they are a big part of ROS and should be learned elsewhere.

# 0.6 - IDEs
I'm using Visual Studio Code on my Ubuntu machine. Follow [these instructions](https://code.visualstudio.com/docs/cpp/config-linux) to install the extension and compiler. This machine has the following g++ --version output:
```
g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
```

# 0.7 - Compiling Your First Program
Follow the [hello world instructions](https://code.visualstudio.com/docs/cpp/config-linux) at the bottom of the VS Code + Linux config tutorial to check that everything is set up. 
- The tasks.json file created by going to "Terminal > Condigure Default Build Task" and selecting "C/C++: g++ build active file" points to the g++ compiler.

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


