### Rudimentary Ani-Cheat
Yeah I love cheating *SLATT*
## Debug Auditor

The debug auditor is tasked with identifying any potentially suspicious programs operating on a system. It achieves this by detecting programs that have a debugger attached. The presence of such a program may indicate an attempt by the user to manipulate data within the program.

### Setup
If you are using VScode, make sure your paths are set correctly in your C/C++ properties file. especially for the use of `winternl.h`.

```
"includePath": [
                "${workspaceFolder}/**",
                "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um"
                //My winternl.h Path ^
            ],
```
