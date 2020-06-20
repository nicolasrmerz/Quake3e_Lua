#include "lua_fs.h"
int qlua_read_fs(lua_State *L) {
    char filename [MAX_OSPATH];

    union {
        char *c;
        void *v;
    } f;

    if(lua_type(L, 1) != LUA_TSTRING)
        Com_Error(ERR_FATAL, "qlua_read_fs: attempt to read non-string filename");

    Q_strncpyz(filename, lua_tostring(L, 1), sizeof (filename));

    int len = FS_ReadFile( filename, &f.v );

    if(len < 0)
	    Com_Error(ERR_FATAL, "qlua_read_fs: attempt to read file that doesn't exist");

    lua_pushlstring(L, f.c, (size_t)len);

    return 1;
}

int qlua_write_fs(lua_State *L) {
    char filename [MAX_OSPATH];

    if(lua_type(L, 1) != LUA_TSTRING)
        Com_Error(ERR_FATAL, "qlua_write_fs: attempt to write non-string filename");

    if(lua_type(L, 2) != LUA_TSTRING)
        Com_Error(ERR_FATAL, "qlua_write_fs: attempt to write non-string");

    // Pushes the length of the buffer onto the stack
    lua_len(L, 2);

    int file_len = (int)lua_tonumber(L, -1);

    // Pop str length off stack
    lua_pop(L, 1);

    if (file_len < 0)
        Com_Error(ERR_FATAL, "qlua_write_fs: file length < 0: %i", file_len);

    Q_strncpyz(filename, lua_tostring(L, 1), sizeof (filename));

    FS_WriteFile( filename, (void *)lua_tostring(L,2), file_len);

    return 0;
}


// USE lua_register INSTEAD!!!!!
// E.g.
// lua_register(L, "LuaFunctionName", c_funcion_Name)
static const struct luaL_Reg fs_l [] = {
    {"read", qlua_read_fs},
    {"write", qlua_write_fs},
    {NULL, NULL}
};

int qlua_open_fs(lua_State *L) {
    luaL_newlib (L, fs_l);
    lua_setglobal(L, "qfs");

    return 1;
}
