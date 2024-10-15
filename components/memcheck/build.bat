g++ -c -DBUILD_MY_DLL memcheck_shared_lib.cpp
g++ -shared -o memcheck_shared_lib.dll memcheck_shared_lib.o -Wl,--out-implib,memchecklibshared_lib.a