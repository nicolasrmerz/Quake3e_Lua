#include "../lua-src/lauxlib.h"
#include "../lua-src/lua.h"
#include "../lua-src/lualib.h"
#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"


qboolean qlua_checkhook(lua_State *L, const char *hook);

void qlua_gethook(lua_State *L, const char *hook);

int qlua_check_and_get_hook(lua_State *L, const char *hook);

void qlua_pcall(lua_State *L, int nargs, int nresults, qboolean washook);
