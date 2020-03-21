#include "block.h"

void Block::SetActive(bool active){
    m_Active = active;
}

void Block::SetBlockType(BlockType type){
    m_Type = type;
}

void Block::SetFocus(bool focus){
    m_Focus = focus;
}

BlockProps Block::GetProps(){
    BlockBase* blockBase = BlockBase::Get();
    return blockBase->GetBlockProps(m_Type);
}