struct EventMouseMotion{
    double m_Xpos;
    double m_Ypos;
    EventMouseMotion(): m_Xpos(0), m_Ypos(0){}
    EventMouseMotion(double xpos, double ypos): m_Xpos(xpos), m_Ypos(ypos){}
};