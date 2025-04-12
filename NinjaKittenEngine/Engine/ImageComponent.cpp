#include "ImageComponent.h"
#include "SDL.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "HeroComponent.h"
#include "TilingComponent.h"

Engine::ImageComponent::ImageComponent(System* pSystem, GameObject* pGameObject, const char* fileName, int r , int g , int b )
    :Component(pSystem, pGameObject)
{
    ResourceSystem* pResources = pSystem->GetResources();
    Graphics* pGraphics = pSystem->GetGraphics();
    m_name = fileName;
    if (m_name != "")
    {
        m_pImage = pResources->GetImageData(fileName, pGraphics->GetRender());
        m_pOldImage = m_pImage;
        m_color.r = r;
        m_color.g = g;
        m_color.b = b;
    }
}

Engine::ImageComponent::~ImageComponent()
{
    if (m_pClip == nullptr)
    {
        delete m_pClip;
    }
}

void Engine::ImageComponent::Render(Engine::System* pSystem)
{
    PositionComponent* PosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    Graphics* pGraphics = pSystem->GetGraphics();
    if (PosComp != nullptr && m_visible == true)
        pGraphics->DrawImage(this->GetImage(), (int)PosComp->GetX(), (int)PosComp->GetY(), m_pClip, PosComp->GetAngle(), m_color.r, m_color.g, m_color.b);
}

void Engine::ImageComponent::SetColor(Color color)
{
    m_color = color;
}

void Engine::ImageComponent::SetClip(int x, int y, int w, int h)
{
    if (m_pClip == nullptr)
    {
        m_pClip = new Rect();
    }
    m_pClip->x = x;
    m_pClip->y = y;
    m_pClip->w = w;
    m_pClip->h = h;
}

