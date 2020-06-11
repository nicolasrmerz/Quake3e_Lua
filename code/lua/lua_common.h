#include <string.h>
#include "../lua-src/lauxlib.h"
#include "../lua-src/lua.h"
#include "../lua-src/lualib.h"
#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"

lua_State *L;

void L_Init(void);

int qlua_loadfile(lua_State *, const char *);

#define qlua_dofile(L, filename) (qlua_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0))
