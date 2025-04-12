#include "SliderComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"

Engine::SliderComponent::SliderComponent(System* pSystem, GameObject* pGameObject, int val, std::string gameObjectStr)
    :Component(pSystem, pGameObject)
{
    m_value = val;
    m_gameObjectStr = gameObjectStr;
}

bool Engine::SliderComponent::Update(System* pSystem)
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

    ImageComponent* sliderImgComp = dynamic_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"));
    PositionComponent* sliderPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

    ImageComponent* knobImgComp = dynamic_cast<ImageComponent*>(m_pGameObject->GetComponent("ImageComponent"));
    PositionComponent* knobPosComp = dynamic_cast<PositionComponent*>(m_pGameObject->GetComponent("PositionComponent"));

    m_value = ((knobPosComp->GetX() - sliderPosComp->GetX() + (knobImgComp->GetImage()->GetW() / 2)) / sliderImgComp->GetImage()->GetW()) * 100;

    return true;
}

void Engine::SliderComponent::Activate()
{
    if (m_hovering)
    {
        ImageComponent* sliderImgComp = dynamic_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"));
        PositionComponent* sliderPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

        ImageComponent* knobImgComp = dynamic_cast<ImageComponent*>(m_pGameObject->GetComponent("ImageComponent"));
        PositionComponent* knobPosComp = dynamic_cast<PositionComponent*>(m_pGameObject->GetComponent("PositionComponent"));

        int x, y;
        SDL_GetMouseState(&x, &y);
        knobPosComp->SetXY(x, knobPosComp->GetY());

        m_value = ((knobPosComp->GetX() - sliderPosComp->GetX() + (knobImgComp->GetImage()->GetW() / 2)) / sliderImgComp->GetImage()->GetW()) * 100;


    }
}