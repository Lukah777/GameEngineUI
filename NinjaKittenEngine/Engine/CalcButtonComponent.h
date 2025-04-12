#pragma once
#include "Component.h"


namespace Engine
{
    struct CalculatorComponent;

    class CalcButtonComponent : public Component
    {
    private:
        char m_buttonSymbol = ' ';
        Color m_ogColor = { 0,0,0 };
        Color m_hoverColor = { 255, 255, 0 };
        bool m_hovering = false;
        CalculatorComponent* m_calcComp = nullptr;
    public:
        CalcButtonComponent(System* pSystem, GameObject* pGameObject);
        bool Update(System* pSystem) override;
        void Activate(System* pSystem);
    };
}

