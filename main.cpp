#include <iostream>
#include <Launcher.h>
#include <lua.hpp>

int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_jit(L);
    luaL_dostring(L, "print('helloworld from lua')");
    lua_close(L);

    Nanometro::Launcher* RHI = new Nanometro::Launcher();

    return RHI->Init(0);
}