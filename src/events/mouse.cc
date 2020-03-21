#include "mouse.h"

bool Mouse::IsButtonPressed(MouseButton key){
    std::vector<MouseButton>::iterator it = std::find(m_Keys.begin(), m_Keys.end(), key);
    return it != m_Keys.end();
}

void Mouse::SetButtonPressed(MouseButton key){
    if(!IsButtonPressed(key)){
        m_Keys.push_back(key);
    }
}

void Mouse::SetButtonReleased(MouseButton key){
    if(IsButtonPressed(key)){
        std::vector<MouseButton>::iterator it = std::find(m_Keys.begin(), m_Keys.end(), key);
        m_Keys.erase(it);
    }
}