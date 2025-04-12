#include "HeroComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "TextComponent.h"
#include "ImageComponent.h"
#include "CheckboxComponent.h"
#include "ToggleComponent.h"
#include "RadioButtonComponent.h"

Engine::HeroComponent::HeroComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
    m_pSystem = pSystem;
}

void Engine::HeroComponent::HandleMessage(Engine::Message msg)
{
    if (msg.m_pRecipiant == GetOwner())
    {
        if (msg.m_msg == (const char*)"Collision" && msg.m_pSender->GetComponent("EnemyComponent") != nullptr)       //Check if Enemy
        {
            GetMessageSys()->SendMsg("Destroy", GetOwner(), GetOwner());
        }

        if (msg.m_msg == (const char*)"Collision")
        {
            PhysicsComponent* pPhysComp = dynamic_cast<PhysicsComponent*>(GetOwner()->GetComponent("PhysicsComponent"));
            PositionComponent* pPosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
            double oldAngle = pPosComp->GetOldAngle();
            pPosComp->SetAngle(oldAngle);

            if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_W_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, 2);
            }
            else if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_A_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, 2, 0);
            }
            else if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_S_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, -2);
            }
            else if (m_pSystem->GetInput()->GetIsKeyDown(m_pSystem->GetInput()->ENGINE_D_KEY))
            {
                pPhysComp->ApplyVelocity(m_pSystem, -2, 0);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 0.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, 1, 0);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 90.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, 1);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 180.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, -1, 0);
            }
            if (dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"))->GetAngle() == 270.0)
            {
                pPhysComp->ApplyVelocity(m_pSystem, 0, -1);
            }
        }
    }
}

void Engine::HeroComponent::UpdateHealth(System* pSystem, int change)
{
    if (m_health + change > 100)
        m_health == 100;
    else if (m_health + change < 0)
    {
        m_health = 0;
    }
    else
    {
        m_health += change;
    }

    if (m_pHealthBar == nullptr)
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

                if (pChildObject->GetName() == "HealthBar")
                {
                    m_pHealthBar = pChildObject;
                }
            }
        }
    }
    
    bool respawn = !dynamic_cast<ToggleComponent*>(m_pToggleRespawns->GetComponent("ToggleComponent"))->GetOn();
    
    if (m_health <= 0 && respawn)
    {
        m_health = 100;
    }
    else if (m_health <= 0 && !respawn)
    {
        GetOwner()->SetEnabled(false);
        for(GameObject* enemy : m_pEnemies)
        {
            PositionComponent* posComp = dynamic_cast<PositionComponent*>(enemy->GetComponent("PositionComponent"));

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
        }
    }
    else
    {
        GetOwner()->SetEnabled(true);
    }

    TextComponent* pHealthTextComp = static_cast<TextComponent*>(m_pHealthBar->GetComponent("TextComponent"));
    ImageComponent* pHealthImageComp = static_cast<ImageComponent*>(m_pHealthBar->GetComponent("ImageComponent"));
    PositionComponent* pHealthPosComp = static_cast<PositionComponent*>(m_pHealthBar->GetComponent("PositionComponent"));

    std::string healthStr = std::to_string(m_health);
    double curHealthW = (double)m_health/100.0 * pHealthImageComp->GetImage()->GetW();

    pHealthTextComp->ReloadText(pSystem, healthStr.c_str());
    pHealthImageComp->SetClip(pHealthPosComp->GetX(), pHealthPosComp->GetY(), curHealthW, pHealthImageComp->GetImage()->GetH());

    return;
}

void Engine::HeroComponent::UpdateMoney(System* pSystem, int change)
{
    TextComponent* pMoneyTextComp = static_cast<TextComponent*>(m_pMoneyCount->GetComponent("TextComponent"));

    m_money += change;
    std::string moneyStr = std::to_string(m_money);
    pMoneyTextComp->ReloadText(pSystem, moneyStr.c_str());
    return;
}

bool Engine::HeroComponent::Update(Engine::System* pSystem)
{
    if (m_pHint == nullptr || m_pEnemies.size() < 7)
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

                if (pChildObject->GetName() == "Hint")
                {
                    m_pHint = pChildObject;
                }
                if (pChildObject->GetComponent("EnemyComponent"))
                {
                    m_pEnemies.emplace_back(pChildObject);
                }
                if (pChildObject->GetName() == "Hints")
                {
                    m_pHintCheckbox = pChildObject;
                }
                if (pChildObject->GetName() == "ToggleRespawns")
                {
                    m_pToggleRespawns = pChildObject;
                }
                if (pChildObject->GetName() == "Easy")
                {
                    m_pEasy = pChildObject;
                }
                if (pChildObject->GetName() == "Normal")
                {
                    m_pNormal = pChildObject;
                }
                if (pChildObject->GetName() == "Hard")
                {
                    m_pHard = pChildObject;
                }
                if (pChildObject->GetName() == "Money")
                {
                    m_pMoneyCount = pChildObject;
                }
            }
        }
    }
    m_pEnemies[1]->SetEnabled(false);
    m_pEnemies[2]->SetEnabled(false);
    m_pEnemies[3]->SetEnabled(false);
    m_pEnemies[4]->SetEnabled(false);
    m_pEnemies[5]->SetEnabled(false);
    m_pEnemies[6]->SetEnabled(false);
    if (static_cast<RadioButtonComponent*>(m_pEasy->GetComponent("RadioButtonComponent"))->GetOn())
    {
        m_pEnemies[0]->SetEnabled(true);
    }
    if (static_cast<RadioButtonComponent*>(m_pNormal->GetComponent("RadioButtonComponent"))->GetOn())
    {
        m_pEnemies[1]->SetEnabled(true);
        m_pEnemies[2]->SetEnabled(true);
    }
    if (static_cast<RadioButtonComponent*>(m_pHard->GetComponent("RadioButtonComponent"))->GetOn())
    {
        m_pEnemies[1]->SetEnabled(true);
        m_pEnemies[2]->SetEnabled(true);
        m_pEnemies[3]->SetEnabled(true);
        m_pEnemies[4]->SetEnabled(true);
        m_pEnemies[5]->SetEnabled(true);
        m_pEnemies[6]->SetEnabled(true);
    }

    m_pHint->SetEnabled(static_cast<CheckboxComponent*>(m_pHintCheckbox->GetComponent("CheckboxComponent"))->GetOn());
    return true;
}