//
//  TinyGPUProgram.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyGPUProgram.h"
#include "TinyMemoryAlloc.h"
#include "TinyPlatform.h"

namespace Tiny
{
    TinyGPUProgram::TinyGPUProgram(const std::string& vs, const std::string& fs)
        : mParams(TINY_NEW TinyGPUProgramParameters())
        , mHandler(0)
        , mVertexShaderSource(vs)
        , mFragmentShaderSource(fs)
    {
        //
    }
    
    TinyGPUProgram::~TinyGPUProgram()
    {
        TINY_DELETE mParams;
    }
    
    void TinyGPUProgram::load()
    {
        
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        GLint result = GL_FALSE;
        int infoLogLength;
        char *shaderInfoMessage = nullptr;
        char *programInfoMessage = nullptr;
        
        // Compile Vertex Shader
        const char* vSourceStr = mVertexShaderSource.c_str();
        glShaderSource(vertexShader, 1, &vSourceStr, NULL);
        glCompileShader(vertexShader);
        
        // Check Vertex Shader
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            shaderInfoMessage = (char *)malloc(infoLogLength + 1);
            glGetShaderInfoLog(vertexShader, infoLogLength, NULL, shaderInfoMessage);
            TINYLOG("vertex shder info: %s", shaderInfoMessage);
            free(shaderInfoMessage);
        }
        assert(result && "vertex shader error");
        
        // Compile Fragment Shader
        const char* fSourceStr = mFragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &fSourceStr , NULL);
        glCompileShader(fragmentShader);
        //TINYLOG("f:%s", vSourceStr);
        
        // Check Fragment Shader
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            shaderInfoMessage = (char *)malloc(infoLogLength + 1);
            glGetShaderInfoLog(fragmentShader, infoLogLength, NULL, shaderInfoMessage);
            TINYLOG("fragment shder info: %s", shaderInfoMessage);
            free(shaderInfoMessage);
        }
        assert(result && "fragment shader error");
        
        // Link the program
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        
        // Check the program
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            programInfoMessage = (char *)malloc(infoLogLength + 1);
            glGetProgramInfoLog(program, infoLogLength, NULL, programInfoMessage);
            TINYLOG("program info: %s", programInfoMessage);
            free(programInfoMessage);
        }
        assert(result && "shader link error");
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        mHandler = program;
    }
    
    void TinyGPUProgram::useProgram()
    {
        glUseProgram(mHandler);
        mParams->bindParametersToProgram(mHandler);
    }
    
    void TinyGPUProgram::setParameter(const TinyGPUProgramParameter& value)
    {
        mParams->setParameter(value);
    }
    
    TinyGPUProgramParameters* TinyGPUProgram::getGPUProgramParameters()
    {
        return mParams;
    }
    
    GLuint TinyGPUProgram::getHandler()
    {
        return mHandler;
    }
    
    TinyGPUProgramParameters::TinyGPUProgramParameters()
    {
        //
    }
    
    TinyGPUProgramParameters::~TinyGPUProgramParameters()
    {
        //
    }
    
    void TinyGPUProgramParameters::setParameter(const TinyGPUProgramParameter& value)
    {
        mParams[value.mName] = value;
    }
    
    void TinyGPUProgramParameters::updateAutoParams(TinyAutoParamDataSource* autoPram)
    {
        const kmMat4& projMatrix = autoPram->getProjectionMatrix();
        setParameter(TinyGPUProgramParameter("projMatrix", GP_MATRIX_4X4, &projMatrix));
        
        const kmMat4& viewMatrix = autoPram->getViewMatrix();
        setParameter(TinyGPUProgramParameter("viewMatrix", GP_MATRIX_4X4, &viewMatrix));
        
        const kmMat4& modelMatrix = autoPram->getModelMatrix();
        setParameter(TinyGPUProgramParameter("modelMatrix", GP_MATRIX_4X4, &modelMatrix));
        
        const kmVec3& eyePositionModelSpace = autoPram->getEyePositionModelSpace();
        setParameter(TinyGPUProgramParameter("eyePositionModelSpace", GP_FLOAT3, &eyePositionModelSpace));
    }
    
    void TinyGPUProgramParameters::bindParametersToProgram(GLuint program)
    {
        auto iter = mParams.begin();
        uint8 textureCnter = 0;
        for (; iter != mParams.end(); iter ++)
        {
            iter->second.calcLocation(program);
            GLint location = iter->second.mLocation;
            if (location >= 0)
            {
                switch (iter->second.mType)
                {
                    case GP_FLOAT1:
                    {
                        glUniform1fv(location, 1, (GLfloat*)iter->second.mBindData);
                        break;
                    }
                    case GP_FLOAT2:
                    {
                        glUniform2fv(location, 1, (GLfloat*)iter->second.mBindData);
                        break;
                    }
                    case GP_FLOAT3:
                    {
                        glUniform3fv(location, 1, (GLfloat*)iter->second.mBindData);
                        break;
                    }
                    case GP_FLOAT4:
                    {
                        glUniform4fv(location, 1, (GLfloat*)iter->second.mBindData);
                        break;
                    }
                    case GP_INT1:
                    {
                        glUniform1iv(location, 1, (GLint*)iter->second.mBindData);
                        break;
                    }
                    case GP_INT2:
                    {
                        glUniform2iv(location, 1, (GLint*)iter->second.mBindData);
                        break;
                    }
                    case GP_INT3:
                    {
                        glUniform3iv(location, 1, (GLint*)iter->second.mBindData);
                        break;
                    }
                    case GP_INT4:
                    {
                        glUniform4iv(location, 1, (GLint*)iter->second.mBindData);
                        break;
                    }
                    case GP_MATRIX_3X3:
                    {
                        glUniformMatrix3fv(location, 1, GL_FALSE, (GLfloat*)iter->second.mBindData);
                        break;
                    }
                    case GP_MATRIX_4X4:
                    {
                        //TODO
                        #include "kazmath/kazmath.h"
                        kmMat4* mat;
                        mat = (kmMat4*)iter->second.mBindData;
                        glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)iter->second.mBindData);
                        break;
                    }
                    case GP_SAMPLER:
                    {
                        glActiveTexture(GL_TEXTURE0 + textureCnter);
                        glEnable(GL_TEXTURE_2D);
                        auto textureID = *(GLuint*)iter->second.mBindData;
                        glBindTexture(GL_TEXTURE_2D, textureID);
                        glUniform1i(location, textureCnter);
                        ++ textureCnter;
                        break;
                    }
                    case GP_SAMPLERCUBE:
                    {
                        glActiveTexture(GL_TEXTURE0 + textureCnter);
                        glEnable(GL_TEXTURE_CUBE_MAP);
                        auto textureID = *(GLuint*)iter->second.mBindData;
                        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
                        glUniform1i(location, textureCnter);
                        ++ textureCnter;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
    
    TinyGPUProgramParameter::TinyGPUProgramParameter()
        : mBindData(nullptr)
        , mType(GP_UNDEFINE)
        , mLocation(0)
    {
        
    }
    
    TinyGPUProgramParameter::TinyGPUProgramParameter(const std::string& name,
                                                     TinyGPUProgramParameterType type,
                                                     const void* data)
    {
        mName = name;
        mType = type;
        if (data)
        {
            uint32 size = getDataSizeByType(type);
            mBindData = malloc(size);
            memcpy(mBindData, data, size);
        }
        mLocation = 0;
    }
    
    TinyGPUProgramParameter::~TinyGPUProgramParameter()
    {
        if (mBindData)
        {
            free(mBindData);
        }
    }
    
    TinyGPUProgramParameter& TinyGPUProgramParameter::operator = (const TinyGPUProgramParameter& param)
    {
        mType = param.mType;
        mName = param.mName;
        mLocation = param.mLocation;
        uint32 length = getDataSizeByType(mType);
        mBindData = malloc(length);
        memcpy(mBindData, param.mBindData, length);
        return *this;
    }
    
    uint32 TinyGPUProgramParameter::getDataSizeByType(TinyGPUProgramParameterType type)
    {
        uint32 ret = 0;
        switch (type) {
            case GP_FLOAT1:
                ret = sizeof(float);
                break;
            case GP_FLOAT2:
                ret = sizeof(float) * 2;
                break;
            case GP_FLOAT3:
                ret = sizeof(float) * 3;
                break;
            case GP_FLOAT4:
                ret = sizeof(float) * 4;
                break;
            case GP_INT1:
                ret = sizeof(int32) * 1;
                break;
            case GP_INT2:
                ret = sizeof(int32) * 2;
                break;
            case GP_INT3:
                ret = sizeof(int32) * 3;
                break;
            case GP_INT4:
                ret = sizeof(int32) * 4;
                break;
            case GP_MATRIX_3X3:
                ret = sizeof(float) * 9;
                break;
            case GP_MATRIX_4X4:
                ret = sizeof(float) * 16;
                break;
            case GP_SAMPLER:
                ret = sizeof(int32);
                break;
            case GP_SAMPLERCUBE:
                ret = sizeof(int32);
                break;
            default:
                break;
        }
        return ret;
    }
    
    void TinyGPUProgramParameter::calcLocation(GLuint program)
    {
        const GLchar* nameStr = mName.c_str();
        mLocation = glGetUniformLocation(program, nameStr);
    }
}




