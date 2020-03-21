#include "block-props.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace{
    struct AttributeBlockFile
    {
        static std::string Id;
        static std::string TexTop;
        static std::string TexBottom;
        static std::string TexSide;
        static std::string TexAll;
        static std::string Type;
        static std::string Collidable;
        static std::string Opaque;
    };
    std::string AttributeBlockFile::Id = "Id";
    std::string AttributeBlockFile::TexTop = "TexTop";
    std::string AttributeBlockFile::TexBottom = "TexBottom";
    std::string AttributeBlockFile::TexSide = "TexSide";
    std::string AttributeBlockFile::TexAll = "TexAll";
    std::string AttributeBlockFile::Type = "Type";
    std::string AttributeBlockFile::Collidable = "Collidable";
    std::string AttributeBlockFile::Opaque = "Opaque";
};

//@TODO : Optimize function
BlockProps::BlockProps(const std::string block){
    std::ifstream stream("res/blocks/" + block + ".block");
    int atlasNumEl = 10;
    
    if(!stream.is_open()){
        std::cout << "Unable to open file " << block.c_str() << std::endl;
        exit(EXIT_FAILURE);
    }

    float minX = 0.001f;
    float maxX = 0.099f;
    float minY = 0.001f;
    float maxY = 0.099f;

    std::string line;
    while(getline(stream, line)){
        std::stringstream ss;
        if(line.find(AttributeBlockFile::Id + ":") == 0){
            int id;
            line.replace(0, AttributeBlockFile::Id.size() + 1, "");
            ss << line;
            ss >> id;
            //m_Id = static_cast<BlockType>(id);
        }else if(line.find(AttributeBlockFile::TexTop + ":") == 0){
            int x, y;
            line.replace(0, AttributeBlockFile::TexTop.size() + 1, "");
            ss << line;
            ss >> y >> x;
            float indexX = ((float)x)/atlasNumEl;
            float indexY = ((float)y)/atlasNumEl;
            m_TexCoords.top = {
                indexX + minX, indexY + minY,
                indexX + maxX, indexY + minY,
                indexX + maxX, indexY + maxY,
                indexX + minX, indexY + maxY
            };
        }else if(line.find(AttributeBlockFile::TexBottom + ":") == 0){
            int x, y;
            line.replace(0, AttributeBlockFile::TexBottom.size() + 1, "");
            ss << line;
            ss >> y >> x;
            float indexX = ((float)x)/atlasNumEl;
            float indexY = ((float)y)/atlasNumEl;
            m_TexCoords.bottom = {
                indexX + minX, indexY + maxY,
                indexX + maxX, indexY + maxY,
                indexX + maxX, indexY + minY,
                indexX + minX, indexY + minY
            };
        }else if(line.find(AttributeBlockFile::TexSide + ":") == 0){
            int x, y;
            line.replace(0, AttributeBlockFile::TexSide.size() + 1, "");
            ss << line;
            ss >> y >> x;
            float indexX = ((float)x)/atlasNumEl;
            float indexY = ((float)y)/atlasNumEl;
            m_TexCoords.front = m_TexCoords.back = {
                indexX + minX, indexY + minY,
                indexX + maxX, indexY + minY,
                indexX + maxX, indexY + maxY,
                indexX + minX, indexY + maxY
            };
            m_TexCoords.left = {
                indexX + maxX, indexY + maxY,
                indexX + minX, indexY + maxY,
                indexX + minX, indexY + minY,
                indexX + maxX, indexY + minY
            };
            m_TexCoords.right = {
                indexX + minX, indexY + maxY,
                indexX + maxX, indexY + maxY,
                indexX + maxX, indexY + minY,
                indexX + minX, indexY + minY
            };
        }else if(line.find(AttributeBlockFile::TexAll + ":") == 0){
            int x, y;
            line.replace(0, AttributeBlockFile::TexAll.size() + 1, "");
            ss << line;
            ss >> y >> x;
            float indexX = ((float)x)/atlasNumEl;
            float indexY = ((float)y)/atlasNumEl;
            m_TexCoords.front = m_TexCoords.back = m_TexCoords.left = m_TexCoords.right = m_TexCoords.top = m_TexCoords.bottom = {
                indexX + minX, indexY + minY,
                indexX + maxX, indexY + minY,
                indexX + maxX, indexY + maxY,
                indexX + minX, indexY + maxY
            };
        }else if(line.find(AttributeBlockFile::Type + ":") == 0){
            int type;
            line.replace(0, AttributeBlockFile::Type.size() + 1, "");
            ss << line;
            ss >> type;
            m_MeshType = static_cast<BlockMeshType>(type);
        }else if(line.find(AttributeBlockFile::Collidable + ":") == 0){
            bool collidable;
            line.replace(0, AttributeBlockFile::Collidable.size() + 1, "");
            ss << line;
            ss >> collidable;
            m_IsCollidable = collidable;
        }else if(line.find(AttributeBlockFile::Opaque + ":") == 0){
            bool opaque;
            line.replace(0, AttributeBlockFile::Opaque.size() + 1, "");
            ss << line;
            ss >> opaque;
            m_IsOpaque = opaque;
        }
    }

}