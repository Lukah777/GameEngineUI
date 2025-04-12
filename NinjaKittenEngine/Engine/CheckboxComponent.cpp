#include "CheckboxComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"

Engine::CheckboxComponent::CheckboxComponent(System* pSystem, GameObject* pGameObject, bool on, std::string gameObjectStr)
    :Component(pSystem, pGameObject)
{
    m_on = on;
    m_gameObjectStr = gameObjectStr;
}

bool Engine::CheckboxComponent::Update(System* pSystem)
{
    if (m_pGameObject == nullptr)
        m_pGameObject = pSystem->FindGameObject(m_gameObjectStr);

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
    else
    {
        imgComp->SetColor(m_ogColor);
        m_hovering = false;
    }

    m_pGameObject->SetEnabled(m_on);

    return true;
}

void Engine::CheckboxComponent::Activate()
{
    if (m_hovering)
    {
        if (m_on)
            m_on = false;
        else
            m_on = true;
    }
}