#pragma once
#include "Component.h"
#include "string.h"

namespace Engine
{
    struct Rect;
    class ImageComponent : public Component
    {
    private:
        Image* m_pImage = nullptr;
        Image* m_pOldImage = nullptr;
        Color m_color;
        bool m_visible = true;
        std::string m_name = "";
        Rect* m_pClip = nullptr;
    public:
        ImageComponent(System* pSystem, GameObject* pGameObject, const char* filename, int r = 255, int g = 255, int b = 255);
        ~ImageComponent();
        Image* GetImage(){ return m_pImage; }
        Image* GetOldImage(){ return m_pOldImage; }
        void Render(Engine::System* pSystem);
        void SetColor(Color color);
        Color GetColor() { return m_color; };
        void SetColor(bool toggle) { m_visible = toggle; };
        std::string GetName() { return m_name; }
        void SetClip(int x, int y, int w, int h);
        void SetImage(Image* pImage) { m_pImage = pImage; }
    };
}


