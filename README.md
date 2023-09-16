# CADExchangerTask
Program in C++ that implement support of 3D curves hierarchy

#  1. The Mathcad Curves file.xmcd can be used for visual representation of curves in space depending on different parameters. This file allows  to check the correctness of creating curves in a low-level language.
#  2. The Mathcad Curves file.pdf is a snapshot of curves with the given parameters.

# The main part of the program contains 2 header files located in the "include" directory and 2 implementation files in the "src" directory. 
#    3. The "constant.h" file contains symbolic constants that are connected to calculation files.
#    4. The "curves.h" file contains declarations of curve classes and functions.
#    5. The "curves.cpp" file contains realization of the curves class and functions
#    6. The "main.cpp" the file contains function callers, classes instantiation, and class methods invocation according to the task
#  7. Geometric3D.exe " obtained by compilation "main.cpp " and "curves.cpp " with subsequent linking by using makefile.

#  Additional part of the program "additionalDllOpenMP" contains 2 catalogs: "dllCompiling" and "execCompiling". Additional part of the program is implemented using the "Code::blocks" IDE.
#    8. "dllCompiling" directory contains the project to create "dllCompiling.dll" library from the "curves.h" and "main" file. "main.cpp " this is an analogue "curves.cpp " file with "__declspec(dllimport)" and "__declspec(dllimport) " wrappers.
#        "__declspec(dllimport/dllimport)" wrappers implement Application Programming Interface for communication between library and executable files. 
#    9. In "execCompiling" directory contains the project to create "execCompiling.exe" file. Executable file connect with "dllCompiling.dll" and doesn't work without it.
#    10. Other .dll files in the "additionalDllOpenMP" directory are used to connect the OpenMP library.



  

  
  
