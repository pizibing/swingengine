#include <mach-o/dyld.h>
#include <cstdlib>
#include <cstring>

extern "C" 
{
	
/*--------------------------------------------------------------------------*/
void* SE_GL_GetFunctionPointer(const char* acFunction)
{
    NSSymbol tempSymbol;
    char* acSymbolName;

    /* Prepend a '_' for the Unix C symbol mangling convention. */
    acSymbolName = (char*)malloc(strlen((const char*)acFunction) + 2);
    strcpy(acSymbolName+1, (const char*)acFunction);
    acSymbolName[0] = '_';

    tempSymbol = 0;
    if( NSIsSymbolNameDefined(acSymbolName) )
	{
        tempSymbol = NSLookupAndBindSymbol(acSymbolName);
	}

    free(acSymbolName);
    return tempSymbol ? NSAddressOfSymbol(tempSymbol) : 0;
}
/*--------------------------------------------------------------------------*/

} // extern "C"