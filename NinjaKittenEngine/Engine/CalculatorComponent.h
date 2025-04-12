#pragma once
#include "Component.h"
#include <string>

namespace Engine
{
    class CalculatorComponent : public Component
    {
    private:
        std::string m_equation;
    public:
        CalculatorComponent(System* pSystem, GameObject* pGameObject);
        bool Update(System* pSystem) override;
        void Calculate(char input);
    };
}


