#include "System.h"
#include "GameObject.h"
#include "../BLD/BleachNew.h"
#include "SDL.h"
#include "SoundComponent.h"

#define THREADS 0
#define MENUTOOL 1

void Engine::System::Render(std::vector<GameObject*> pGameObjects)
{
    for (int i = 0; i < GetGameObjectSize(); i++)
    {
        GameObject* pObject = nullptr;
        pObject = GetGameObjectAt(i);
        pObject->Render(this);
    }
}

void Engine::System::Run()
{
    bool run = true;
    int fps = 60;
    int deisredDelta = 1000 / fps;

    // Game loop
    while (run)
    {
#if THREADS
        GetGraphics()->Clear();

         m_worker = std::thread(&System::Render, this, std::ref(m_GameObjects)); 
#endif
         int startLoop = SDL_GetTicks();
         GetMessageSystem()->DistributeMsgs(this);


        // Update
        for (int i = 0; i < GetGameObjectSize(); i++)  
        {
            GameObject* pObject = nullptr;
            pObject = GetGameObjectAt(i);
            if (pObject != nullptr)
            {
                run = pObject->Update(this);
                if (run == false)
                    break;
                
                run = GetInput()->Update(this);
                if (run == false)
                    break;
            }
        }


#if THREADS 
        // Render with Threads
        
        m_worker.join();

        GetGraphics()->Present();
#else
        GetGraphics()->Clear();
        for (int i = 0; i < GetGameObjectSize(); i++)
        {
            GameObject* pObject = nullptr;
            pObject = GetGameObjectAt(i);
            pObject->Render(this);
        }
        GetGraphics()->Present();
#endif
        int delta = SDL_GetTicks() - startLoop;
        if (delta < deisredDelta)
        {
            SDL_Delay(deisredDelta - delta);
        }
    }

    Deinitalize(); // Deinitalize all that was initalized in opposite order
}

void Engine::System::Inialize(const char* windowName, int windowW, int windowH)
{
    // Intitalize
    m_log.OpenLog();
    m_window.OpenWindow(&m_log, windowName, windowW, windowH);
    m_graphics.CreateGraphics(&m_log, m_window.GetSDLWindow());
    m_resources.CreateResources(&m_log, this, "Assets/Scribblenauts.xml");

    for (int i = 0; i < GetGameObjectSize(); i++)
    {
        for (int j = 0; j < GetGameObjectAt(i)->GetGameObjectSize(); j++)
        {
            if (GetGameObjectAt(i)->GetGameObjectAt(j)->GetName() == "MusicSlider")
            {
                SoundComponent* soundComp = static_cast<SoundComponent*>(GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("SoundComponent"));
                soundComp->PlaySound();
                break;
            }
        }
#if MENUTOOL
        if (GetGameObjectAt(i)->GetName() == "MenuTool")
        {
            GetGameObjectAt(i)->SetEnabled(true);
        }
#endif // MENUTOOL
    }

    m_windowW = windowW;
    m_windowH = windowH;
    m_numCells = 16;   //$ needs to scale better and not make smaller then object
}

void Engine::System::Deinitalize()
{
    // Deinitalize
    for (auto object: m_gameObjects)
    {
        BLEACH_DELETE(object); 
    }

    m_resources.CloseResourceSystem();
    m_graphics.CloseGraphics();
    m_window.CloseWindow();
    m_log.CloseLog();
}

Engine::GameObject* Engine::System::GetGameObjectAt(int index)
{ 
    if (m_gameObjects[index] != nullptr)
        return m_gameObjects[index]; 
    return nullptr;
}

Engine::GameObject* Engine::System::FindGameObject(std::string objectName)
{
    for (auto object : m_gameObjects)
    {
        if (object->GetName() == objectName)
            return object;
        else
        {
            if (object->FindGameObject(objectName) != nullptr)
                return object->FindGameObject(objectName);
        }
    }
    return nullptr;
}
