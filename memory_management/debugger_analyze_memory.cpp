#include <stdio.h>
// To compile with debug symbols: g++ -g debugger_analyze_memory.cpp
// gdb a.out, then use the following commands:
// list
// break 5
// run
// step
// p str1
// p &str1
// x/7tb 0x7fffffffdc60
// x/7xb 0x7fffffffdc60
// x/7cb 0x7fffffffdc60

int main()
{
    char str1[]= "UDACITY";
    printf("%s",str1);

    return 0;
}
