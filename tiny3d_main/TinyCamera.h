//
//  TinyCamera.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyCamera_h
#define proj_mac_TinyCamera_h

#include "kazmath/kazmath.h"
#include "TinyMovableObject.h"
#include <string>

class TinySceneManager;

namespace Tiny
{
    class TinySceneManager;
    class TinyObject;
    class TinyViewPort;
    class TinyRenderQueue;
    
    class TinyCamera : public TinyMovableObject
    {
    public:
        TinyCamera(const std::string &name, TinySceneManager *mgr);
        ~TinyCamera();
        void renderScene(TinyViewPort *viewPort);
        void notifyViewPort(TinyViewPort *vp);
        TinyViewPort *getViewPort();
        void getViewMatrix(kmMat4& ret);
        void getProjectionMatrix(kmMat4& ret);
        void updateRenderQueue(TinyCamera* cam, TinyRenderQueue* queue);
        void roll(float radian);
        void pitch(float radian);
        void yaw(float radian);
        void rotate(kmVec3& axis, float radian);
        const kmQuaternion& getOrientation();
        void moveRelative(const kmVec3& vec);
        const kmVec3& getDerivedPosition();
        const kmQuaternion& getDerivedOrientation();
    private:
        TinyViewPort *mLastViewPort;
        TinySceneManager *mSceneMgr;
        std::string mName;
        float mFov;
        float mAspect;
        float mNear;
        float mFar;
        kmVec3 mPosition;
        kmVec3 mDerivedPosition;
        kmQuaternion mOrientation;
        kmQuaternion mDerivedOrientation;
        kmVec3 mLocalUpDir;
        kmVec3 mLocalFrontDir;
        kmVec3 mLocalSideDir;
    };
}

#endif


