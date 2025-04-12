#include "SoundComponent.h"
#include "GameObject.h"
#include "SliderComponent.h"
#include "CheckboxComponent.h"
#include <SDL_mixer.h>

Engine::SoundComponent::SoundComponent(System* pSystem, GameObject* pGameObject, std::string file, bool music)
    :Component(pSystem, pGameObject)
{
    if (music)
    {
        m_music = pSystem->GetResources()->GetMusic(file);
    }
    else
    {
        m_SFX = pSystem->GetResources()->GetSFX(file);
    }

    if (m_music != nullptr)
    {
        Mix_VolumeMusic(m_volume);
    }
    else
        Mix_VolumeChunk(m_SFX, m_volume);
}

Engine::SoundComponent::~SoundComponent()
{
    if (m_music)
        Mix_FreeMusic(m_music);
    else if (m_SFX)
        Mix_FreeChunk(m_SFX);
}

bool Engine::SoundComponent::Update(System* pSystem)
{
    for (int i = 0; i < pSystem->GetGameObjectSize(); i++)
    {
        for (int j = 0; j < pSystem->GetGameObjectAt(i)->GetGameObjectSize(); j++)
        {
            if (pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetName() == "Mute")
            {   
                if (dynamic_cast<CheckboxComponent*>(pSystem->GetGameObjectAt(i)->GetGameObjectAt(j)->GetComponent("CheckboxComponent"))->GetOn() == true)
                    m_volume = 0;
                else
                    m_volume = dynamic_cast<SliderComponent*>(GetOwner()->GetComponent("SliderComponent"))->GetVal();
                break;
            }   
        }
    }

    if (m_music != nullptr)
    {
        Mix_VolumeMusic(m_volume);
    }
    else
        Mix_VolumeChunk(m_SFX, m_volume);


    return true;
}

void Engine::SoundComponent::PlaySound()
{
    if (m_music != nullptr)
    {
        Mix_PlayMusic(m_music, -1);
    }
    else
    {
        Mix_PlayChannel(-1, m_SFX, 0);
    }
}
