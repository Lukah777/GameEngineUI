#pragma once
#include "Component.h"

namespace Engine
{
    class RadioButtonComponent : public Component
    {
    private:
        bool m_on = false;
        Color m_ogColor = { 0,0,0 };
        Color m_hoverColor = { 255, 255, 0 };
        std::string m_gameObjectStr;
        GameObject* m_pGameObject = nullptr;
        bool m_hovering = false;
    public:
        RadioButtonComponent(System* pSystem, GameObject* pGameObject, bool on, std::string gameObjectStr);
        bool Update(System* pSystem) override;
        void Activate(System* pSystem);
        GameObject* GetGameObject() { return m_pGameObject; }
        void SetOn(bool on) { m_on = on; };
        bool GetOn() { return m_on; }
    };
}