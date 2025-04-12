#pragma once
#include "Component.h"
#include <string.h>

struct _Mix_Music;
struct Mix_Chunk;

namespace Engine 
{
    class SoundComponent : public Component
    {
    private:
        _Mix_Music* m_music = nullptr;
        Mix_Chunk* m_SFX = nullptr;
        int m_volume = 0;
    public:
        SoundComponent(System* pSystem, GameObject* pGameObject, std::string file, bool music = false);
        ~SoundComponent();
        bool Update(System* pSystem) override;
        void PlaySound();
    };
}


