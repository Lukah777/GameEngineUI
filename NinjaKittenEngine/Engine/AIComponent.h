#pragma once
#include "Component.h"
#include "HeroComponent.h"
#include "SoundComponent.h"

namespace Engine {
    class AIComponent : public Component
    {
    private:
        HeroComponent* m_pObjectHeroComp = nullptr;
        SoundComponent* m_pSoundComp = nullptr;
        bool m_hovering = false;
    public:
        AIComponent(System* pSystem, GameObject* pGameObject);
        bool Update(Engine::System* pSystem) override;
        void Activate(System* pSystem);
    };
}


