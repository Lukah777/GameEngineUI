#pragma once
struct SDL_GetKeyboardState;

namespace Engine {
    class System;

    class Input
    {
    private:
        int m_dragTimer = 0;
        bool m_draging = false;
        int m_mouseX = 0;
        int m_mouseY = 0;
        bool m_control = false;

    public:
        enum keycode {
            ENGINE_ESCAPE_KEY = 41,
            ENGINE_W_KEY = 26,
            ENGINE_A_KEY = 4,
            ENGINE_S_KEY = 22,
            ENGINE_D_KEY = 7,
            ENGINE_MOUSE_BUTTON = 1025,
            ENGINE_SPACE_KEY = 44
            
        };
        bool GetIsKeyDown(int key);
        bool Click(Engine::System* pSystem);
        bool Drag(Engine::System* pSystem);
        bool Update(Engine::System* pSystem);
    };
}
