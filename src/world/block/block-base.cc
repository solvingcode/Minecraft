#include "block-base.h"

BlockBase* BlockBase::m_Instance = nullptr;

BlockBase::BlockBase(){
    m_Blocks[BlockType::Grass] = new BlockProps("grass");
    m_Blocks[BlockType::Water] = new BlockProps("water");
    m_Blocks[BlockType::Dirt] = new BlockProps("dirt");
    m_Blocks[BlockType::Stone] = new BlockProps("stone");
    m_Blocks[BlockType::Wood] = new BlockProps("wood");
    m_Blocks[BlockType::Leaf] = new BlockProps("leaf");
    m_Blocks[BlockType::Plant] = new BlockProps("plant");
    m_Blocks[BlockType::Sand] = new BlockProps("sand");
    m_Blocks[BlockType::FlowerYellow] = new BlockProps("flower-yellow");
    m_Blocks[BlockType::Cloud] = new BlockProps("cloud");
    m_Blocks[BlockType::Sun] = new BlockProps("sun");
    m_Blocks[BlockType::Moon] = new BlockProps("moon");
}

BlockBase* BlockBase::Get(){
    if(BlockBase::m_Instance == nullptr){
        BlockBase::m_Instance = new BlockBase();
    }
    return BlockBase::m_Instance;
}

BlockProps BlockBase::GetBlockProps(BlockType type){
    return *m_Blocks[(int)type];
}