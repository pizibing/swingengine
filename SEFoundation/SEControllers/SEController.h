// Swing Engine Version 1 Source Code 
// Most of techniques in the engine are mainly based on David Eberly's
// Wild Magic 4 open-source code.The author of Swing Engine learned a lot
// from Eberly's experience of architecture and algorithm.
// Several sub-systems are totally new,and others are re-implimented or
// re-organized based on Wild Magic 4's sub-systems.
// Copyright (c) 2007-2010.  All Rights Reserved
//
// Eberly's permission:
// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// the location:
// http://www.gnu.org/copyleft/lgpl.html

#ifndef Swing_Controller_H
#define Swing_Controller_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:控制器类
// 说明:
// 作者:Sun Che
// 时间:20080327
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Controller : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    virtual ~Controller(void);

    // 获取被控制的对象
    inline Object* GetObject(void) const;

    // 派生类需实现此函数
    virtual bool Update(double dAppTime);

    enum RepeatType
    {
        RT_CLAMP,
        RT_WRAP,
        RT_CYCLE,
        RT_COUNT
    };

    RepeatType Repeat;  // default = RT_CLAMP
    double MinTime;     // default = 0.0
    double MaxTime;     // default = 0.0
    double Phase;       // default = 0.0
    double Frequency;   // default = 1.0
    bool Active;        // default = true

protected:
    // 虚基类
    Controller(void);

    friend class Object;
    // 重载后,派生类可对其所期望的被控制对象进行类型识别.
    virtual void SetObject(Object* pObject);

    // 从application时间单位到controller时间单位的转换.
    // 派生类在其update函数中可以使用这个函数.
    double GetControlTime(double dAppTime);

    // 常规指针指向被控制的object,避免object和controller的smart pointer互指问题
    Object* m_pObject;

    double m_dLastAppTime;

private:
    static const char* ms_pRepeatType[RT_COUNT];
};

typedef SmartPointer<Controller> ControllerPtr;

#include "SEController.inl"

}

#endif
