#include <iostream>
#include <GL/glew.h>
#include <signal.h>

#define IsTrace 0
#define ASSERT(x) if(!(x)) __builtin_trap();
#define CallGL(x) ClearLogs();\
    x;\
    ASSERT(LogCall(#x, __FILE__, __LINE__))

void ClearLogs();

bool LogCall(std::string function, std::string file, int line);

#define LogTrace(...) if(IsTrace) printf(__VA_ARGS__)