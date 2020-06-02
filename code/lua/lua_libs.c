#include "lua_libs.h"

void qlua_openlibs(lua_State *L) {
    // CMD
    qlua_open_cmd(L);
    // FileSystem
    qlua_open_fs(L);
}
