//
//  TinyViewPort.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyViewPort_h
#define proj_mac_TinyViewPort_h

#include "TinyObject.h"
#include "kazmath/kazmath.h"

namespace Tiny
{
    class TinyRenderTarget;
    class TinyCamera;
    
    class TinyViewPort : public TinyObject
    {
    public:
        TinyViewPort(TinyCamera *cam, TinyRenderTarget *target, float left, float bottom, float width, float height, int zOrder);
        virtual ~TinyViewPort();
        TinyRenderTarget *getRenderTarget();
        void update();
        void updateDimensions();
        kmVec2 geViewPortLeftBottom();
        kmVec2 getViewPortSize();
    protected:
        kmVec2 mLeftBottomPosition;
        kmVec2 mRealLeftBottomPosition;
        kmVec2 mSize;
        kmVec2 mRealSize;
        TinyCamera *mCamera;
        int mZorder;
        TinyRenderTarget* mTarget;
    };
}

#endif
