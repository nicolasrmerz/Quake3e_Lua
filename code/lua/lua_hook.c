#include "lua_hook.h"

qboolean qlua_checkhook(lua_State *L, const char *hook)
{
    qboolean found;

    if (hook) {
        lua_getglobal(L, "CheckHook");
        lua_pushstring(L, hook);

        qlua_pcall(L,1,1,qfalse);

        found = (qboolean)lua_toboolean(L, -1);
        lua_pop(L, 1);
        return found;
    }
    return 0;
}

void qlua_gethook(lua_State *L, const char *hook)
{
    if (hook) {
        lua_getglobal(L, "CallHook");
        lua_pushstring(L, hook);
    }
}

int qlua_check_and_get_hook(lua_State *L, const char *hook)
{
    if (qlua_checkhook(L, hook)) {
        qlua_gethook(L, hook);
        return 1;
    }
    return 0;
}

void qlua_pcall(lua_State *L, int nargs, int nresults, qboolean washook) {
    if(washook) nargs++;
    if(lua_pcall(L,nargs,nresults,0) != 0)
        Com_Error(ERR_FATAL, "qlua_pcall: %s", lua_tostring(L, -1));
}
