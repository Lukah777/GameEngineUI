#pragma once
#include "Component.h"


namespace Engine
{
    struct TextComponent;

    class FriendListComponent : public Component
    {
    private:
        std::vector<std::string> m_names;
        int m_topScreenIndex = 0;
        int m_buttonTop = 1;
        bool m_beenUpdated = false;
        TextComponent* m_FriendButton1 = nullptr;
        TextComponent* m_FriendButton2 = nullptr;
        TextComponent* m_FriendButton3 = nullptr;
        TextComponent* m_FriendButton4 = nullptr;
        TextComponent* m_FriendButton5 = nullptr;
        TextComponent* m_FriendButton6 = nullptr;
        TextComponent* m_FriendButton7 = nullptr;
        TextComponent* m_FriendButton8 = nullptr;
    public:
        FriendListComponent(System* pSystem, GameObject* pGameObject, std::vector<std::string> names);
        bool Update(System* pSystem) override;
        void UpdateIndex(int index);
    };
}

