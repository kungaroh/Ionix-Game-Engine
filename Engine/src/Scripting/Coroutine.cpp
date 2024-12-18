#include "Coroutine.h"

namespace IonixEngine 
{
    void runCoroutine(lua_State* L)
    {
	
	    lua_getglobal(L, "myCoroutineFunction");  // Push the coroutine function onto the stack
        lua_State* co = lua_newthread(L);         // Create a new coroutine
        
        lua_pushvalue(L, -1);                     // Copy the function to the new thread
        lua_xmove(L, co, 1);                      // Move it to the new thread
        
        int status = lua_resume(co, nullptr, 0, 0);  // Start the coroutine
        if (status == LUA_YIELD) {
            // Coroutine yielded, you can call again later
        } else if (status == LUA_OK) {
            // Coroutine finished
        } else {
            // Error handling
            const char* error = lua_tostring(L, -1);
            printf("Error: %s\n", error);
            lua_pop(L, 1); // Remove error message from stack
        }
    }
}
