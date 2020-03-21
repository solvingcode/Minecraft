#pragma once
#include <vector>
#include <algorithm>

enum MouseButton{
    LEFT,
    RIGHT
};

class Mouse{

public:
    Mouse() = default;
    bool IsButtonPressed(MouseButton key);
    void SetButtonPressed(MouseButton key);
    void SetButtonReleased(MouseButton key);
private:
    std::vector<MouseButton> m_Keys;
};