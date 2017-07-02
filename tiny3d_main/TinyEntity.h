//
//  TinyEntity.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyEntity_h
#define proj_mac_TinyEntity_h

#include <vector>
#include <string>
#include "TinyObject.h"
#include "TinyPlatform.h"
#include "TinyMovableObject.h"
#include "TinySkeleton.h
#include "TinyAnimationState.h"

namespace Tiny
{
    class TinyRenderQueue;
    class TinySubEntity;
    class TinyMesh;
    class TinyMaterial;
    class TinyNode;
    class TinyNameGenerator;
    
    class TinyEntity : public TinyMovableObject
    {
    public:
        typedef std::vector<TinySubEntity*> SubEntityList;
        TinyEntity(const std::string& name, TinyMesh* mesh);
        TinyEntity(TinyMesh* mesh);
        ~TinyEntity();
        void initialize();
        void updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue);
        void setRenderQueueGroupID(uint8 groupID);
        void setRenderPriority(uint8 priority);
        void setMaterial(TinyMaterial* material);
        void buildSubEntityList(TinyMesh* mesh, SubEntityList* list);
        void getModelMatrix(kmMat4& mat);
        TinySubEntity* getSubEntity(uint32 index);
        TinySkeleton* getSkeleton(){return mSkeletonInstance};
        bool hasSkeleton(){return mSkeletonInstance != NULL;}
        void updateAnimation();
    protected:
        SubEntityList mSubEntitys;
        uint8 mRenderQueueGroupID;
        uint8 mRenderPriority;
        TinyMesh* mMesh;
        TinyMaterial* mMaterial;
        static TinyNameGenerator mNameGenerator;
        TinySkeleton* mSkeletonInstance;
        TinyAnimationStateSet* mAnimationState;
        
    };
}

#endif
