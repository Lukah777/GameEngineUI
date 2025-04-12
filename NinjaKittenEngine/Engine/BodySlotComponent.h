#pragma once
#include "Component.h"
namespace Engine
{
    class BodySlotComponent : public Component
    {
    private:
        Image* m_pImage = nullptr;
        Image* m_pOldImage = nullptr;
        Color m_color;
        std::string m_name = "";
    public:
        BodySlotComponent(System* pSystem, GameObject* pGameObject, const char* file);
        void Render(Engine::System* pSystem);
        Image* GetImage() { return m_pImage; }
        Image* GetOldImage() { return m_pOldImage; }
        void SetImage(Image* pImage) { m_pImage = pImage; }
    };
}
