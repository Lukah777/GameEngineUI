#include "TranslationButtonComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"
#include "TextComponent.h"
#include "NavButtonComponent.h"

Engine::TranslationButtonComponent::TranslationButtonComponent(System* pSystem, GameObject* pGameObject, std::string language, std::string NavGameObjectStr, GameObject* pSelfGameObject)
    :Component(pSystem, pGameObject)
{
    if (language == "English")
        m_newLanguage = English;
    else if (language == "French")
        m_newLanguage = French;
    else if (language == "Italian")
        m_newLanguage = Italian;
    else if (language == "German")
        m_newLanguage = German;
    else if (language == "Spanish")
        m_newLanguage = Spanish;
    else 
        m_newLanguage = English;

    m_navGameObjectStr = NavGameObjectStr;
    m_selfGameObject = pSelfGameObject;
}

bool Engine::TranslationButtonComponent::Update(System* pSystem)
{
    if (m_navGameObject == nullptr)
        m_navGameObject = pSystem->FindGameObject(m_navGameObjectStr);

    int x, y;
    SDL_GetMouseState(&x, &y);
    ImageComponent* imgComp = dynamic_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"));
    PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

    if (x > posComp->GetX() && x < posComp->GetX() + imgComp->GetImage()->GetW()
        && y > posComp->GetY() && y < posComp->GetY() + imgComp->GetImage()->GetH())
    {
        m_hovering = true;
    }
    else
    {
        m_hovering = false;
    }
    return true;
}

void Engine::TranslationButtonComponent::Activate(System* pSystem)
{
    if (m_hovering)
    {
        pSystem->GetResources()->SetTranslation(m_newLanguage);
        m_navGameObject->ToggleEnabled();
        m_selfGameObject->ToggleEnabled();
        m_hovering = false;
        for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
        {
            for (int j = 0; j < pSystem->GetGameObjectAt(i)->GetGameObjectSize(); j++)
            {
                if (pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("TextComponent") != nullptr)
                {
                    TextComponent* txtComp = dynamic_cast<TextComponent*>(pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("TextComponent"));
                    txtComp->ReloadText(pSystem);
                }
            }
        }
    }
}