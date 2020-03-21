#include "tree.h"
#include "world/chunk/superchunk.h"

void Tree::GenerateOak(SuperChunk& chunk, glm::vec3 tree){
    Random rand = Random::Get();
    int height = rand.GetIntInRange(4, 8);
    
    for(int y = 0; y <= height; y++){
        chunk.SetBlock(tree.x, tree.y + y, tree.z, BlockType::Wood);
    }

    rand.SetSeed(tree.x + tree.z);
    int heightLeaf = rand.GetIntInRange(4, 6);
    for(int iHeightLeaf = 0; iHeightLeaf < heightLeaf; iHeightLeaf++){
        rand.SetSeed(tree.x + tree.z + iHeightLeaf);
        int leafSize;
        if(iHeightLeaf < heightLeaf / 2){
            leafSize = iHeightLeaf + 1;
        }else{
            leafSize = heightLeaf - iHeightLeaf;
        }
        for(int zleaf = -leafSize; zleaf < leafSize; zleaf++){
            for(int xleaf = -leafSize; xleaf < leafSize; xleaf++){
                chunk.SetBlock(
                    tree.x + xleaf, 
                    tree.y + height + iHeightLeaf, 
                    tree.z + zleaf, 
                    xleaf == 0 && zleaf == 0 && iHeightLeaf < heightLeaf - 1 ? BlockType::Wood : BlockType::Leaf
                );
            }
        }
    }
}