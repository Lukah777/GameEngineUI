#include "CalcButtonComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <SDL.h>
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "CalculatorComponent.h"

Engine::CalcButtonComponent::CalcButtonComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::CalcButtonComponent::Update(System* pSystem)
{
    if (m_buttonSymbol == ' ')
        m_buttonSymbol = dynamic_cast<TextComponent*>(pSystem->FindGameObject(GetOwner()->GetName())->GetComponent("TextComponent"))->GetToken()[0];

    if (m_calcComp == nullptr)
    {
        for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
        {
            GameObject* pObject = nullptr;
            pObject = pSystem->GetGameObjectAt(i);
            if (pObject == nullptr)
                break;
            if (!pObject->GetEnabled())
                continue;

            for (int j = 0; j < pObject->GetGameObjectSize(); j++)
            {
                GameObject* pChildObject = nullptr;
                pChildObject = pObject->GetGameObjectAt(j);
                if (pChildObject == nullptr)
                    break;
                if (!pChildObject->GetEnabled())
                    continue;

                if (pChildObject->GetComponent("CalculatorComponent") != nullptr)
                    m_calcComp = dynamic_cast<CalculatorComponent*>(pChildObject->GetComponent("CalculatorComponent"));
            }
        }
    }

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

void Engine::CalcButtonComponent::Activate(System* pSystem)
{
    if (m_hovering)
    {
        m_calcComp->Calculate(m_buttonSymbol);
    }
}
