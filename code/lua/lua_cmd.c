#include "lua_cmd.h"

int qlua_exec_cmd(lua_State *L) {
    char cmd [MAX_CMD_LINE];
    if(lua_type(L, 1) != LUA_TSTRING)
        Com_Error(ERR_FATAL, "qlua_run_cmd: attempt to run non-string");

    Q_strncpyz(cmd, lua_tostring(L, 1), sizeof (cmd));

    Cbuf_ExecuteText(EXEC_NOW, cmd);

    return 0;
}

int qlua_get_sys_time(lua_State *L) {
    int time = Sys_Milliseconds();

    lua_pushnumber(L, time);

    return 1;
}

int qlua_print(lua_State *L) {
    char buff [MAX_CMD_LINE];

    if(lua_type(L, 1) != LUA_TSTRING)
        Com_Error(ERR_FATAL, "qlua_print: attempt to print non-string");

    Q_strncpyz(buff, lua_tostring(L, 1), sizeof (buff));

    Com_Printf("%s\n", buff);

    return 0;
}

static const struct luaL_Reg cmd_l [] = {
    {"exec", qlua_exec_cmd},
    {"sys_time", qlua_get_sys_time},
    {"print", qlua_print},
    {NULL, NULL}
};

int qlua_open_cmd(lua_State *L) {
    luaL_newlib (L, cmd_l);
    lua_setglobal(L, "qcmd");

    return 1;
}
