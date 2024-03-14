
@echo off
set include_paths= /I"C:\SDL2\access_path" /I"C:\glew\glew-2.1.0\include"

set lib_path= "C:\SDL2\lib\x64"

set common_compiler_flags= -MTd -nologo -fp:fast -Gm- -GR- -EHa- -O2 -Oi -WX -W4 -wd4201 -wd4100 -wd4189  -wd4244 -wd4505 -wd4026 -wd4028 -wd4996 -DDEBUG=0 -DWIN32_PROGAM=1 -FC -Z7 
set common_linker_flags= -incremental:no -opt:ref  user32.lib opengl32.lib glew32.lib SDL2main.lib SDL2.lib SDL2_image.lib SDL2_mixer.lib  gdi32.lib winmm.lib imm32.lib version.lib user32.lib shell32.lib dwmapi.lib

if not exist build mkdir build
pushd build

cl  %common_compiler_flags% /Fe:win32_main.exe ..\source\main.c -Fmwin32_main.map %include_paths% /link /LIBPATH:C:\SDL2\lib\x64 /LIBPATH:C:\glew\glew-2.1.0\lib\Release\x64  %common_linker_flags% /SUBSYSTEM:WINDOWS  






















REM old glfw_build
REM cl -nologo -Zi -FC -Fo -MT -EHsc  ..\source\win32_main.cpp  user32.lib gdi32.lib shell32.lib glfw3_mt.lib opengl32.lib glew32s.lib soloud_static_x64.lib Winmm.lib







REM to link -lfltk I linked -lole32 -luuid -lcomctl32
REM to link -lsoloud_static I needed -lWinmm as a backend (and -static-libgcc -static-libstdc++ I think)
REM to link pthread i needed -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic (I think)



REM (OLD MINGW64 compile)
REM g++ -m64 ..\source\main.c -lfltk -lglfw3 -lgdi32 -lopengl32 -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lsoloud_static -lWinmm -lole32 -luuid -lcomctl32 -o main.exe


REM 64 bit and 32 bit switches
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86


REM 32 bit compile:
REM run in command prompt.  RUN:
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
REM then run:
REM cl -MT -nologo -Gm- -GR- -EHa- -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -DINTERNAL=1 -DDEBUG=1 -Zi -FC -Fm win32_main.cpp /link -opt:ref -subsystem:windows,5.1 user32.lib gdi32.lib opengl32.lib


REM Compiler Flags:

REM Zi  : debug info (Z7 older debug format for complex builds)
REM Zo  : More debug info for optimized builds
REM FC  : Full path on errors
REM Oi  : Always do intrinsics with you can
REM Od  : No optimizations
REM O2  : Full optimizations
REM MT  : Use the c static lib instead of searching for dll at run-time
REM MTd : Sabe as MT but using the debug version of CRT
REM GR- : Turn off C++ run-time type info
REM Gm- : Turn off incremental build
REM EHa-: Turn off exception handling
REM WX  : Treat warning as errors
REM W4  : Set Warning level to 4 (Wall to all levels)
REM wd  : Ignore warning
REM fp:fast    : Ignores the rules in some cases to optimize fp operations
REM Fmfile.map : Outputs a map file (mapping of the functions on the exr)

REM Linker Options:

REM subsystem:windows,5.1 : Make exe compatible with Windows XP (only works on x86)
REM opt:ref               : Don't put unused things in the exe
REM incremental:no        : Don't need to do incremental builds
REM LD                    : Build a dll
REM PDB:file.pdb          : Change the .pdb's path