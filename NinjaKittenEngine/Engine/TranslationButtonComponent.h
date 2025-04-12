#pragma once
#include "Component.h"
#include "ResourceSystem.h"

namespace Engine
{
    class TranslationButtonComponent : public Component
    {
    private:
        bool m_hovering = false;
        Language m_newLanguage = English;
        std::string m_navGameObjectStr;
        GameObject* m_navGameObject = nullptr;
        GameObject* m_selfGameObject;
    public:
        TranslationButtonComponent(System* pSystem, GameObject* pGameObject, std::string language, std::string NavGameObjectStr, GameObject* pSelfGameObject);
        bool Update(System* pSystem) override;
        void Activate(System* pSystem);
    };
}

