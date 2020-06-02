#include "lua_cmd.h"

int qlua_exec_cmd(lua_State *L) {
    char cmd [MAX_CMD_LINE];
    if(lua_type(L, 1) != LUA_TSTRING)
        Com_Error(ERR_FATAL, "qlua_run_cmd: attempt to run non-string");

    Q_strncpyz(cmd, lua_tostring(L, 1), sizeof (cmd));

    Cbuf_ExecuteText(EXEC_NOW, cmd);

    return 0;
}
static const struct luaL_Reg cmd_l [] = {
    {"exec", qlua_exec_cmd},
    {NULL, NULL}
};

int qlua_open_cmd(lua_State *L) {
    luaL_newlib (L, cmd_l);
    lua_setglobal(L, "qcmd");

    return 1;
}
