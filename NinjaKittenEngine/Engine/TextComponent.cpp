#include "TextComponent.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "PositionComponent.h"
#include "EditButtonComponent.h"

Engine::TextComponent::TextComponent(System* pSystem, GameObject* pGameObject, const char* text, const char* font, int size, int r, int g, int b, int x, int y, int w,int h)
    :Component(pSystem, pGameObject)
{
    TTF_Init();
    m_pMsgRect = new SDL_Rect;
    ResourceSystem* pResources = pSystem->GetResources();
    Graphics* pGraphics = pSystem->GetGraphics();
    if (text != nullptr)
    {
        // create text
       m_pFont = pResources->GetFontData(font);
       m_pColor = new SDL_Color ;
       m_pColor->r = r;
       m_pColor->g = g;
       m_pColor->b = b;


       m_token = text;
       SDL_Surface* surfaceMessage = nullptr;

       std::string::const_iterator it = m_token.begin();

       while (it != m_token.end() && std::isdigit(*it))
       {
           ++it;
       }

       if (m_pFont == nullptr)
       {
           std::cout << "FONT FAIL\n";
       }

       if (m_pColor == nullptr)
       {
           std::cout << "Color FAIL\n";
       }

       if (m_token.length() <= 1 || m_token == "|")
       {
           surfaceMessage = TTF_RenderText_Solid(m_pFont, text, *m_pColor);
       }
       else if (!m_token.empty() && it == m_token.end())
       {
           surfaceMessage = TTF_RenderText_Solid(m_pFont, text, *m_pColor);
       }
       else
       {
           const char* trans = pResources->GetTranslation(m_token);
          surfaceMessage = TTF_RenderText_Solid(m_pFont, trans, *m_pColor);
       }

       if( surfaceMessage == nullptr)
       {
           std::cout << "FAIL\n" << surfaceMessage;
       }

       m_pMssage = SDL_CreateTextureFromSurface(pSystem->GetGraphics()->GetRender(), surfaceMessage);

       m_pMsgRect->x = x;
       m_pMsgRect->y = y;
       m_pMsgRect->w = w;
       m_pMsgRect->h = h;

    }
}

Engine::TextComponent::~TextComponent()
{
    delete m_pMsgRect;
    delete m_pColor;
    SDL_DestroyTexture(m_pMssage);
}

void Engine::TextComponent::Render(Engine::System* pSystem)
{
    PositionComponent* PosComp = dynamic_cast<PositionComponent*>(GetOwner()->GetComponent("PositionComponent"));
    Graphics* pGraphics = pSystem->GetGraphics();
    if (PosComp != nullptr)
    {
        // Draw text
        SDL_RenderCopy(pSystem->GetGraphics()->GetRender(), m_pMssage, NULL, m_pMsgRect);

    }
}

void Engine::TextComponent::ReloadText(Engine::System* pSystem, const char* text)
{
    SDL_Surface* surfaceMessage;

    std::string::const_iterator it = m_token.begin();

    while (it != m_token.end() && std::isdigit(*it))
    {
        ++it;
    }

    if (text != "\0" )
    {
        surfaceMessage = TTF_RenderText_Solid(m_pFont, text, *m_pColor);
        m_token = text;
    }
    else if (m_token.length() <= 1 || m_token == "|")
    {
        surfaceMessage = TTF_RenderText_Solid(m_pFont, m_token.c_str(), *m_pColor);
    }
    else if (!m_token.empty() && it == m_token.end())
    {
        surfaceMessage = TTF_RenderText_Solid(m_pFont, m_token.c_str(), *m_pColor);
    }
    else
    {
        surfaceMessage = TTF_RenderText_Solid(m_pFont, pSystem->GetResources()->GetTranslation(m_token), *m_pColor);
    }
    m_pMssage = SDL_CreateTextureFromSurface(pSystem->GetGraphics()->GetRender(), surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

}

bool Engine::TextComponent::Drag(System* pSystem, int mouseX, int mouseY)
{
    if (pSystem->FindGameObject("EditButton") != nullptr)
    {
        EditButtonComponent* editComp = dynamic_cast<EditButtonComponent*>(pSystem->FindGameObject("EditButton")->GetComponent("EditButtonComponent"));
        if (editComp->GetOn() == true)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if ((x > m_pMsgRect->x && x < m_pMsgRect->x + m_pMsgRect->w
    && y > m_pMsgRect->y && y < m_pMsgRect->y + m_pMsgRect->h
    ) || (m_oldX != 0 && m_oldY != 0))
            {

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
                    m_pMsgRect->x = m_pMsgRect->x - diffX;
                }
                else if (prevX < x)
                {
                    m_pMsgRect->x = m_pMsgRect->x + diffX;
                }

                int diffY = abs(prevY - y);
                if (prevY > y)
                {
                    m_pMsgRect->y = m_pMsgRect->y - diffY;
                }
                else if (prevY < y)
                {
                    m_pMsgRect->y = m_pMsgRect->y + diffY;
                }

                m_oldX = x;
                m_oldY = y;
                return true;
            }
        }
    }
    return false;
}