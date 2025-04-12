#pragma once
#include "Component.h"
namespace Engine
{
    class EditButtonComponent : public Component
    {
    private:
        bool m_on = false;
        Color m_ogColor = { 0, 0, 255 };
        Color m_hoverColor = { 255, 255, 0 };
        Color m_onColor = { 0, 255, 0 };
        bool m_hovering = false;
    public:
        EditButtonComponent(System* pSystem, GameObject* pGameObject);
        bool Update(System* pSystem) override;
        void Activate();
        bool GetOn() { return m_on; };
    };

}