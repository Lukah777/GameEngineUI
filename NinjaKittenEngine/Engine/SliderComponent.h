#pragma once
#include "Component.h"

namespace Engine
{
    class SliderComponent : public Component
    {
    private:
        int m_value = false;
        Color m_ogColor = { 0,0,0 };
        Color m_hoverColor = { 255, 255, 0 };
        std::string m_gameObjectStr;
        GameObject* m_pGameObject = nullptr;
        bool m_hovering = false;
    public:
        SliderComponent(System* pSystem, GameObject* pGameObject, int val, std::string gameObjectStr);
        bool Update(System* pSystem) override;
        void Activate();
        int GetVal() { return m_value; };
    };
}