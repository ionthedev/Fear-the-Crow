
#include "game/FearTheCrow.h"


#define MAX_COLUMNS 20

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //Initializes game and engine loop
    FearTheCrow game(true);

    return 0;
}