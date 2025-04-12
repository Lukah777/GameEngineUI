#pragma once
#include <unordered_map>
#include "Unzipper.h"
#include "Image.h"  
#include "../Engine/TinyXMLParser.h"
#include "TMXParser.h"
#include <string>

struct SDL_Renderer;
struct _TTF_Font;
struct _Mix_Music;
struct Mix_Chunk;

enum Language { English, French, Italian, German, Spanish };

namespace Engine 
{
    class Log;
    class Image;
    class ResourceSystem
    {
    private:
        Log* m_pLog = nullptr;
        Unzipper m_unzipper;
        std::unordered_map<std::string, Image*> m_ImageMap;
        std::unordered_map<std::string, _TTF_Font*> m_FontMap;
        TinyXMLParser m_XMLparser;
        TMXParser m_TMXparser;
        Language m_language = English;
        std::unordered_map<std::string, std::string> m_EnglishMap;
        std::unordered_map<std::string, std::string> m_FrenchMap;
        std::unordered_map<std::string, std::string> m_ItalianMap;
        std::unordered_map<std::string, std::string> m_GermanMap;
        std::unordered_map<std::string, std::string> m_SpanishMap;
        void TextParser(std::string data);

    public:
        void CloseResourceSystem();
        void CreateResources(Log* plog, System* pSystem, std::string file);
        Image* GetImageData(const char* fileName, SDL_Renderer* pSDLRenderer);
        _TTF_Font* GetFontData(const char* file);
        TMXParser* GetTMXParser() { return &m_TMXparser; };
        void RunLuaScript(std::string fileName);
        void SetTranslation(Language language) { m_language = language; }
        const char* GetTranslation(std::string token);
        _Mix_Music* GetMusic(std::string file);
        Mix_Chunk* GetSFX(std::string file);
    };
}
