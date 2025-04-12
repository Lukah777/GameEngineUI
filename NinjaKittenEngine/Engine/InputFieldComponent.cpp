#include "InputFieldComponent.h"
#include <SDL.h>
#include "../BLD/BleachNew.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "PositionComponent.h"

Engine::InputFieldComponent::InputFieldComponent(System* pSystem, GameObject* pGameObject, int x, int y, int w, int h)
    :Component(pSystem, pGameObject)
{
    m_cursorStartX = x;
    m_cursorStartY = y;
    m_cursorX = x;
    m_cursorY = y;
    m_width = w;
    m_height = h;

    m_pInput = pSystem->GetInput();
    pSystem->FindGameObject("InputMenu")->AddGameObject(BLEACH_NEW(GameObject("Cursor", pSystem->GetMessageSystem())));
    m_pCursor = pSystem->FindGameObject("InputMenu")->GetBackGameObject();
    m_pCursor->AddComponent("PositionComponent", BLEACH_NEW(Engine::PositionComponent(pSystem, m_pCursor, m_cursorX, m_cursorY, 0)));
    m_pCursor->AddComponent("TextComponent", BLEACH_NEW(Engine::TextComponent(pSystem, m_pCursor, m_cursor, "Assets/comicbd.ttf", 24, 0, 0, 0, m_cursorX, m_cursorY, 25, 50)));
}
bool Engine::InputFieldComponent::Update(Engine::System* pSystem)
{
    if (m_timer2 < 30)
    {
        m_timer2++;
        
    }
    else
    {
        m_timer2 = 0;
        if (m_cursor == "|")
        {
            m_cursor = " ";
        }
        else
        {
            m_cursor = "|";
        }
        TextComponent* cursorText = static_cast<TextComponent*>(m_pCursor->GetComponent("TextComponent"));
        cursorText->ReloadText(pSystem, m_cursor);
    }
    

    if (m_newChar != "")
    {
        if (m_timer < 5)
        {           
            m_timer++;
            return true;
        }
        else
        {
            m_newChar = "";
            m_timer = 0;
        }
    }
    

    for (int i = 4; i <= 56; i++)
    {
        if (m_pInput->GetIsKeyDown(i))
        {
            if (i == 4)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "A";
                else
                    m_newChar = "a";
            }
            else if (i == 5)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "B";
                else
                    m_newChar = "b";
            }
            else if (i == 6)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "C";
                else
                    m_newChar = "c";
            }
            else if (i == 7)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "D";
                else
                    m_newChar = "d";
            }
            else if (i == 8)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "E";
                else
                    m_newChar = "e";
            }
            else if (i == 9)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "F";
                else
                    m_newChar = "f";
            }
            else if (i == 10)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "G";
                else
                    m_newChar = "g";
            }
            else if (i == 11)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "H";
                else
                    m_newChar = "h";
            }
            else if (i == 12)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "I";
                else
                    m_newChar = "i";
            }
            else if (i == 13)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "J";
                else
                    m_newChar = "j";
            }
            else if (i == 14)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "K";
                else
                    m_newChar = "k";
            }
            else if (i == 15)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "L";
                else
                    m_newChar = "l";
            }
            else if (i == 16)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "M";
                else
                    m_newChar = "m";
            }
            else if (i == 17)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "N";
                else
                    m_newChar = "n";
            }
            else if (i == 18)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "O";
                else
                    m_newChar = "o";
            }
            else if (i == 19)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "P";
                else
                    m_newChar = "p";
            }
            else if (i == 20)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "Q";
                else
                    m_newChar = "q";
            }
            else if (i == 21)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "R";
                else
                    m_newChar = "r";
            }
            else if (i == 22)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "S";
                else
                    m_newChar = "s";
            }
            else if (i == 23)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "T";
                else
                    m_newChar = "t";
            }
            else if (i == 24)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "U";
                else
                    m_newChar = "u";
            }
            else if (i == 25)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "V";
                else
                    m_newChar = "v";
            }
            else if (i == 26)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "W";
                else
                    m_newChar = "w";
            }
            else if (i == 27)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "X";
                else
                    m_newChar = "x";
            }
            else if (i == 28)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "Y";
                else
                    m_newChar = "y";
            }
            else if (i == 29)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "Z";
                else
                    m_newChar = "z";
            }
            else if (i == 30)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "!";
                else
                    m_newChar = "1";
            }
            else if (i == 31)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "@";
                else
                    m_newChar = "2";
            }
            else if (i == 32)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "#";
                else
                    m_newChar = "3";
            }
            else if (i == 33)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "$";
                else
                    m_newChar = "4";
            }
            else if (i == 34)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "%";
                else
                    m_newChar = "5";
            }
            else if (i == 35)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "^";
                else
                    m_newChar = "6";
            }
            else if (i == 36)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "&";
                else
                    m_newChar = "7";
            }
            else if (i == 37)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "*";
                else
                    m_newChar = "8";
            }
            else if (i == 38)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "(";
                else
                    m_newChar = "9";
            }
            else if (i == 39)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = ")";
                else
                    m_newChar = "0";
            }
            else if (i == 42)
            {
                m_cursorX -= 25;

                if (m_cursorX < m_cursorStartX)
                {
                    m_cursorY -= 50;
                    m_cursorX = 575;
                }
                if (m_cursorY < m_cursorStartY)
                {
                    m_cursorX = m_cursorStartX;
                    m_cursorY = m_cursorStartY;
                }

                GameObject* pGameObjectChildBack = pSystem->FindGameObject("InputMenu")->GetBackGameObject();
                if (pGameObjectChildBack->GetName() == "InputChar")
                {
                    BLEACH_DELETE(pGameObjectChildBack);
                    pSystem->FindGameObject("InputMenu")->RemoveGameObject();
                    if (m_inputStr.size() > 0)
                        m_inputStr.pop_back();
                }
               
            }
            else if (i == 44)
                m_newChar = " ";
            else if (i == 45)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "_";
                else
                    m_newChar = "-";
            }
            else if (i == 46)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "+";
                else
                    m_newChar = "=";
            }            
            else if (i == 47)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "{";
                else
                    m_newChar = "[";
            }
            else if (i == 48)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "}";
                else
                    m_newChar = "]";
            }
            else if (i == 49)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "|";
                else
                    m_newChar = "\\";
            }
            else if (i == 51)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = ":";
                else
                    m_newChar = ";";
            }
            else if (i == 52)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "'";
                else
                    m_newChar = "\"";
            }
            else if (i == 53)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "~";
                else
                    m_newChar = "`";
            }
            else if (i == 54)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = ">";
                else
                    m_newChar = ",";
            }
            else if (i == 55)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = ">";
                else
                    m_newChar = ".";
            }
            else if (i == 46)
            {
                if (m_pInput->GetIsKeyDown(225) || m_pInput->GetIsKeyDown(229))
                    m_newChar = "?";
                else
                    m_newChar = "/";
            }

            if ((m_newChar != "" ) && m_cursorY < 550 && m_cursorY >= m_cursorStartY)
            {
                pSystem->FindGameObject("InputMenu")->AddGameObject(BLEACH_NEW(GameObject("InputChar", pSystem->GetMessageSystem())));
                GameObject* pGameObjectChildBack = pSystem->FindGameObject("InputMenu")->GetBackGameObject();
                pGameObjectChildBack->AddComponent("PositionComponent", BLEACH_NEW(Engine::PositionComponent(pSystem, pGameObjectChildBack, m_cursorX, m_cursorY, 0)));
                pGameObjectChildBack->AddComponent("TextComponent", BLEACH_NEW(Engine::TextComponent(pSystem, pGameObjectChildBack, m_newChar, "Assets/comicbd.ttf", 24, 0, 0, 0, m_cursorX, m_cursorY, 25, 50)));
                m_charGameObjects.push_back(pGameObjectChildBack);
                m_cursorX += 25;

                if (m_cursorX > m_width)
                {
                    m_cursorY += 50;
                    m_cursorX = m_cursorStartX;
                    for (int i = m_charGameObjects.size()-1; i >= 0; i--)
                    {
                        TextComponent* text = static_cast<TextComponent*>(m_charGameObjects[i]->GetComponent("TextComponent"));
                        if (text->GetToken() == " ")
                        {
                            for (int k = i + 1; k < m_charGameObjects.size(); k++)
                            {
                                PositionComponent* pos = static_cast<PositionComponent*>(m_charGameObjects[k]->GetComponent("PositionComponent"));
                                TextComponent* text = static_cast<TextComponent*>(m_charGameObjects[k]->GetComponent("TextComponent"));
                                pos->SetXY(m_cursorX, m_cursorY);
                                text->GetMsgRect()->x = m_cursorX;
                                text->GetMsgRect()->y = m_cursorY;
                                m_cursorX += 25;
                            }
                            break;
                        }
                    }
                }

                m_inputStr += m_newChar;
            }

            PositionComponent* cursorPos = static_cast<PositionComponent*>(m_pCursor->GetComponent("PositionComponent"));
            TextComponent* cursorText = static_cast<TextComponent*>(m_pCursor->GetComponent("TextComponent"));
            cursorPos->SetXY(m_cursorX, m_cursorY);
            cursorText->GetMsgRect()->x = m_cursorX;
            cursorText->GetMsgRect()->y = m_cursorY;
            break;

        }
    }

    return true;
}