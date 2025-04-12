#include "BodySlotComponent.h"
#include "PositionComponent.h"
#include "Graphics.h"
#include "GameObject.h"

Engine::BodySlotComponent::BodySlotComponent(System* pSystem, GameObject* pGameObject, const char* file)
    :Component(pSystem, pGameObject)
{
    ResourceSystem* pResources = pSystem->GetResources();
    Graphics* pGraphics = pSystem->GetGraphics();
    m_name = file;
    if (file != nullptr)
    {
        m_pImage = pResources->GetImageData(file, pGraphics->GetRender());
        m_pOldImage = m_pImage;
        m_color.r = 255;
        m_color.g = 255;
        m_color.b = 255;
    }
}

void Engine::BodySlotComponent::Render(Engine::System* pSystem)
{
    PositionComponent* PosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    Graphics* pGraphics = pSystem->GetGraphics();
    if (PosComp != nullptr)
        pGraphics->DrawImage(m_pImage, (int)PosComp->GetX(), (int)PosComp->GetY(), nullptr, PosComp->GetAngle(), m_color.r, m_color.g, m_color.b);
}
