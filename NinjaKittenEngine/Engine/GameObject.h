#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"

namespace Engine
{
    class GameObject
    {
    private:
        std::string m_name;
        MessageSystem* m_pMsgSys;
        std::vector<GameObject*> m_gameObjects;
        std::unordered_map<std::string, Component*> m_components;
        bool m_enabled = true;
    public:

        GameObject(std::string name, MessageSystem* pMsgSys, bool enabled = true);
        ~GameObject();
        void AddComponent(std::string compName, Component* pComponent);
        void AddGameObject(GameObject* pGameObject) { m_gameObjects.emplace_back(pGameObject); };
        Component* GetComponent(std::string compName);
        GameObject* GetBackGameObject() { return m_gameObjects.back(); };
        size_t GetGameObjectSize() { return m_gameObjects.size(); }
        GameObject* GetGameObjectAt(int index);
        GameObject* FindGameObject(std::string objectName);
        void RemoveGameObject() { m_gameObjects.pop_back(); };
        bool Update(System* pSystem);
        void Render(Engine::System* pSystem);
        void PassMsg(Engine::Message msg);
        std::string GetName() { return m_name; }
        void ToggleEnabled();
        void SetEnabled(bool on) { m_enabled = on; };
        bool GetEnabled() { return m_enabled; }
    };
}


