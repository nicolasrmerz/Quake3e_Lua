#include "../lua-src/lauxlib.h"
#include "../lua-src/lua.h"
#include "../lua-src/lualib.h"
#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"
#include "lua_cmd.h"
#include "lua_fs.h"

void qlua_openlibs(lua_State *L);
