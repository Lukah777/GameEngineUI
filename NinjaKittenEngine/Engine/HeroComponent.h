#pragma once
#include "Component.h"

namespace Engine 
{
    class HeroComponent : public Component
    {
    private:
        bool m_collision = false;
        System* m_pSystem;
        GameObject* m_pHealthBar = nullptr;
        GameObject* m_pMoneyCount = nullptr;
        GameObject* m_pHint = nullptr;
        GameObject* m_pHintCheckbox = nullptr;
        GameObject* m_pToggleRespawns = nullptr;
        GameObject* m_pEasy = nullptr;
        GameObject* m_pNormal = nullptr;
        GameObject* m_pHard = nullptr;
        std::vector<GameObject*> m_pEnemies;
        int m_health = 100;
        int m_money = 0;
    public:
        HeroComponent(System* pSystem, GameObject* pGameObject);
        void HandleMessage(Engine::Message msg);
        void UpdateHealth(System* pSystem ,int change);
        void UpdateMoney(System* pSystem, int change);
        bool Update(Engine::System* pSystem) override;
    };
}


