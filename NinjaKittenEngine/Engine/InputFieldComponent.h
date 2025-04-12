#pragma once
#include "Component.h"
#include "Input.h"

namespace Engine
{
    class InputFieldComponent : public Component
    {
    private:
        Input* m_pInput;
        std::string m_inputStr;
        int m_cursorStartX;
        int m_cursorStartY;
        int m_cursorX;
        int m_cursorY;
        int m_width;
        int m_height;
        int m_timer = 0;
        int m_timer2 = 0;
        const char* m_newChar = "";
        const char* m_cursor = "|";
        GameObject* m_pCursor;
        std::vector<GameObject*> m_charGameObjects;

    public:
        InputFieldComponent(System* pSystem, GameObject* pGameObject, int x, int y, int w, int h);
        bool Update(Engine::System* pSystem);
        std::string GetInputStr() { return m_inputStr; }
    };
}


