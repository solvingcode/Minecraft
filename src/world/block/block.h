#pragma once
#include "block-base.h"

class Block{
public:
    Block(): m_Active(true), m_Focus(false), m_Type(BlockType::Air){}
    Block(BlockType type): m_Active(true), m_Focus(false), m_Type(type){}
    ~Block(){}
    
    bool IsActive() { return m_Active; }
    bool IsFocus() { return m_Focus; }
    void SetActive(bool active);
    void SetBlockType(BlockType type);
    void SetFocus(bool focus);
    BlockType GetType() {return m_Type;}
    BlockProps GetProps();

private:
    bool m_Active;
    bool m_Focus;
    BlockType m_Type;
};