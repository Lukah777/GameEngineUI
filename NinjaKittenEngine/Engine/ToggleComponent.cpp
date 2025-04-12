#include "ToggleComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"

Engine::ToggleComponent::ToggleComponent(System* pSystem, GameObject* pGameObject, bool on, std::string gameObjectStr)
    :Component(pSystem, pGameObject)
{
    m_on = on;
    m_gameObjectStr = gameObjectStr;
}

bool Engine::ToggleComponent::Update(System* pSystem)
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


    

    return true;
}

void Engine::ToggleComponent::Activate()
{
    if (m_hovering)
    {
        PositionComponent* knobPosComp = dynamic_cast<PositionComponent*>(m_pGameObject->GetComponent("PositionComponent"));

        if (m_on)
        {
            m_on = false;
            knobPosComp->SetXY(knobPosComp->GetX() + 93, knobPosComp->GetY());

        }
        else
        {
            m_on = true;
            knobPosComp->SetXY(knobPosComp->GetX() - 93, knobPosComp->GetY());
        }
    }
}