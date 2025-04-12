#include "EquipButtonComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "HeadSlotComponent.h"
#include "BodySlotComponent.h"
#include <SDL.h>
#include "PositionComponent.h"

Engine::EquipButtonComponent::EquipButtonComponent(System* pSystem, GameObject* pGameObject, const char* file, int slot, std::string NavGameObjectStr, GameObject* pSelfGameObject, int height, int yOffest)
    :Component(pSystem, pGameObject)
{
    m_navGameObjectStr = NavGameObjectStr;
    m_selfGameObject = pSelfGameObject;
    

    ResourceSystem* pResources = pSystem->GetResources();
    Graphics* pGraphics = pSystem->GetGraphics();
    m_name = file;
    m_slot = slot;
    if (file != nullptr)
    {
        m_pImage = pResources->GetImageData(file, pGraphics->GetRender());
        m_color.r = 255;
        m_color.g = 255;
        m_color.b = 255;
    }

    if (height == 0)
        m_height = m_pImage->GetH();
    else
        m_height = height;

    m_yOffset = yOffest;

    
}

bool Engine::EquipButtonComponent::Update(System* pSystem)
{
    if (m_navGameObject == nullptr && m_navGameObjectStr != "")
        m_navGameObject = pSystem->FindGameObject(m_navGameObjectStr);

    int x, y;
    SDL_GetMouseState(&x, &y);
    ImageComponent* imgComp = dynamic_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"));
    PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    if (m_ogColor.r == 0 && m_ogColor.g == 0 && m_ogColor.b == 0)
        m_ogColor = imgComp->GetColor();

    if (x > posComp->GetX() && x < posComp->GetX() + imgComp->GetImage()->GetW()
        && y > posComp->GetY() + m_yOffset && y < posComp->GetY() + m_yOffset + m_height)
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

void Engine::EquipButtonComponent::Activate(System* pSystem)
{
    if (m_hovering)
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

                if (pChildObject->GetName() == "Hero")
                {
                    if (m_slot == 0)
                    {
                        ImageComponent* pHeroImageComp = dynamic_cast<ImageComponent*>(pChildObject->GetComponent("ImageComponent"));
                        pHeroImageComp->SetImage(m_pImage);
                    }
                    else if (m_slot == 1)
                    {
                        HeadSlotComponent* pHeadSlotComp = dynamic_cast<HeadSlotComponent*>(pChildObject->GetComponent("HeadSlotComponent"));
                        if (pHeadSlotComp->GetImage() == m_pImage)
                        {
                            pHeadSlotComp->SetImage(pHeadSlotComp->GetOldImage());
                        }
                        else
                        {
                            pHeadSlotComp->SetImage(m_pImage);
                        }
                    }
                    else if (m_slot == 2)
                    {
                        BodySlotComponent* pBodySlotComp = dynamic_cast<BodySlotComponent*>(pChildObject->GetComponent("BodySlotComponent"));
                        if (pBodySlotComp->GetImage() == m_pImage)
                        {
                            pBodySlotComp->SetImage(pBodySlotComp->GetOldImage());
                        }
                        else
                        {
                            pBodySlotComp->SetImage(m_pImage);
                        }
                    }
                }
            }
        }
        if (m_navGameObjectStr != "")
        {
            m_navGameObject->ToggleEnabled();
            m_selfGameObject->ToggleEnabled();
        }
        m_hovering = false;
    }
}
