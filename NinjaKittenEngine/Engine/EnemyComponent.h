#pragma once
#include "Component.h"
namespace Engine
{
    class EnemyComponent : public Component
    {
    private:
    public:
        EnemyComponent(System* pSystem, GameObject* pGameObject);
    };
}


