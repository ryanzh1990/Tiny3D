//
//  TinySceneManager.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinySceneManager_h
#define proj_mac_TinySceneManager_h

#include <vector>
#include <string>
#include "TinyObject.h"
#include "kazmath/kazmath.h"
#include "TinyAutoParamDataSource.h"
#include "TinyPrerequisite.h"

namespace Tiny
{
    class TinySceneManager : public TinyObject
    {
    public:
        TinySceneManager();
        virtual ~TinySceneManager();
        void renderScene(TinyCamera *cam);
        void findVisibleObjects(TinyCamera *cam);
        void renderVisibleObjects();
        void updateSceneGraph();
        void renderQueueGroupObjects(TinyRenderQueueGroup* group);
        void renderObjects(TinyRenderableCollection* collection);
        void renderSingleObject(TinyRenderable* renderable);
        void updateGpuProgramParameters(TinyRenderOperation& ro);
        void setViewPort(TinyViewPort *vp);
        void setProjectionMatrix(kmMat4& matrix);
        void setViewMatrix(kmMat4& matrix);
        void setModelMatrix(kmMat4& matrix);
        void setEyePositionModelSpace(const kmVec3& position);
        TinySceneNode* getRootSceneNode();
        TinyRenderQueue* getRenderQueue();
        void clearBg();
        TinyCamera* createCamera(const std::string& name);
    private:
        typedef std::vector<TinyCamera*> CameraList;
        TinyViewPort *mCurrentViewPort;
        TinyCamera *mCameraInProgress;
        TinySceneNode* mSceneRoot;
        TinyRenderSystem* mDestRenderSystem;
        TinyRenderQueue* mRenderQueue;
        TinyAutoParamDataSource mAutoParamDataSource;
        CameraList mCameraList;
    };
}

#endif
