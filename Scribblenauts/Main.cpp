#include "../NinjaKittenEngine/Engine/system.h"
#include "../NinjaKittenEngine/Engine/GameObject.h"
#include "../NinjaKittenEngine/BLD/BleachNew.h"

int main()
{
    BLEACH_INIT_LEAK_DETECTOR();
    
    Engine::System system;
    system.Inialize("Scribblenauts", 1024, 768);
    system.Run();

    BLEACH_DUMP_AND_DESTROY_LEAK_DETECTOR();
    return 0;
}