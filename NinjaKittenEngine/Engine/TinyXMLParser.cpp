#include "TinyXMLParser.h"
#include "../TinyXML/tinyxml2.h"
#include <string>
#include <sstream>
#include "../Engine/GameObject.h"
#include "../Engine/ImageComponent.h"
#include "../Engine/InputComponent.h"
#include "../Engine/PositionComponent.h"
#include "../Engine/TilingComponent.h"
#include "../Engine/PhysicsComponent.h"
#include "../Engine/CollisionComponent.h"
#include "../Engine/DoorComponent.h"
#include "../Engine/KeyComponent.h"
#include "../Engine/EnemyComponent.h"
#include "../Engine/DeathComponent.h"
#include "../Engine/HeroComponent.h"
#include "../BLD/BleachNew.h"
#include "AimingComponent.h"
#include "BulletComponent.h"
#include "AIComponent.h"
#include "EnemyBulletComponent.h"
#include "TeleporterComponent.h"
#include "TextComponent.h"
#include "NavButtonComponent.h"
#include "TranslationButtonComponent.h"
#include "CheckboxComponent.h"
#include "ToggleComponent.h"
#include "RadioButtonComponent.h"
#include "SliderComponent.h"
#include "InputFieldComponent.h"
#include "SoundComponent.h"
#include "HeadSlotComponent.h"
#include "BodySlotComponent.h"
#include "EquipButtonComponent.h"
#include "FriendButtonComponent.h"
#include "FriendListComponent.h"
#include "CalcButtonComponent.h"
#include "CalculatorComponent.h"
#include "EditButtonComponent.h"

void Engine::TinyXMLParser::RunParser(System* pSystem, std::string file)
{
    
    tinyxml2::XMLDocument doc;

#if NDEBUG
    doc.Parse(file.c_str(), file.size());
#else
    doc.LoadFile(file.c_str());
#endif
    
    tinyxml2::XMLElement* entryTag = doc.FirstChildElement();

    while (entryTag != NULL)
    {
        std::string name = entryTag->Name();
        if (name != "GameObject")
        {
            entryTag = entryTag->NextSiblingElement();
            continue;
        }
        std::string objectName = entryTag->Attribute("Name");

        bool enabled = true;
        std::string enabledString = (entryTag->Attribute("Enabled"));
        if (enabledString == "false")
            enabled = false;


        pSystem->AddGameObject(BLEACH_NEW(GameObject(objectName, pSystem->GetMessageSystem(), enabled)));

        tinyxml2::XMLElement* childTag = entryTag->FirstChildElement();
        while (childTag != NULL)
        {
            GameObject* pGameObjectBack = pSystem->GetBackGameObject();
            std::string name = childTag->Name();
            if (name != "GameObject")
            {
                childTag = childTag->NextSiblingElement();
                continue;
            }
            std::string childobjectName = childTag->Attribute("Name");

            bool enabled = true;
            std::string enabledString = (childTag->Attribute("Enabled"));
            if (enabledString == "false")
                enabled = false;

            pGameObjectBack->AddGameObject(BLEACH_NEW(GameObject(childobjectName, pSystem->GetMessageSystem(), enabled)));

            tinyxml2::XMLElement* componentTag = childTag->FirstChildElement();

            while (componentTag != NULL)
            {
                GameObject* pGameObjectChildBack = pGameObjectBack->GetBackGameObject();
                std::string componentName = componentTag->Attribute("Name");
                if (componentName == "ImageComponent")
                {
                    const char* fileName = "";
                    if (componentTag->FirstChildElement("Image") != nullptr)
                    {
                        fileName = componentTag->FirstChildElement("Image")->GetText();
                    }                    
                    int r = 255;
                    int g = 255;
                    int b = 255;
                    if (componentTag->FirstChildElement("R") != nullptr)
                    {
                        std::string rStr = componentTag->FirstChildElement("R")->GetText();
                        r = stoi(rStr);
                    }
                    if (componentTag->FirstChildElement("G") != nullptr)
                    {
                        std::string gStr = componentTag->FirstChildElement("G")->GetText();
                        g = stoi(gStr);
                    }
                    if (componentTag->FirstChildElement("B") != nullptr)
                    {
                        std::string bStr = componentTag->FirstChildElement("B")->GetText();
                        b = stoi(bStr);
                    }
                    pGameObjectChildBack->AddComponent("ImageComponent", BLEACH_NEW(Engine::ImageComponent(pSystem, pGameObjectChildBack, fileName, r, g, b)));
                }
                if (componentName == "PhysicsComponent")
                {
                    pGameObjectChildBack->AddComponent("PhysicsComponent", BLEACH_NEW(Engine::PhysicsComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "InputComponent")
                {
                    pGameObjectChildBack->AddComponent("InputComponent", BLEACH_NEW(Engine::InputComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "PositionComponent")
                {
                    int x = 0;
                    int y = 0;
                    double angle = 0.0;
                    if (componentTag->FirstChildElement("X") != nullptr) //$ as a helper function? and cache result rather then looking up?
                    {
                        std::string xStr = componentTag->FirstChildElement("X")->GetText();
                        x = stoi(xStr);
                    }
                    if (componentTag->FirstChildElement("Y") != nullptr)
                    {
                        std::string yStr = componentTag->FirstChildElement("Y")->GetText();
                        y = stoi(yStr);
                    }
                    if (componentTag->FirstChildElement("Angle") != nullptr)
                    {
                        std::string yStr = componentTag->FirstChildElement("Angle")->GetText();
                        angle = stoi(yStr);
                    }
                    pGameObjectChildBack->AddComponent("PositionComponent", BLEACH_NEW(Engine::PositionComponent(pSystem, pGameObjectChildBack, x, y, angle)));
                }
                if (componentName == "TilingComponent")
                {
                    const char* fileName = componentTag->FirstChildElement()->GetText();
                    pGameObjectChildBack->AddComponent("TilingComponent", BLEACH_NEW(Engine::TilingComponent(pSystem, pGameObjectChildBack, fileName)));
                }
                if (componentName == "CollisionComponent")
                {
                    pGameObjectChildBack->AddComponent("CollisionComponent", BLEACH_NEW(Engine::CollisionComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "DeathComponent")
                {
                    pGameObjectChildBack->AddComponent("DeathComponent", BLEACH_NEW(Engine::DeathComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "HeroComponent")
                {
                    pGameObjectChildBack->AddComponent("HeroComponent", BLEACH_NEW(Engine::HeroComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "DoorComponent")
                {
                    pGameObjectChildBack->AddComponent("DoorComponent", BLEACH_NEW(Engine::DoorComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "KeyComponent")
                {
                    pGameObjectChildBack->AddComponent("KeyComponent", BLEACH_NEW(Engine::KeyComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "EnemyComponent")
                {
                    pGameObjectChildBack->AddComponent("EnemyComponent", BLEACH_NEW(Engine::EnemyComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "AimingComponent")
                {
                    pGameObjectChildBack->AddComponent("AimingComponent", BLEACH_NEW(Engine::AimingComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "BulletComponent")
                {
                    pGameObjectChildBack->AddComponent("BulletComponent", BLEACH_NEW(Engine::BulletComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "EnemyBulletComponent")
                {
                    pGameObjectChildBack->AddComponent("EnemyBulletComponent", BLEACH_NEW(Engine::EnemyBulletComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "AIComponent")
                {
                    pGameObjectChildBack->AddComponent("AIComponent", BLEACH_NEW(Engine::AIComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "TeleporterComponent")
                {
                    pGameObjectChildBack->AddComponent("TeleporterComponent", BLEACH_NEW(Engine::TeleporterComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "TextComponent")
                {
                    const char* text = componentTag->FirstChildElement()->GetText();
                    const char* font = "";
                    int size = 0;
                    int r = 0;
                    int g = 0;
                    int b = 0;
                    int x = 0;
                    int y = 0;
                    int w = 0;
                    int h = 0;
                    if (componentTag->FirstChildElement("Font") != nullptr)
                    {
                        font = componentTag->FirstChildElement("Font")->GetText();
                    }
                    if (componentTag->FirstChildElement("Size") != nullptr)
                    {
                        std::string sizeStr = componentTag->FirstChildElement("Size")->GetText();
                        size = stoi(sizeStr);
                    }
                    if (componentTag->FirstChildElement("R") != nullptr)
                    {
                        std::string rStr = componentTag->FirstChildElement("R")->GetText();
                        r = stoi(rStr);
                    }
                    if (componentTag->FirstChildElement("G") != nullptr)
                    {
                        std::string gStr = componentTag->FirstChildElement("G")->GetText();
                        g = stoi(gStr);
                    }
                    if (componentTag->FirstChildElement("B") != nullptr)
                    {
                        std::string bStr = componentTag->FirstChildElement("B")->GetText();
                        b = stoi(bStr);
                    }
                    if (componentTag->FirstChildElement("X") != nullptr)
                    {
                        std::string xStr = componentTag->FirstChildElement("X")->GetText();
                        x = stoi(xStr);
                    }
                    if (componentTag->FirstChildElement("Y") != nullptr)
                    {
                        std::string yStr = componentTag->FirstChildElement("Y")->GetText();
                        y = stoi(yStr);
                    }
                    if (componentTag->FirstChildElement("W") != nullptr)
                    {
                        std::string wStr = componentTag->FirstChildElement("W")->GetText();
                        w = stoi(wStr);
                    }
                    if (componentTag->FirstChildElement("H") != nullptr)
                    {
                        std::string hStr = componentTag->FirstChildElement("H")->GetText();
                        h = stoi(hStr);
                    }
                    pGameObjectChildBack->AddComponent("TextComponent", BLEACH_NEW(Engine::TextComponent(pSystem, pGameObjectChildBack, text, font, size, r, g, b, x, y, w, h)));
                }
                if (componentName == "NavButtonComponent")
                {
                    std::string navGameObjectStr = componentTag->FirstChildElement("NavGameObject")->GetText();
                    pGameObjectChildBack->AddComponent("NavButtonComponent", BLEACH_NEW(Engine::NavButtonComponent(pSystem, pGameObjectChildBack, navGameObjectStr, pGameObjectBack)));
                }
                if (componentName == "TranslationButtonComponent")
                {
                    std::string langStr;
                    std::string navGameObjectStr;
                    if (componentTag->FirstChildElement("Language") != nullptr)
                    {
                        langStr = componentTag->FirstChildElement("Language")->GetText();
                    }
                    if (componentTag->FirstChildElement("NavGameObject") != nullptr)
                    {
                        navGameObjectStr = componentTag->FirstChildElement("NavGameObject")->GetText();
                    }
                    pGameObjectChildBack->AddComponent("TranslationButtonComponent", BLEACH_NEW(Engine::TranslationButtonComponent(pSystem, pGameObjectChildBack, langStr, navGameObjectStr, pGameObjectBack)));
                }
                if (componentName == "CheckboxComponent")
                {
                    bool on = false;
                    if (componentTag->FirstChildElement("On") != nullptr)
                    {
                        std::string onStr = componentTag->FirstChildElement("On")->GetText();
                        if (onStr == "true")
                            on = true;
                    }
                    std::string gameObjectStr = componentTag->FirstChildElement("GameObject")->GetText();

                    pGameObjectChildBack->AddComponent("CheckboxComponent", BLEACH_NEW(Engine::CheckboxComponent(pSystem, pGameObjectChildBack, on, gameObjectStr)));

                }
                if (componentName == "ToggleComponent")
                {
                    bool on = false;
                    if (componentTag->FirstChildElement("On") != nullptr)
                    {
                        std::string onStr = componentTag->FirstChildElement("On")->GetText();
                        if (onStr == "true")
                            on = true;
                    }
                    std::string gameObjectStr = componentTag->FirstChildElement("GameObject")->GetText();

                    pGameObjectChildBack->AddComponent("ToggleComponent", BLEACH_NEW(Engine::ToggleComponent(pSystem, pGameObjectChildBack, on, gameObjectStr)));
                }
                if (componentName == "RadioButtonComponent")
                {
                    bool on = false;
                    if (componentTag->FirstChildElement("On") != nullptr)
                    {
                        std::string onStr = componentTag->FirstChildElement("On")->GetText();
                        if (onStr == "true")
                            on = true;
                    }
                    std::string gameObjectStr = componentTag->FirstChildElement("GameObject")->GetText();

                    pGameObjectChildBack->AddComponent("RadioButtonComponent", BLEACH_NEW(Engine::RadioButtonComponent(pSystem, pGameObjectChildBack, on, gameObjectStr)));
                }
                if (componentName == "SliderComponent")
                {
                    int val = 0;
                    if (componentTag->FirstChildElement("Value") != nullptr)
                    {
                        std::string valStr = componentTag->FirstChildElement("Value")->GetText();
                        val = stoi(valStr);
                    }
                    std::string gameObjectStr = componentTag->FirstChildElement("GameObject")->GetText();

                    pGameObjectChildBack->AddComponent("SliderComponent", BLEACH_NEW(Engine::SliderComponent(pSystem, pGameObjectChildBack, val, gameObjectStr)));
                }
                if (componentName == "InputFieldComponent")
                {
                    int x, y, w, h;
                    if (componentTag->FirstChildElement("CursorX") != nullptr)
                    {
                        std::string xStr = componentTag->FirstChildElement("CursorX")->GetText();
                        x = stoi(xStr);
                    }
                    if (componentTag->FirstChildElement("CursorY") != nullptr)
                    {
                        std::string yStr = componentTag->FirstChildElement("CursorY")->GetText();
                        y = stoi(yStr);
                    }
                    if (componentTag->FirstChildElement("Width") != nullptr)
                    {
                        std::string wStr = componentTag->FirstChildElement("Width")->GetText();
                        w = stoi(wStr);
                    }
                    if (componentTag->FirstChildElement("Height") != nullptr)
                    {
                        std::string hStr = componentTag->FirstChildElement("Height")->GetText();
                        h = stoi(hStr);
                    }
                    pGameObjectChildBack->AddComponent("InputFieldComponent", BLEACH_NEW(Engine::InputFieldComponent(pSystem, pGameObjectChildBack, x, y, w, h)));
                }
                if (componentName == "SoundComponent")
                {
                    std::string file;
                    bool music = false;
                    if (componentTag->FirstChildElement("File") != nullptr)
                    {
                        file = componentTag->FirstChildElement("File")->GetText();
                    }
                    if (componentTag->FirstChildElement("Music") != nullptr)
                    {
                        std::string text = componentTag->FirstChildElement("Music")->GetText();
                        if (text == "true")
                        {
                            music = true;
                        }
                        if (text == "false")
                        {
                            music = false;
                        }
                    }
                    pGameObjectChildBack->AddComponent("SoundComponent", BLEACH_NEW(Engine::SoundComponent(pSystem, pGameObjectChildBack, file, music)));
                }
                if (componentName == "HeadSlotComponent")
                {
                    std::string file = "";
                    if (componentTag->FirstChildElement("Image") != nullptr)
                    {
                        file = componentTag->FirstChildElement("Image")->GetText();
                    }
                    pGameObjectChildBack->AddComponent("HeadSlotComponent", BLEACH_NEW(Engine::HeadSlotComponent(pSystem, pGameObjectChildBack, file.c_str())));
                }
                if (componentName == "BodySlotComponent")
                {
                    std::string file = "";
                    if (componentTag->FirstChildElement("Image") != nullptr)
                    {
                        file = componentTag->FirstChildElement("Image")->GetText();
                    }
                    pGameObjectChildBack->AddComponent("BodySlotComponent", BLEACH_NEW(Engine::BodySlotComponent(pSystem, pGameObjectChildBack, file.c_str())));
                }
                if (componentName == "EquipButtonComponent")
                {
                    std::string slot;
                    int slotNumber = 0;
                    std::string file;
                    if (componentTag->FirstChildElement("Slot") != nullptr)
                    {
                        slot = componentTag->FirstChildElement("Slot")->GetText();

                        if (slot == "Character")
                        {
                            slotNumber = 0;
                        }
                        else if (slot == "Head")
                        {
                            slotNumber = 1;
                        }
                        else if (slot == "Body")
                        {
                            slotNumber = 2;
                        }
                    }
                    if (componentTag->FirstChildElement("Image") != nullptr)
                    {
                        file = componentTag->FirstChildElement("Image")->GetText();
                    }

                    std::string navGameObjectStr = "";
                    if (componentTag->FirstChildElement("NavGameObject") != nullptr)
                    {
                        navGameObjectStr = componentTag->FirstChildElement("NavGameObject")->GetText();
                    }

                    int height = 0;
                    int yOffset = 0;
                    std::string tempString;

                    if (componentTag->FirstChildElement("Height") != nullptr)
                    {
                        tempString = componentTag->FirstChildElement("Height")->GetText();
                        height = stoi(tempString);
                    }
                    if (componentTag->FirstChildElement("yOffset") != nullptr)
                    {
                        tempString = componentTag->FirstChildElement("yOffset")->GetText();
                        yOffset = stoi(tempString);
                    }
                    pGameObjectChildBack->AddComponent("EquipButtonComponent", BLEACH_NEW(Engine::EquipButtonComponent(pSystem, pGameObjectChildBack, file.c_str(), slotNumber, navGameObjectStr, pGameObjectBack, height, yOffset)));
                }
                if (componentName == "FriendButtonComponent")
                {
                    pGameObjectChildBack->AddComponent("FriendButtonComponent", BLEACH_NEW(Engine::FriendButtonComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "FriendListComponent")
                {
                    std::vector<std::string> names;
                    std::string tempString;

                    if (componentTag->FirstChildElement("Names") != nullptr)
                    {
                        tempString = componentTag->FirstChildElement("Names")->GetText();
                        std::istringstream iss(tempString);
                        for (std::string line; std::getline(iss, line); )
                        {
                            names.push_back(line);
                        }
                    }
                    pGameObjectChildBack->AddComponent("FriendListComponent", BLEACH_NEW(Engine::FriendListComponent(pSystem, pGameObjectChildBack, names)));
                }
                if (componentName == "CalcButtonComponent")
                {
                    pGameObjectChildBack->AddComponent("CalcButtonComponent", BLEACH_NEW(Engine::CalcButtonComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "CalculatorComponent")
                {
                    pGameObjectChildBack->AddComponent("CalculatorComponent", BLEACH_NEW(Engine::CalculatorComponent(pSystem, pGameObjectChildBack)));
                }
                if (componentName == "EditButtonComponent")
                {
                    pGameObjectChildBack->AddComponent("EditButtonComponent", BLEACH_NEW(Engine::EditButtonComponent(pSystem, pGameObjectChildBack)));
                }
                componentTag = componentTag->NextSiblingElement();
            }
            childTag = childTag->NextSiblingElement();
        }
        entryTag = entryTag->NextSiblingElement();
    }
}
