#pragma once
#include "Component.h"

struct SDL_Texture;
struct SDL_Rect;
struct _TTF_Font;
struct SDL_Color;

namespace Engine
{
    class TextComponent : public Component   
    {
    private:
        _TTF_Font* m_pFont;
        SDL_Color* m_pColor;
        SDL_Texture* m_pMssage;
        SDL_Rect* m_pMsgRect;
        std::string m_token = "";
        int m_oldX = NULL;
        int m_oldY = NULL;
    public:
        TextComponent(System* pSystem, GameObject* pGameObject, const char* text, const char* font, int size, int r, int g, int b, int x, int y, int w, int h);
        ~TextComponent();
        void Render(Engine::System* pSystem);
        void ReloadText(Engine::System* pSystem, const char* text =  "\0");
        SDL_Rect* GetMsgRect() { return m_pMsgRect; }
        std::string GetToken() { return m_token; }
        bool Drag(System* pSystem, int mouseX, int mouseY);
        void SetOldX(int oldX) { m_oldX = oldX; };
        void SetOldY(int oldY) { m_oldY = oldY; };
    };
}

