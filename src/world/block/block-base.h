#pragma once
#include "block-type.h"
#include "block-props.h"

class BlockBase{
public:
    static BlockBase* Get();
    BlockProps GetBlockProps(BlockType type);
private:
    BlockBase();
    std::array<BlockProps*, BlockType::SIZE> m_Blocks;
    static BlockBase* m_Instance;
};