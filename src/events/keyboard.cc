#include "keyboard.h"

bool Keyboard::IsKeyPressed(int key){
    std::vector<int>::iterator it = std::find(m_Keys.begin(), m_Keys.end(), key);
    return it != m_Keys.end();
}

void Keyboard::SetKeyPressed(int key){
    if(!IsKeyPressed(key)){
        m_Keys.push_back(key);
    }
}

void Keyboard::SetKeyReleased(int key){
    if(IsKeyPressed(key)){
        std::vector<int>::iterator it = std::find(m_Keys.begin(), m_Keys.end(), key);
        m_Keys.erase(it);
    }
}