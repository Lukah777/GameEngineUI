#include "RadioButtonComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"

Engine::RadioButtonComponent::RadioButtonComponent(System* pSystem, GameObject* pGameObject, bool on, std::string gameObjectStr)
    :Component(pSystem, pGameObject)
{
    m_on = on;
    m_gameObjectStr = gameObjectStr;
}

bool Engine::RadioButtonComponent::Update(System* pSystem)
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

void Engine::RadioButtonComponent::Activate(System* pSystem)
{
    if (m_hovering)
    {
        if (!m_on)
        {
            m_on = true;
        }

        //
        for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
        {
            GameObject* pObject = nullptr;
            pObject = pSystem->GetGameObjectAt(i);
            if (pObject == nullptr)
                break;

            for (int j = 0; j < pObject->GetGameObjectSize(); j++)
            {
                GameObject* pChildObject = nullptr;
                pChildObject = pObject->GetGameObjectAt(j);
                if (pChildObject == nullptr)
                    break;

                if (pChildObject->GetComponent("RadioButtonComponent") != nullptr)
                {
                    RadioButtonComponent* pButtonComp = static_cast<RadioButtonComponent*>(pChildObject->GetComponent("RadioButtonComponent"));

                    if (pButtonComp != this)
                    {
                        pButtonComp->SetOn(!m_on);
                    }
                }
            }
        }
    }
}