#include "AIComponent.h"
#include "HeroComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "ImageComponent.h"
#include "SDL.h"
#include "CollisionComponent.h"
#include "EnemyBulletComponent.h"
#include <string.h> 
#include <random>

Engine::AIComponent::AIComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
}

bool Engine::AIComponent::Update(Engine::System* pSystem)
{
    double moveSpeed = 1;
    double VelX = 0;
    double VelY = 0;

    PositionComponent* pOwnerPosComp = static_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    PositionComponent* pTargetPosComp = nullptr;

    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = pSystem->GetGameObjectAt(i);
        if (pObject == nullptr || !pObject->GetEnabled())
            continue;
        for (int j = 0; j < pObject->GetGameObjectSize(); j++)
        {
            GameObject* pChildObject = nullptr;
            pChildObject = pObject->GetGameObjectAt(j);
            if (pChildObject == nullptr )
                break;
            HeroComponent* pHeroComp = static_cast<HeroComponent*>(pChildObject->GetComponent("HeroComponent"));

            if (pHeroComp == nullptr)
                continue;

            pTargetPosComp = static_cast<PositionComponent*>(pChildObject->GetComponent("PositionComponent"));


            //
            if (pOwnerPosComp->GetX() < pTargetPosComp->GetX())
            {
                VelX = moveSpeed;
            }
            else if (pOwnerPosComp->GetX() > pTargetPosComp->GetX())
            {
                VelX = -moveSpeed;
            }
            else
            {
                VelX = 0;
            }

            if (pOwnerPosComp->GetY() < pTargetPosComp->GetY())
            {
                VelY = moveSpeed;
            }
            else if (pOwnerPosComp->GetY() > pTargetPosComp->GetY())
            {
                VelY = -moveSpeed;
            }
            else
            {
                VelY = 0;
            }

            dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, VelX, VelY);


            int ownerX = (int)pOwnerPosComp->GetX();
            int ownerY = (int)pOwnerPosComp->GetY();

            SDL_Rect OwnerRect;
            Image* pOwnerImg = static_cast<ImageComponent*>(GetOwner()->GetComponent("ImageComponent"))->GetImage();
            OwnerRect.x = ownerX;
            OwnerRect.y = ownerY;
            OwnerRect.w = pOwnerImg->GetW();
            OwnerRect.h = pOwnerImg->GetH();

            for (int j = 0; j < pSystem->GetGameObjectSize(); j++)
            {
                GameObject* pObjectNew = nullptr;
                pObjectNew = pSystem->GetGameObjectAt(j);
                    for (int j = 0; j < pObjectNew->GetGameObjectSize(); j++)
                    {
                        GameObject* pChildObjectNew = nullptr;
                        pChildObjectNew = pObjectNew->GetGameObjectAt(j);
                        if (pChildObjectNew == nullptr)
                            break;;
                        CollisionComponent* pOtherCollisionComp = static_cast<CollisionComponent*>(pChildObjectNew->GetComponent("CollisionComponent"));
                        if (pChildObjectNew == nullptr)
                            break;

                        if (pOtherCollisionComp != nullptr && pChildObjectNew != GetOwner() && pChildObjectNew->GetComponent("CollisionComponent") != nullptr)
                        {
                            SDL_Rect ObjectRect;
                            PositionComponent* pObjectPosComp = static_cast<PositionComponent*>(pChildObjectNew->GetComponent("PositionComponent"));
                            Image* pObjectImg = static_cast<ImageComponent*>(pChildObjectNew->GetComponent("ImageComponent"))->GetImage();
                            ObjectRect.x = (int)pObjectPosComp->GetX();
                            ObjectRect.y = (int)pObjectPosComp->GetY();
                            ObjectRect.w = pObjectImg->GetW();
                            ObjectRect.h = pObjectImg->GetH();


                            if (SDL_HasIntersection(&ObjectRect, &OwnerRect) == SDL_TRUE)
                            {
                                dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"))->ApplyVelocity(pSystem, -VelX, -VelY);
                                VelX = 0;
                                VelY = 0;

                                m_pObjectHeroComp = static_cast<HeroComponent*>(pChildObjectNew->GetComponent("HeroComponent"));
                                if (m_pObjectHeroComp !=  nullptr)
                                {
                                    m_pObjectHeroComp->UpdateHealth(pSystem, -10);
                                    std::srand(time(NULL));
                                    int x, y;
                                    if (rand() % 2 > 0)
                                    {
                                        x = (rand()% 100) - 131;
                                    }
                                    else
                                    {
                                        x = (rand()% 100) + 1024;
                                    }
                                    if (rand() % 2 > 0)
                                    {
                                        y = (rand() % 100) - 178;
                                    }
                                    else
                                    {
                                        y = (rand() % 100) + 769;
                                    }
                                   
                                    pOwnerPosComp->SetXY(x, y);
                                }
                                break;
                            }
                        }
                    }
            }
        }
    }

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

void Engine::AIComponent::Activate(System* pSystem)
{
    if (m_pObjectHeroComp == nullptr || m_pSoundComp == nullptr)
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

                if (pChildObject->GetComponent("HeroComponent") !=  nullptr)
                {
                    m_pObjectHeroComp = static_cast<HeroComponent*>(pChildObject->GetComponent("HeroComponent"));
                }
                if (pChildObject->GetName() == "SFXSlider")
                {
                    if (pChildObject->GetComponent("SoundComponent") != nullptr)
                        m_pSoundComp = static_cast<SoundComponent*>(pChildObject->GetComponent("SoundComponent"));
                }
            }
        }
    }

    if (m_hovering)
    {
        PositionComponent* posComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));

        std::srand(time(NULL));
        int x, y;
        if (rand() % 2 > 0)
        {
            x = (rand() % 100) - 131;
        }
        else
        {
            x = (rand() % 100) + 1024;
        }
        if (rand() % 2 > 0)
        {
            y = (rand() % 100) - 178;
        }
        else
        {
            y = (rand() % 100) + 769;
        }

        posComp->SetXY(x, y);
        m_pSoundComp->PlaySound();
        m_pObjectHeroComp->UpdateMoney(pSystem, 250);
    }
}