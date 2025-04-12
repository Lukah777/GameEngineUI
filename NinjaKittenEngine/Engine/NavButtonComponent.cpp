#include "NavButtonComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "PositionComponent.h"
#include "SDL.h"
#include "InputFieldComponent.h"
#include "SoundComponent.h"
#include "TextComponent.h"
#include "EditButtonComponent.h"

Engine::NavButtonComponent::NavButtonComponent(System* pSystem, GameObject* pGameObject, std::string NavGameObjectStr, GameObject* pSelfGameObject)
    :Component(pSystem, pGameObject)
{
    m_navGameObjectStr = NavGameObjectStr;
    m_selfGameObject = pSelfGameObject;
}

bool Engine::NavButtonComponent::Update(System* pSystem)
{

    if (m_navGameObject == nullptr )
        m_navGameObject = pSystem->FindGameObject(m_navGameObjectStr);

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

void Engine::NavButtonComponent::Activate(System* pSystem)
{
    if (m_hovering)
    {
        SoundComponent* voiceOver = nullptr;
        bool found = false;
        for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
        {
            for (int j = 0; j < pSystem->GetGameObjectAt(i)->GetGameObjectSize(); j++)
            {
                if (pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("InputFieldComponent") != nullptr)
                {
                    if (m_navGameObjectStr == "MainMenu")
                    {
                        InputFieldComponent* inputFieldComp = dynamic_cast<InputFieldComponent*>(pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("InputFieldComponent"));
                        if (inputFieldComp != nullptr)
                            std::cout << inputFieldComp->GetInputStr() << std::endl;
                        found = true;
                        break;
                    }
                }
                if (pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetName() == "VoiceSlider")
                {
                    voiceOver = dynamic_cast<SoundComponent*>(pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("SoundComponent"));
                }
            }
        }

        if (m_navGameObjectStr == "Quit")
            m_quit = true;
        else
        {
            if (m_navGameObjectStr == "Game")
                voiceOver->PlaySound();
            m_navGameObject->ToggleEnabled();
            m_selfGameObject->ToggleEnabled();
        }
        m_hovering = false;
    }
}

bool Engine::NavButtonComponent::Drag(System* pSystem, int mouseX, int mouseY)
{
    if (m_hovering || (m_oldX != 0 && m_oldY != 0))
    {
        if (pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent") != nullptr)
        {
            if (dynamic_cast<EditButtonComponent*>(pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent"))->GetOn() == true)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
                TextComponent* textPosComp = dynamic_cast<TextComponent*>(GetOwner()->GetComponent("TextComponent"));

                int prevX;
                if (m_oldX == 0)
                    prevX = mouseX;
                else
                    prevX = m_oldX;

                int prevY;
                if (m_oldY == 0)
                    prevY = mouseY;
                else
                    prevY = m_oldY;

                int diffX = abs(prevX - x);
                if (prevX > x)
                {
                    posComp->SetXY(posComp->GetX() - diffX, posComp->GetY());
                    if (textPosComp != nullptr)
                        textPosComp->GetMsgRect()->x = textPosComp->GetMsgRect()->x - diffX;

                }
                else if (prevX < x)
                {
                    posComp->SetXY(posComp->GetX() + diffX, posComp->GetY());
                    if (textPosComp != nullptr)
                        textPosComp->GetMsgRect()->x = textPosComp->GetMsgRect()->x + diffX;

                }

                int diffY = abs(prevY - y);
                if (prevY > y)
                {
                    posComp->SetXY(posComp->GetX(), posComp->GetY() - diffY);
                    if (textPosComp != nullptr)
                        textPosComp->GetMsgRect()->y = textPosComp->GetMsgRect()->y - diffY;

                }
                else if (prevY < y)
                {
                    posComp->SetXY(posComp->GetX(), posComp->GetY() + diffY);
                    if (textPosComp != nullptr)
                        textPosComp->GetMsgRect()->y = textPosComp->GetMsgRect()->y + diffY;

                }

                m_oldX = x;
                m_oldY = y;
                return true;
            }
        }
    }
    return false;
}