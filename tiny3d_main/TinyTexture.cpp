//
//  TinyTexture.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyTexture.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinyTexture::TinyTexture()
        : mHandler(0)
    {
        
    }
    
    TinyTexture::~TinyTexture()
    {
        
    }
    
    void TinyTexture::load(uint8* data, uint32 length, bool genMipmap)
    {
        TinyImage* image = TINY_NEW TinyImage();
        image->initWithData(data, length, false);
        initWithImage(image, genMipmap);
        TINY_DELETE image;
    }
    
    void TinyTexture::load(std::vector<uint8*>& datas, std::vector<uint32>& lengths, bool genMipmap)
    {
        uint32 length = (uint32)datas.size();
        std::vector<TinyImage*> images;
        for (int i = 0; i < length; i ++)
        {
            TinyImage* image = TINY_NEW TinyImage();
            image->initWithData(datas[i], lengths[i], genMipmap);
            images.push_back(image);
        }
        initWithImages(images, genMipmap);
        for (int i = 0; i < length; i ++)
        {
            TINY_DELETE images[i];
        }
    }
    
    void TinyTexture::initWithImage(TinyImage* image, bool genMipmap)
    {
        if (mHandler == 0)
        {
            TinyImage::DataList& dataList = image->mDataList;
            TinyImage::SizeList& sizeList = image->mSizeList;
            //glPixelStorei(GL_UNPACK_ALIGNMENT,4);
            glGenTextures(1, &mHandler);
            
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, mHandler);
            
            uint32 mipMapCount = (uint32)image->mDataList.size();
            for (int i = 0; i < mipMapCount; i ++)
            {
                uint32 width = sizeList[i].x;
                uint32 height = sizeList[i].y;
                glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataList[i]);
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            if (genMipmap == false)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            glDisable(GL_TEXTURE_2D);
        }
    }
    
    void TinyTexture::initWithImages(std::vector<TinyImage*>& images, bool genMipmap)
    {
        if (mHandler == 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_CUBE_MAP);
            glGenTextures(1, &mHandler);
            glBindTexture(GL_TEXTURE_CUBE_MAP, mHandler);
            
            for (int cubeIdx = 0; cubeIdx < 6; cubeIdx ++)
            {
                TinyImage::DataList& dataList = images[cubeIdx]->mDataList;
                TinyImage::SizeList& sizeList = images[cubeIdx]->mSizeList;
                
                uint32 mipMapCount = (uint32)dataList.size();
                for (int i = 0; i < mipMapCount; i ++)
                {
                    uint32 width = sizeList[i].x;
                    uint32 height = sizeList[i].y;
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + cubeIdx, i, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataList[i]);
                }
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            if (genMipmap == false)
            {
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
            }
            glDisable(GL_TEXTURE_CUBE_MAP);
        }
    }
    
    const GLuint& TinyTexture::getHandler()
    {
        return mHandler;
    }
}