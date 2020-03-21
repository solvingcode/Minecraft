struct EventKeyboard{
    int m_Key, m_Scancode;
    EventKeyboard(int key, int scancode): m_Key(key), m_Scancode(scancode){}
    EventKeyboard(): m_Key(0), m_Scancode(0){}
};