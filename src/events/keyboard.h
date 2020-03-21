#pragma once
#include <vector>
#include <algorithm>

class Keyboard{

public:
    Keyboard() = default;
    bool IsKeyPressed(int key);
    void SetKeyPressed(int key);
    void SetKeyReleased(int key);
private:
    std::vector<int> m_Keys;
};