#include "Input.h"
#include <SDL.h>
#include "GameObject.h"
#include "NavButtonComponent.h"
#include "TranslationButtonComponent.h"
#include "CheckboxComponent.h"
#include "ToggleComponent.h"
#include "RadioButtonComponent.h"
#include "SliderComponent.h"
#include "System.h"
#include "AIComponent.h"
#include "PositionComponent.h"
#include "EquipButtonComponent.h"
#include "FriendButtonComponent.h"
#include "CalcButtonComponent.h"
#include "EditButtonComponent.h"
#include "TextComponent.h"
#include "../TinyXML/tinyxml2.h"


bool Engine::Input::GetIsKeyDown(int key)
{
    int Length;
    const Uint8* KeyboardState = SDL_GetKeyboardState(&Length);

    if (KeyboardState[key])
    {
        return true;
    }
    
    return false;
}

bool Engine::Input::Click(Engine::System* pSystem)
{
   
    GameObject* pHeroObject = nullptr;
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

            if (dynamic_cast<EditButtonComponent*>(pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent"))->GetOn() == false)
            {
                if (pChildObject->GetComponent("NavButtonComponent") != nullptr)
                {
                    NavButtonComponent* pButtonComp = static_cast<NavButtonComponent*>(pChildObject->GetComponent("NavButtonComponent"));

                    if (pButtonComp != nullptr)
                    {
                        pButtonComp->Activate(pSystem);
                        if (pButtonComp->GetQuit())
                            return false;
                    }
                }
                else if (pChildObject->GetComponent("TranslationButtonComponent") != nullptr)
                {
                    TranslationButtonComponent* pButtonComp = static_cast<TranslationButtonComponent*>(pChildObject->GetComponent("TranslationButtonComponent"));

                    if (pButtonComp != nullptr)
                    {
                        pButtonComp->Activate(pSystem);
                    }
                }
                else if (pChildObject->GetComponent("CheckboxComponent") != nullptr)
                {
                    CheckboxComponent* pButtonComp = static_cast<CheckboxComponent*>(pChildObject->GetComponent("CheckboxComponent"));

                    if (pButtonComp != nullptr)
                    {
                        pButtonComp->Activate();
                    }
                }
                else if (pChildObject->GetComponent("ToggleComponent") != nullptr)
                {
                    ToggleComponent* pButtonComp = static_cast<ToggleComponent*>(pChildObject->GetComponent("ToggleComponent"));

                    if (pButtonComp != nullptr)
                    {
                        pButtonComp->Activate();
                    }
                }
                else if (pChildObject->GetComponent("RadioButtonComponent") != nullptr)
                {
                    RadioButtonComponent* pButtonComp = static_cast<RadioButtonComponent*>(pChildObject->GetComponent("RadioButtonComponent"));

                    if (pButtonComp != nullptr)
                    {
                        pButtonComp->Activate(pSystem);
                    }
                }
                else if (pChildObject->GetComponent("SliderComponent") != nullptr)
                {
                    SliderComponent* pButtonComp = static_cast<SliderComponent*>(pChildObject->GetComponent("SliderComponent"));

                    if (pButtonComp != nullptr)
                    {
                        pButtonComp->Activate();
                    }
                }
                else if (pChildObject->GetComponent("AIComponent") != nullptr)
                {
                    AIComponent* pButtonComp = static_cast<AIComponent*>(pChildObject->GetComponent("AIComponent"));

                    if (pButtonComp != nullptr && pHeroObject->GetEnabled())
                    {
                        pButtonComp->Activate(pSystem);
                    }
                }
                else if (pChildObject->GetComponent("HeroComponent") != nullptr)
                {
                    pHeroObject = pChildObject;
                }
                else if (pChildObject->GetComponent("EquipButtonComponent") != nullptr)
                {
                    EquipButtonComponent* pEquipButtonComp = static_cast<EquipButtonComponent*>(pChildObject->GetComponent("EquipButtonComponent"));

                    if (pEquipButtonComp != nullptr)
                    {
                        pEquipButtonComp->Activate(pSystem);
                    }
                }
                else if (pChildObject->GetComponent("FriendButtonComponent") != nullptr)
                {
                    FriendButtonComponent* pFriendButtonComp = static_cast<FriendButtonComponent*>(pChildObject->GetComponent("FriendButtonComponent"));

                    if (pFriendButtonComp != nullptr)
                    {
                        pFriendButtonComp->Activate(pSystem);
                    }
                }
                else if (pChildObject->GetComponent("CalcButtonComponent") != nullptr)
                {
                    CalcButtonComponent* pCalcButtonComp = static_cast<CalcButtonComponent*>(pChildObject->GetComponent("CalcButtonComponent"));

                    if (pCalcButtonComp != nullptr)
                    {
                        pCalcButtonComp->Activate(pSystem);
                    }
                }
            }
            if (pChildObject->GetComponent("EditButtonComponent") != nullptr)
            {
                EditButtonComponent* pEditButtonComp = static_cast<EditButtonComponent*>(pChildObject->GetComponent("EditButtonComponent"));

                if (pEditButtonComp != nullptr)
                {
                    pEditButtonComp->Activate();
                }
            }
        }
    }
    return true;
}

bool Engine::Input::Drag(Engine::System* pSystem)
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

            bool textDrag = false;
            bool buttonDrag = false;

            if (pChildObject->GetComponent("FriendButtonComponent") != nullptr)
            {
                FriendButtonComponent* pFriendButtonComp = static_cast<FriendButtonComponent*>(pChildObject->GetComponent("FriendButtonComponent"));

                if (pFriendButtonComp != nullptr)
                {
                    pFriendButtonComp->Drag(pSystem, m_mouseY);
                }
            }
            if (pChildObject->GetComponent("TextComponent") != nullptr)
            {
                TextComponent* pTextComp = static_cast<TextComponent*>(pChildObject->GetComponent("TextComponent"));

                if (pTextComp != nullptr)
                {
                    textDrag = pTextComp->Drag(pSystem, m_mouseX, m_mouseY);
                    
                }
            }
            if (pChildObject->GetComponent("NavButtonComponent") != nullptr)
            {
                NavButtonComponent* pButtonComp = static_cast<NavButtonComponent*>(pChildObject->GetComponent("NavButtonComponent"));

                if (pButtonComp != nullptr)
                {
                    if (!textDrag)
                        buttonDrag = pButtonComp->Drag(pSystem, m_mouseX, m_mouseY);
                }
            }
            if (textDrag || buttonDrag)
            {
                return true;
            }
        }
    }

    return true;
}

bool Engine::Input::Update(Engine::System* pSystem)
{
    SDL_Event event;       
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent") != nullptr)
            {
                if (dynamic_cast<EditButtonComponent*>(pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent"))->GetOn() == true)
                {
                    if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)
                    {
                        m_control = true;
                    }
                    if (m_control)
                    {
                        if (event.key.keysym.sym == SDLK_t)
                        {
                            for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
                            {
                                if (pSystem->GetGameObjectAt(i)->GetName() == "TitleMenu" || pSystem->GetGameObjectAt(i)->GetName() == "MenuTool")
                                    pSystem->GetGameObjectAt(i)->SetEnabled(true);
                                else
                                    pSystem->GetGameObjectAt(i)->SetEnabled(false);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_m)
                        {
                            for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
                            {
                                if (pSystem->GetGameObjectAt(i)->GetName() == "MainMenu" || pSystem->GetGameObjectAt(i)->GetName() == "MenuTool")
                                    pSystem->GetGameObjectAt(i)->SetEnabled(true);
                                else
                                    pSystem->GetGameObjectAt(i)->SetEnabled(false);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_o)
                        {
                            for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
                            {
                                if (pSystem->GetGameObjectAt(i)->GetName() == "OptionsMenu" || pSystem->GetGameObjectAt(i)->GetName() == "MenuTool")
                                    pSystem->GetGameObjectAt(i)->SetEnabled(true);
                                else
                                    pSystem->GetGameObjectAt(i)->SetEnabled(false);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_s)
                        {
                            std::string file;
#if NDEBUG
                            file = "../Assets/Scribblenauts.xml"));
#else
                           file = "../NinjaKittenEngine/Assets/Scribblenauts.xml";
#endif
                            using namespace tinyxml2;
                            XMLDocument doc;
                            doc.LoadFile(file.c_str());
                            tinyxml2::XMLElement* entryTag = doc.FirstChildElement();

                            while (entryTag != NULL)
                            {
                                std::string name = entryTag->Name();
                                if (name != "GameObject")
                                {
                                    entryTag = entryTag->NextSiblingElement();
                                    continue;
                                }
                                std::string objectName = entryTag->Attribute("Name");

                                bool enabled = true;
                                std::string enabledString = (entryTag->Attribute("Enabled"));
                                if (enabledString == "false")
                                    enabled = false;

                                tinyxml2::XMLElement* childTag = entryTag->FirstChildElement();
                                while (childTag != NULL)
                                {
                                    GameObject* pGameObjectBack = pSystem->GetBackGameObject();
                                    std::string name = childTag->Name();
                                    if (name != "GameObject")
                                    {
                                        childTag = childTag->NextSiblingElement();
                                        continue;
                                    }
                                    std::string childobjectName = childTag->Attribute("Name");

                                    bool enabled = true;
                                    std::string enabledString = (childTag->Attribute("Enabled"));
                                    if (enabledString == "false")
                                        enabled = false;
  
                                    tinyxml2::XMLElement* componentTag = childTag->FirstChildElement();

                                    while (componentTag != NULL)
                                    {
                                        GameObject* pGameObjectChildBack = pGameObjectBack->GetBackGameObject();
                                        std::string componentName = componentTag->Attribute("Name");

                                        if (componentName == "PositionComponent")
                                        {
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
                                                    
                                                    if (childobjectName == pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetName())
                                                    {
                                                        Engine::PositionComponent* posComp = dynamic_cast<PositionComponent*>(pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("PositionComponent"));
                                                        if (posComp != nullptr)
                                                        {
                                                            if (componentTag->FirstChildElement("X") != nullptr)
                                                            {
                                                                componentTag->FirstChildElement("X")->SetText(posComp->GetX());
                                                            }
                                                            if (componentTag->FirstChildElement("Y") != nullptr)
                                                            {
                                                                componentTag->FirstChildElement("Y")->SetText(posComp->GetY());
                                                            }
                                                        }
                                                    }
                                                }                                            
                                            } 
                                        }
                                        
                                        if (componentName == "TextComponent")
                                        {
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

                                                    if (childobjectName == pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetName())
                                                    {
                                                        Engine::TextComponent* textComp = dynamic_cast<TextComponent*>(pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("TextComponent"));
                                                        if (textComp != nullptr)
                                                        {
                                                            if (componentTag->FirstChildElement("X") != nullptr)
                                                            {
                                                                componentTag->FirstChildElement("X")->SetText(textComp->GetMsgRect()->x);
                                                            }
                                                            if (componentTag->FirstChildElement("Y") != nullptr)
                                                            {
                                                                componentTag->FirstChildElement("Y")->SetText(textComp->GetMsgRect()->y);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        componentTag = componentTag->NextSiblingElement();
                                    }
                                    childTag = childTag->NextSiblingElement();
                                }
                                entryTag = entryTag->NextSiblingElement();
                            }
                            doc.SaveFile(file.c_str());
                        }
                    }
                }
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
                {
                    GameObject* pObject = nullptr;
                    pObject = pSystem->GetGameObjectAt(i);
                    if (pObject == nullptr)
                        break;

                    if (pObject->GetName() == "Game" && pObject->GetEnabled())
                    {
                        pObject->SetEnabled(false);

                        for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
                        {
                            GameObject* pObject2 = nullptr;
                            pObject2 = pSystem->GetGameObjectAt(i);
                            if (pObject2 == nullptr)
                                break;

                            if (pObject2->GetName() == "PauseMenu")
                            {
                                pObject2->SetEnabled(true);
                                return true;
                            }

                        }
                    }
                }
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)
            {
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

                        if (pChildObject->GetComponent("FriendButtonComponent") != nullptr)
                        {
                            FriendButtonComponent* pFriendButtonComp = static_cast<FriendButtonComponent*>(pChildObject->GetComponent("FriendButtonComponent"));

                            if (pFriendButtonComp != nullptr)
                            {
                                pFriendButtonComp->ScrollUp(pSystem);
                            }
                        }
                    }
                }
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
            {
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

                        if (pChildObject->GetComponent("FriendButtonComponent") != nullptr)
                        {
                            FriendButtonComponent* pFriendButtonComp = static_cast<FriendButtonComponent*>(pChildObject->GetComponent("FriendButtonComponent"));

                            if (pFriendButtonComp != nullptr)
                            {
                                pFriendButtonComp->ScrollDown(pSystem);
                            }
                        }
                    }
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            m_draging = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            m_draging = false;
            if (m_dragTimer < 2 && m_dragTimer > 0)
            {
                m_dragTimer = 0;
                bool cont = Click(pSystem);
                if (!cont)
                    return cont;
            }
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

                    if (pChildObject->GetComponent("FriendButtonComponent") != nullptr)
                    {
                        FriendButtonComponent* pFriendButtonComp = static_cast<FriendButtonComponent*>(pChildObject->GetComponent("FriendButtonComponent"));

                        if (pFriendButtonComp != nullptr)
                        {
                            pFriendButtonComp->SetOldY(0);
                        }
                    }
                    if (pChildObject->GetComponent("TextComponent") != nullptr)
                    {
                        TextComponent* pTextComp = static_cast<TextComponent*>(pChildObject->GetComponent("TextComponent"));

                        if (pTextComp != nullptr)
                        {
                            pTextComp->SetOldX(0);
                            pTextComp->SetOldY(0);
                        }
                    }
                    if (pChildObject->GetComponent("NavButtonComponent") != nullptr)
                    {
                        NavButtonComponent* pButtonComp = static_cast<NavButtonComponent*>(pChildObject->GetComponent("NavButtonComponent"));

                        if (pButtonComp != nullptr)
                        {
                            pButtonComp->SetOldX(0);
                            pButtonComp->SetOldY(0);
                        }
                    }
                    
                }
            }
        }

        if (event.type == SDL_KEYUP)
        {
            if (pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent") != nullptr)
            {
                if (dynamic_cast<EditButtonComponent*>(pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent"))->GetOn() == true)
                {
                    if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)
                    {
                        m_control = false;
                    }
                }
            }
        }

        if (m_draging)
        {
            SDL_GetMouseState(&m_mouseX, &m_mouseY);
            m_dragTimer++;
            if (m_dragTimer >= 5)
            {
                m_dragTimer = 0;
                bool cont = Drag(pSystem);
                if (!cont)
                    return cont;
            }
        }
    }
    return true;
}