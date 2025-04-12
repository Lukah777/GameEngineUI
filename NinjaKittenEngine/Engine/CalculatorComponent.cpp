#include "CalculatorComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <sstream>

Engine::CalculatorComponent::CalculatorComponent(System* pSystem, GameObject* pGameObject)
    :Component(pSystem, pGameObject)
{
    m_equation = " ";
}

bool Engine::CalculatorComponent::Update(System* pSystem)
{
    TextComponent* textComp = dynamic_cast<TextComponent*>(GetOwner()->GetComponent("TextComponent"));

    textComp->ReloadText(pSystem, m_equation.c_str());

    return true;
}

double Solve(std::string equation)
{
    std::stringstream equationStream(equation);

    double left = 0;
    double right = 1;
    std::string word;
    bool add = false;
    bool sub = false;
    bool mul = false;
    bool div = false;
    while (equationStream >> word)
    {
        if (word[0] == '(')
        {
            if (left == 0)
                left = Solve(equation.substr(equation.find_first_of('(') + 1, equation.find_last_of(')') - equation.find_first_of('(') - 1));
            else if (right == 0)
                right = Solve(equation.substr(equation.find_first_of('(') + 1, equation.find_last_of(')') - equation.find_first_of('(') - 1));
            else
            {
                left *= Solve(equation.substr(equation.find_first_of('(') + 1, equation.find_last_of(')') - equation.find_first_of('(') - 1));
                return left;
            }

            std::string paraenthises = equation.substr(equation.find_first_of('(') + 1, equation.find_last_of(')') - equation.find_first_of('(') - 1);
            int wordCount = 0;
            for (int i = 0; i < paraenthises.size(); i++)
            {
                if (paraenthises[i] == ' ')
                    wordCount++;
            }
            for (int i = 2; i < wordCount; i++)
            {
                equationStream >> word;
            }

            if (add || sub || mul || div)
            {
                if (add)
                    left += right;
                else if (sub)
                    left -= right;
                else if (mul)
                    left *= right;
                else if (div)
                    left /= right;

                add = false;
                sub = false;
                mul = false;
                div = false;
                return left;
            }
        }

        if (word == "+")
        {
            add = true;
            right = 0;
            continue;
        }
        else if (word == "-")
        {
            sub = true;
            right = 0;
            continue;
        }
        else if (word == "*")
        {
            mul = true;
            right = 0;
            continue;
        }
        else if (word == "/")
        {
            div = true;
            right = 0;
            continue;
        }
        else if (word == ")")
        {
            continue;
        }

        if (left == 0)
            left = stoi(word);
        else if (right == 0)
        {
            right = stoi(word);

            if (add)
                left += right;
            else if (sub)
                left -= right;
            else if (mul)
                left *= right;
            else if (div)
                left /= right;

            add = false;
            sub = false;
            mul = false;
            div = false;
        }
    }
    return left;
}

void Engine::CalculatorComponent::Calculate(char input)
{
    if (input == '=')
    {
        m_equation += ' ';

        int p1 = -1, p2 = -1;
        for (int i = 0; i < m_equation.size(); i++)
        {
            if (m_equation[i] == '*' || m_equation[i] == '/')
            {
                for (int j = i-2; j > 0; j--)
                {
                    if (m_equation[j] == ' ' && m_equation[j+1] != '(')
                    {
                        p1 = j+1;
                        break;
                    }
                }

                for (int k = i+2; k < m_equation.size(); k++)
                {
                    if (m_equation[k] == ' ' && m_equation[k - 1] != ')')
                    {
                        p2 = k+1;
                        break;
                    }
                }
                if (p1 != -1 && p2 != -1)
                {
                    m_equation.insert(m_equation.begin() + p1, '(');
                    m_equation.insert(m_equation.begin() + p2, ')');
                    i += p2 - i;
                }                
            }
        }

        std::string s = std::to_string(Solve(m_equation));
        m_equation = s;
    }
    else if (input == 'C')
    {
        m_equation.clear();
    }
    else if (input == '+')
    {
        m_equation += ' ';
        m_equation += input;
        m_equation += ' ';
    }
    else if (input == '-')
    {
        m_equation += ' ';
        m_equation += input;
        m_equation += ' ';
    }
    else if (input == '*')
    {
        m_equation += ' ';
        m_equation += input;
        m_equation += ' ';
    }
    else if (input == '/')
    {
        m_equation += ' ';
        m_equation += input;
        m_equation += ' ';
    }
    else if (input == '(')
    {
        m_equation += ' ';
        m_equation += input;
    }
    else if (input == ')')
    {
        m_equation += input;
        m_equation += ' ';
    }
    else
        m_equation += input;
}
