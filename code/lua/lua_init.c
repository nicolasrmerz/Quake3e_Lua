#include "lua_common.h"
#include "lua_libs.h"
#define LUA_EXT ".lua"

// Call this from Client/Server Init - Make specific ones for each eventually
void L_Init() {
    union {
        char *c;
        void *v;
    } f;

	cvar_t *lua_dir_name;

    char scriptName [MAX_OSPATH];

	L = NULL;
	lua_dir_name = Cvar_Get( "fs_lua", "", CVAR_INIT | CVAR_SYSTEMINFO );
	if(lua_dir_name && lua_dir_name->string[0]) {
        Com_sprintf( scriptName, sizeof (scriptName), "%s%s", lua_dir_name->string, LUA_EXT);


        // Load into a buffer just to first confirm the main lua script exists
        // Normally, should instead use the qlua_loadfile function
        int len = FS_ReadFile( scriptName, &f.v );
        //int len = qlua_loadScript(scriptName, &buff);
        if(!len)
            return;


		Com_Printf( "--- Initializing Lua ---\n" );
		L = luaL_newstate();
		luaL_openlibs(L);
        qlua_openlibs(L);

        // Run the lua initialization script
        // luaL_dofile for init.lua - find out how to allow this in C but restrict it in the lua scripts
	if(qlua_loadfile(L, "init.lua") != LUA_OK)
            Com_Error(ERR_FATAL, "error loading init.lua: %s", lua_tostring(L, -1));
        if(lua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK)
            Com_Error(ERR_FATAL, "error running init.lua: %s", lua_tostring(L, -1));

        // Run the actual script supplied by the user
        if(luaL_dostring(L, f.c) != LUA_OK)
            Com_Error(ERR_FATAL, "error running %s: %s", scriptName, lua_tostring(L, -1));

	Com_Printf( "L PTR VAL: %p\n", (void *) L);
    }
}
/*
int qlua_loadScript(const char *name, char **buff) {
    union {
        char *c;
        void *v;
    } f;

    int len = FS_ReadFile( name, &f.v );
    
    if(len)
        *buff = f.c;

    return len;
}
*/
int qlua_loadfile(lua_State *L, const char *filename) {
    union {
        char *c;
        void *v;
    } f;

    if(L == NULL)
        return 0;

    int len = FS_ReadFile( filename, &f.v );

    if(!len) {
	    lua_pushstring(L, "Loaded file has length of 0");
        return 1;
	}

    // Will be the different possible Lua error codes
    int res = luaL_loadstring(L, f.c);

    return res;
}

