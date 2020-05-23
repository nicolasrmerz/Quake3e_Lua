#include "../qcommon/qcommon.h"
#include "lua_common.h"

void L_Init() {
	cvar_t *lua_script_name;
	L = NULL;
	lua_script_name = Cvar_Get( "fs_lua", "", CVAR_INIT | CVAR_SYSTEMINFO );
	if(lua_script_name && lua_script_name->string[0])
		Com_Printf( "--- Initializing Lua ---\n" );
		L = luaL_newstate();
		luaL_openlibs(L);
		Com_Printf( "L PTR VAL: %p\n", (void *) L);
}