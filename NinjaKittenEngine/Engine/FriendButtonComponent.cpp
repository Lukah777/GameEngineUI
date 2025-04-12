#include "FriendButtonComponent.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "TextComponent.h"
#include "Gameobject.h"
#include <SDL.h>
#include "FriendListComponent.h"
#include <cmath>
#include <iostream>

Engine::FriendButtonComponent::FriendButtonComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::FriendButtonComponent::Update(System* pSystem)
{
    if (m_firendList == nullptr)
        m_firendList = dynamic_cast<FriendListComponent*>(pSystem->FindGameObject("FriendBackground")->GetComponent("FriendListComponent"));

    int x, y;
    SDL_GetMouseState(&x, &y);
    ImageComponent* imgComp = dynamic_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"));
    PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    TextComponent* textPosComp = dynamic_cast<TextComponent*>(GetOwner()->GetComponent("TextComponent"));

    if (m_ogColor.r == 0 && m_ogColor.g == 0 && m_ogColor.b == 0)
        m_ogColor = imgComp->GetColor();

    if (x > posComp->GetX() && x < posComp->GetX() + imgComp->GetImage()->GetW()
        && y > posComp->GetY() && y < posComp->GetY() + imgComp->GetImage()->GetH())
    {
        imgComp->SetColor(m_hoverColor);
        m_hovering = true;
    }
    else
    {
        imgComp->SetColor(m_ogColor);
        m_hovering = false;
    }

    if (m_moveUp)
    {
        m_timer++;
        posComp->SetXY(posComp->GetX(), posComp->GetY() - 1);
        textPosComp->GetMsgRect()->y = textPosComp->GetMsgRect()->y - 1;
    }
    else if (m_moveDown)
    {
        m_timer++;
        posComp->SetXY(posComp->GetX(), posComp->GetY() + 1);
        textPosComp->GetMsgRect()->y = textPosComp->GetMsgRect()->y + 1;
    }

    if (m_timer >= 96)
    {
        m_moveUp = false;
        m_moveDown = false;
        m_timer = 0;
        if (posComp->GetY() <= -96)
        {
            posComp->SetXY(posComp->GetX(), 672);
            textPosComp->GetMsgRect()->y = 697;
        }
        else if (posComp->GetY() >= 768)
        {
            posComp->SetXY(posComp->GetX(), 0);
            textPosComp->GetMsgRect()->y = 25;
        }
    }

    return true;
}

void Engine::FriendButtonComponent::Activate(System* pSystem)
{
    if (m_hovering)
    {
        TextComponent* textComp = static_cast<TextComponent*>(this->GetOwner()->GetComponent("TextComponent"));
        std::cout << textComp->GetToken() << std::endl;
    }
}

void Engine::FriendButtonComponent::ScrollUp(System* pSystem)
{
    if (!m_moveUp && !m_moveDown)
    {
        m_moveUp = true;
        m_firendList->UpdateIndex(1);
    }
}

void Engine::FriendButtonComponent::ScrollDown(System* pSystem)
{
    if (!m_moveUp && !m_moveDown)
    {
        m_moveDown = true;
        m_firendList->UpdateIndex(-1);
    }
}

void Engine::FriendButtonComponent::Drag(System* pSystem, int mouseY)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    TextComponent* textPosComp = dynamic_cast<TextComponent*>(GetOwner()->GetComponent("TextComponent"));

    int prevY;
    if (m_oldY == 0)
        prevY = mouseY;
    else
        prevY = m_oldY;

    int diff = abs(prevY - y);
    if (prevY > y)
    {
        posComp->SetXY(posComp->GetX(), posComp->GetY() - diff);
        textPosComp->GetMsgRect()->y = textPosComp->GetMsgRect()->y - diff;

    }
    else if (prevY < y)
    {
        posComp->SetXY(posComp->GetX(), posComp->GetY() + diff);
        textPosComp->GetMsgRect()->y = textPosComp->GetMsgRect()->y + diff;

    }
    m_oldY = y;

    if (posComp->GetY() <= -96)
    {
        double offset = posComp->GetY() + 96.0;
        posComp->SetXY(posComp->GetX(), 672 + offset);
        textPosComp->GetMsgRect()->y = 697 + offset;
        m_firendList->UpdateIndex(1);

    }
    else if (posComp->GetY() >= 768)
    {
        double offset = posComp->GetY() - 768.0;
        posComp->SetXY(posComp->GetX(), 0 + offset);
        textPosComp->GetMsgRect()->y = 25 + offset;
        m_firendList->UpdateIndex(-1);
    }
}
