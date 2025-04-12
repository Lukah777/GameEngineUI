#pragma once
#include "Component.h"


namespace Engine 
{
    struct FriendListComponent;

    class FriendButtonComponent : public Component
    {
    private:
        Color m_ogColor = { 0,0,0 };
        Color m_hoverColor = { 255, 255, 0 };
        bool m_hovering = false;
        bool m_moveUp = false;
        bool m_moveDown = false;
        int m_timer = 0;
        FriendListComponent* m_firendList = nullptr;
        int m_oldY = NULL;
    public:
        FriendButtonComponent(System* pSystem, GameObject* pGameObject);
        bool Update(System* pSystem) override;
        void Activate(System* pSystem);
        void ScrollUp(System* pSystem);
        void ScrollDown(System* pSystem);
        void Drag(System* pSystem, int mouseY);
        void SetOldY(int oldY) { m_oldY = oldY; };
    };
}