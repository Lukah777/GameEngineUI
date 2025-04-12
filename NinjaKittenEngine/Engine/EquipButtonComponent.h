#pragma once
#include "Component.h"
namespace Engine
{
    class EquipButtonComponent : public Component
    {
    private:
        Image* m_pImage = nullptr;
        Color m_color;
        std::string m_name = "";
        int m_slot;
        bool m_hovering = false;
        Color m_ogColor = { 0,0,0 };
        Color m_hoverColor = { 128, 128, 128 };
        std::string m_navGameObjectStr;
        GameObject* m_navGameObject = nullptr;
        GameObject* m_selfGameObject;
        int m_height = 0;
        int m_yOffset = 0;

    public:
        EquipButtonComponent(System* pSystem, GameObject* pGameObject, const char* file, int slot, std::string NavGameObjectStr, GameObject* pSelfGameObject, int height, int yOffest);
        bool Update(System* pSystem) override;
        void Activate(System* pSystem);
    };
}

