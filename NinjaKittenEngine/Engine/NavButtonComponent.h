#pragma once
#include "Component.h"

namespace Engine
{
    class NavButtonComponent : public Component
    {
    private:
        Color m_ogColor = {0,0,0};
        Color m_hoverColor = {255, 255, 0};
        std::string m_navGameObjectStr;
        GameObject* m_navGameObject = nullptr;
        GameObject* m_selfGameObject;
        bool m_hovering = false;
        bool m_quit = false;
        int m_oldX = NULL;
        int m_oldY = NULL;

    public:
        NavButtonComponent(System* pSystem, GameObject* pGameObject, std::string NavGameObjectStr, GameObject* pSelfGameObject);
        bool Update(System* pSystem) override;
        void Activate(System* pSystem);
        bool GetQuit() { return m_quit; }
        bool Drag(System* pSystem, int mouseX, int mouseY);
        void SetOldX(int oldX) { m_oldX = oldX; };
        void SetOldY(int oldY) { m_oldY = oldY; };
    };
}

