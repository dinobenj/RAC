# Rudimentary Anti-Cheat
Yeah I love cheating *SLATT*
## Debug Auditor

The debug auditor is tasked with identifying any potentially suspicious programs operating on a system. It achieves this by detecting programs that have a debugger attached. The presence of such a program may indicate an attempt by the user to manipulate data within the program.

### Setup
Make sure your paths are set correctly in your C/C++ properties file. especially for the use of `winternl.h`.

```
"includePath": [
                "${workspaceFolder}/**",
                "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um"
                //My winternl.h Path ^
            ],
```

Also make sure that the file has the right intelliSense Mode. Sometimes the even if the include path is correctly set, the code still will not compile.

```
"intelliSenseMode": "windows-msvc-x64"
```
### Using the Debug Auditor

Here is an example of program output where a program called `Debugged.exe` that is detected.

```
Checking all processes for debugging status...
[DEBUGGED] Process ID: 12345
  Process Name: Debugged.exe
```

The data collected from the debug analyzer will be sent to the database for further analysis.
But this program also provides a local analysis option. Debugged programs can be compared to
a list of other program names for a naive cheater analysis. 

```
./program_checker <program data> <programs>
```

For understanding the workflow of the program I have provided a Snakemake pipeline.
Snakemake is an easy to use, Python-like language to organize workflows. In this case it was
used to make the program and data transportation easier to understand. 
