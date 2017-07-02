//
//  TinyTextureController.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//
#ifndef proj_mac_TinyTextureManager_h
#define proj_mac_TinyTextureManager_h

#include <string>
#include <vector>
#include "TinyResourceManager.h"
#include "TinyTexture.h"
#include "TinySingleton.h"

namespace Tiny
{
    class TinyTextureManager : public TinyResourceManager, public TinySingleton<TinyTextureManager>
    {
    public:
        TinyTextureManager();
        virtual ~TinyTextureManager();
        TinyTexture* load(const std::string& fileName, bool genMipmap);
        TinyTexture* load(const std::vector<std::string>& fileNames, bool genMipmap);
        
    };
}
#endif