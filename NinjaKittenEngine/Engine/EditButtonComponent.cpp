#include "EditButtonComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"

Engine::EditButtonComponent::EditButtonComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::EditButtonComponent::Update(System* pSystem)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    ImageComponent* imgComp = dynamic_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"));
    PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    if (m_ogColor.r == 0 && m_ogColor.g == 0 && m_ogColor.b == 0)
        m_ogColor = imgComp->GetColor();


    if (x > posComp->GetX() && x < posComp->GetX() + imgComp->GetImage()->GetW()
        && y > posComp->GetY() && y < posComp->GetY() + imgComp->GetImage()->GetH())
    {
        imgComp->SetColor(m_hoverColor);
        m_hovering = true;
    }
    else if (m_on)
    {
        imgComp->SetColor(m_onColor);
        m_hovering = false;
    }
    else
    {
        imgComp->SetColor(m_ogColor);
        m_hovering = false;
    }

    return true;
}

void Engine::EditButtonComponent::Activate()
{
    if (m_hovering)
    {
        if (m_on)
            m_on = false;
        else
            m_on = true;
    }
}
