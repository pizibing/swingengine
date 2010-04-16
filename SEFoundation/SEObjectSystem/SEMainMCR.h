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

#ifndef Swing_MainMCR_H
#define Swing_MainMCR_H

// 使用者必须实现各自的Initialize函数,该函数在应用程序pre-main期间被系统调用.
// 使用者必须实现各自的Terminate函数,该函数在应用程序post-main期间被系统调用.
//----------------------------------------------------------------------------
#define SE_DECLARE_INITIALIZE \
public: \
    static bool RegisterInitialize(void); \
    static void Initialize(void); \
private: \
    static bool ms_bInitializeRegistered
//----------------------------------------------------------------------------
#define SE_IMPLEMENT_INITIALIZE(classname) \
bool classname::ms_bInitializeRegistered = false; \
bool classname::RegisterInitialize() \
{ \
    if( !ms_bInitializeRegistered ) \
    { \
        SEMain::AddInitializer(classname::Initialize); \
        ms_bInitializeRegistered = true; \
    } \
    return ms_bInitializeRegistered; \
}
//----------------------------------------------------------------------------
#define SE_REGISTER_INITIALIZE(classname) \
static bool gs_bInitializeRegistered_##classname = \
    classname::RegisterInitialize()
//----------------------------------------------------------------------------
#define SE_INVOKE_INITIALIZE(classname) \
(void)gs_bInitializeRegistered_##classname
//----------------------------------------------------------------------------
#define SE_DECLARE_TERMINATE \
public: \
    static bool RegisterTerminate(void); \
    static void Terminate(void); \
private: \
    static bool ms_bTerminateRegistered
//----------------------------------------------------------------------------
#define SE_IMPLEMENT_TERMINATE(classname) \
bool classname::ms_bTerminateRegistered = false; \
bool classname::RegisterTerminate() \
{ \
    if( !ms_bTerminateRegistered ) \
    { \
        SEMain::AddTerminator(classname::Terminate); \
        ms_bTerminateRegistered = true; \
    } \
    return ms_bTerminateRegistered; \
}
//----------------------------------------------------------------------------
#define SE_REGISTER_TERMINATE(classname) \
static bool gs_bTerminateRegistered_##classname = \
    classname::RegisterTerminate()
//----------------------------------------------------------------------------
#define SE_INVOKE_TERMINATE(classname) \
(void)gs_bTerminateRegistered_##classname
//----------------------------------------------------------------------------

#endif
