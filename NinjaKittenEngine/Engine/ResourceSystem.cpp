#include "ResourceSystem.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Log.h"
#include "Image.h"
#include <string>
#include "../Lua/src/lua.hpp"
#include "../BLD/BleachNew.h"
#include <SDL_ttf.h>
#include <fstream>
#include <SDL_mixer.h>


void Engine::ResourceSystem::CloseResourceSystem()
{
    m_unzipper.CloseUnzipper();
    for (auto [key, val] : m_ImageMap)
    {
        BLEACH_DELETE(val);
    }
    TTF_Quit();
    Mix_CloseAudio();
}

void  Engine::ResourceSystem::TextParser(std::string file)
{
#if NDEBUG
    std::string data;
    data = m_unzipper.GetUnzippedTXT(file);
    int transCount = 0;
    std::string currToken;
    std::string line;
    for (char& c : data) {
        if (c != '\r')
        {
            if (c != '\n')
            line += c;
        }
        else
        {
            if (line == "")
            {
                if (transCount < 5)
                    std::cout << "Missing a translation! \n";
                transCount = 0;
                line = "";
                continue;
            }
            transCount++;
            if (transCount == 1)
            {
                currToken = line;
                m_EnglishMap.emplace(currToken, line);
            }
            else if (transCount == 2)
            {
                m_FrenchMap.emplace(currToken, line);
            }
            else if (transCount == 3)
            {
                m_ItalianMap.emplace(currToken, line);
            }
            else if (transCount == 4)
            {
                m_GermanMap.emplace(currToken, line);
            }
            else if (transCount == 5)
            {
                m_SpanishMap.emplace(currToken, line);
            }
            line = "";
        }
    }

#else
    std::ifstream inputFile(file);

    if (!inputFile.is_open()) 
    {
        std::cout << "Error opening the text file!" << std::endl;
        return;
    }

    std::string line;
    int transCount = 0;
    std::string currToken;
    while (std::getline(inputFile, line)) 
    {
        if (line == "")
        {
            if (transCount < 5)
                std::cout << "Missing a translation! \n";
            transCount = 0;
            continue;
        }
        transCount++;

        if (transCount == 1)
        {
            currToken = line;
            m_EnglishMap.emplace(currToken, line);
        }
        else if (transCount == 2)
        {
            m_FrenchMap.emplace(currToken, line);
        }
        else if (transCount == 3)
        {
            m_ItalianMap.emplace(currToken, line);
        }
        else if (transCount == 4)
        {
            m_GermanMap.emplace(currToken, line);
        }
        else if (transCount == 5)
        {
            m_SpanishMap.emplace(currToken, line);
        }
    }

    // Close the file
    inputFile.close();
#endif
    return;
}

void Engine::ResourceSystem::CreateResources(Log* plog, System* pSystem, std::string file)
{
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    m_pLog = plog;
#if NDEBUG
    m_unzipper.Unzip();
    TextParser("../Assets/Localization.txt");
    m_XMLparser.RunParser(pSystem, m_unzipper.GetUnzippedXML("../" + file));
#else
    std::string strFileName = "../NinjaKittenEngine/";
    strFileName += file;
    const char* fullFileName = strFileName.c_str();
    TextParser("../NinjaKittenEngine/Assets/Localization.txt");
    m_XMLparser.RunParser(pSystem, fullFileName);
#endif
}

Engine::Image* Engine::ResourceSystem::GetImageData(const char* fileName, SDL_Renderer* pSDLRenderer)
{
#if NDEBUG
    // Release
    if (m_ImageMap.find(fileName) == m_ImageMap.end())
    {
        SDL_Surface* pImageSurface = m_unzipper.GetUnzippedImgs(fileName);
        if (pImageSurface == NULL)
        {
            m_pLog->PrintLog("Failed to load image. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }
        SDL_Texture* pTextureTemp = SDL_CreateTextureFromSurface(pSDLRenderer, pImageSurface);

        if (pTextureTemp == NULL)
        {
            m_pLog->PrintLog("Failed to load texture. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }

        m_ImageMap.emplace(fileName, BLEACH_NEW(Image(pTextureTemp, pImageSurface->w, pImageSurface->h)));

        SDL_FreeSurface(pImageSurface);
        return m_ImageMap[fileName];
    }
    else
    {
        return m_ImageMap[fileName];
    }
#else
    // Debug

    std::string strFileName = "../NinjaKittenEngine/";
    strFileName += fileName;
    const char* fullFileName = strFileName.c_str();
    if (m_ImageMap.find(fullFileName) == m_ImageMap.end())
    {
        // Create
        SDL_Surface* pImageSurface = IMG_Load(fullFileName);
        if (pImageSurface == NULL)
        {
            m_pLog->PrintLog("Failed to load image. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }
        SDL_Texture* pTextureTemp = SDL_CreateTextureFromSurface(pSDLRenderer, pImageSurface);


        if (pTextureTemp == NULL)
        {
            m_pLog->PrintLog("Failed to load texture. Error: ");
            m_pLog->PrintLog(SDL_GetError());
            return nullptr;
        }

        m_ImageMap.emplace(fullFileName, BLEACH_NEW(Image(pTextureTemp, pImageSurface->w, pImageSurface->h)));

        SDL_FreeSurface(pImageSurface);
        return m_ImageMap[fullFileName];
    }
    else
    {
        return m_ImageMap[fullFileName];
    }
#endif
    return nullptr;
}

_TTF_Font* Engine::ResourceSystem::GetFontData(const char* file)
{
#if NDEBUG
    return m_unzipper.GetUnzippedTTF(file);
#else
    std::string strFileName = "../NinjaKittenEngine/";
    strFileName += file;
    const char* fullFileName = strFileName.c_str();
    return TTF_OpenFont(fullFileName, 100);
#endif
}

void Engine::ResourceSystem::RunLuaScript(std::string file)
{
    /*
    lua_State* pLuaState = luaL_newstate();
    luaL_openlibs(pLuaState);

    luaL_dostring(pLuaState, "print('Hello, Lua!');");

#if NDEBUG
    luaL_dofile(pLuaState, m_unzipper.GetUnzippedLua(file).c_str());
#else
    luaL_dofile(pLuaState, file.c_str());
#endif
    lua_close(pLuaState);
    */
}

const char* Engine::ResourceSystem::GetTranslation(std::string token)
{
    if (m_language == English)
    {
        return m_EnglishMap.at(token).c_str();
    }
    else if (m_language == French)
    {
        return m_FrenchMap.at(token).c_str();
    }
    else if (m_language == Italian)
    {
        return m_ItalianMap.at(token).c_str();
    }
    else if (m_language == German)
    {
        return m_GermanMap.at(token).c_str();
    }
    else if (m_language == Spanish)
    {
        return m_SpanishMap.at(token).c_str();
    }

    return "";
}

_Mix_Music* Engine::ResourceSystem::GetMusic(std::string file)
{
#if NDEBUG
    return m_unzipper.GetUnzippedMusic(file);
#else
    std::string strFileName = "../NinjaKittenEngine/";
    strFileName += file;
    const char* fullFileName = strFileName.c_str();
    return Mix_LoadMUS(fullFileName);
#endif
}

Mix_Chunk* Engine::ResourceSystem::GetSFX(std::string file)
{
#if NDEBUG
    return m_unzipper.GetUnzippedSFX(file);
#else
    std::string strFileName = "../NinjaKittenEngine/";
    strFileName += file;
    const char* fullFileName = strFileName.c_str();
    return Mix_LoadWAV(fullFileName);
#endif
}
