#include "GameObject.h"
#include "../BLD/BleachNew.h"

Engine::GameObject::GameObject(std::string name, MessageSystem* pMsgSys, bool enabled)
{
    m_name = name;
    m_pMsgSys = pMsgSys;
    m_enabled = enabled;
}

Engine::GameObject::~GameObject()
{
    // Deinitalize
    for (auto object : m_gameObjects)
    {
        BLEACH_DELETE(object);
    }

    for (auto [key, comp] : m_components)
    {
        BLEACH_DELETE(comp);
    }
}

void Engine::GameObject::AddComponent(std::string compName, Component* pComponent)
{
    m_components.emplace(compName, pComponent);
}

Engine::Component* Engine::GameObject::GetComponent(std::string compName)
{
    if (m_components.find(compName) != m_components.end())
        return m_components.at(compName);
    else
        return nullptr;
}

bool Engine::GameObject::Update(System* pSystem)
{
    if (!m_enabled)
        return true;

    if (m_components.size() == 0)
    {
        bool run = true;
        for (int i = 0; i < m_gameObjects.size(); i++)
        {
            GameObject* pObject = nullptr;
            pObject = GetGameObjectAt(i);
            if (pObject != nullptr)
            {
                run = pObject->Update(pSystem);
                if (run == false)
                    return run;
            }
        }
    }

    for (const auto& [key, value] : m_components)
    {
        if (!value->Update(pSystem))
            return false;
    }
    return true;
}

void Engine::GameObject::Render(Engine::System* pSystem)
{
    if (!m_enabled)
        return;

    if (m_components.size() == 0)
    {
        for (int i = 0; i < m_gameObjects.size(); i++)
        {
            GameObject* pObject = nullptr;
            pObject = GetGameObjectAt(i);
            pObject->Render(pSystem);
        }
    }

    for (const auto& [key, value] : m_components)
    {
        value->Render(pSystem);
    }
}

void Engine::GameObject::PassMsg(Engine::Message msg)
{
    for (auto comp : m_components)
    {
        comp.second->HandleMessage(msg);
    }
}

Engine::GameObject* Engine::GameObject::GetGameObjectAt(int index)
{
    if (index < m_gameObjects.size())
    {
        if (m_gameObjects[index] != nullptr)
            return m_gameObjects[index];
    }
    
    return nullptr;
}

Engine::GameObject* Engine::GameObject::FindGameObject(std::string objectName)
{
    for (auto object : m_gameObjects)
    {
        if (object->GetName() == objectName)
            return object;
    }
    return nullptr;
}

void Engine::GameObject::ToggleEnabled()
{
    if (m_enabled)
        m_enabled = false;
    else
        m_enabled = true;
}
