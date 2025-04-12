#include "FriendListComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

Engine::FriendListComponent::FriendListComponent(System* pSystem, GameObject* pGameObject, std::vector<std::string> names)
    :Component(pSystem, pGameObject)
{
    m_names = names;
}

int GetIndex(int index)
{
    if (index >= 24)
    {
        return index - 24;
    }
    else if (index < 0)
    {
        return index + 24;
    }
    return index;
}

bool Engine::FriendListComponent::Update(System* pSystem)
{
    if (m_FriendButton1 == nullptr)
        m_FriendButton1 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton1")->GetComponent("TextComponent"));
    if (m_FriendButton2 == nullptr)
        m_FriendButton2 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton2")->GetComponent("TextComponent"));
    if (m_FriendButton3 == nullptr)
        m_FriendButton3 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton3")->GetComponent("TextComponent"));
    if (m_FriendButton4 == nullptr)
        m_FriendButton4 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton4")->GetComponent("TextComponent"));
    if (m_FriendButton5 == nullptr)
        m_FriendButton5 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton5")->GetComponent("TextComponent"));
    if (m_FriendButton6 == nullptr)
        m_FriendButton6 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton6")->GetComponent("TextComponent"));
    if (m_FriendButton7 == nullptr)
        m_FriendButton7 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton7")->GetComponent("TextComponent"));
    if (m_FriendButton8 == nullptr)
        m_FriendButton8 = dynamic_cast<TextComponent*>(pSystem->FindGameObject("FriendButton8")->GetComponent("TextComponent"));

    if (m_buttonTop == 1)
    {
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+1)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+2)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+3)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+4)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+5)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+6)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex+7)].c_str());
    }
    else if (m_buttonTop == 2)
    {
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }
    else if (m_buttonTop == 3)
    {
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }
    else if (m_buttonTop == 4)
    {
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }
    else if (m_buttonTop == 5)
    {
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }
    else if (m_buttonTop == 6)
    {
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }
    else if (m_buttonTop == 7)
    {
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }
    else if (m_buttonTop == 8)
    {
        m_FriendButton8->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex)].c_str());
        m_FriendButton1->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 1)].c_str());
        m_FriendButton2->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 2)].c_str());
        m_FriendButton3->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 3)].c_str());
        m_FriendButton4->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 4)].c_str());
        m_FriendButton5->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 5)].c_str());
        m_FriendButton6->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 6)].c_str());
        m_FriendButton7->ReloadText(pSystem, m_names[GetIndex(m_topScreenIndex + 7)].c_str());
    }

    m_beenUpdated = false;
    return true;
}

void Engine::FriendListComponent::UpdateIndex(int index)
{
    if (!m_beenUpdated)
    { 
        m_topScreenIndex += index;
        m_buttonTop += index;

        if (m_buttonTop > 8)
        {
            m_buttonTop = 1;
        }
        else if (m_buttonTop < 1)
        {
            m_buttonTop = 8;
        }

        if (m_topScreenIndex >= 24)
        {
            m_topScreenIndex = 0;
        }
        else if (m_topScreenIndex < 0)
        {
            m_topScreenIndex = 23;
        }

        m_beenUpdated = true;
    }
}
