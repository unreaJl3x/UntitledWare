#include "bunnyhope.h"

void UntitledWare::Misc::Bunnyhope() {
    while(true) {
        if (csgo.isGrounded() && GetAsyncKeyState(VK_SPACE)) {
            cout << "Jump" << endl;
            Write<int>(csgo.pHandle, csgo.localPlayerAddress+hazedumper::signatures::dwForceJump, 6);
        }
    }
}