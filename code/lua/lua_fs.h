#include "../lua-src/lauxlib.h"
#include "../lua-src/lua.h"
#include "../lua-src/lualib.h"
#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"

int qlua_read_fs(lua_State *L);

int qlua_write_fs(lua_State *L);

int qlua_open_fs(lua_State *L);
