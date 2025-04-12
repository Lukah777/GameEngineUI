#pragma once
#include "System.h"
#include <vector>

struct Color {
    int r = 0;
    int g = 0;
    int b = 0;
};

namespace Engine
{
    class GameObject;
    class Component
    {
    private:
         MessageSystem* m_pMsgSys = nullptr;
         GameObject* m_Owner = nullptr;
    public:
        

        Component() {};
        Component(System* pSystem, GameObject* pGameObject);
        virtual ~Component() {};
        virtual bool Update(System* pSystem);
        virtual void Render(System* pSystem);
        virtual void HandleMessage(Message msg);
        MessageSystem* GetMessageSys() { return m_pMsgSys; };
        GameObject* GetOwner();
    };
}



