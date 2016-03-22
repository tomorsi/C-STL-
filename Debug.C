#include <stdio.h>
#include <stdarg.h>

#include "Debug.h"

bool Debug::bDebug = false;

void Debug::debugPrint(const char * format, ...)
{
  if (bDebug)
  {
    char buffer[1024];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    printf(buffer);
    va_end (args);
  }
}
