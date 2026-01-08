#include "bnc.h"

int main() {
    Executable exe = {0};

    bnc_AddCommand(&exe, "cl", 
                         "main.c", 
                         "/MD", "/O2", "/TC", 
                         "/Fe:", "build/bnkget.exe",
                         "/Fo:", "build/",
                         "/Fd:", "build/");
    bnc_CmdPrint(&exe);
    bnc_CmdBuild(&exe);
}
