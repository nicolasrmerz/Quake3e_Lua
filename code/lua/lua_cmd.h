#include "../lua-src/lauxlib.h"
#include "../lua-src/lua.h"
#include "../lua-src/lualib.h"
#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"

int qlua_exec_cmd(lua_State *L);

int qlua_get_sys_time(lua_State *L);

int qlua_print(lua_State *L);

int qlua_open_cmd(lua_State *L);
