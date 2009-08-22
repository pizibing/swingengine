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

#include "SEFoundationPCH.h"
#include "SELight.h"
#include "SEMatrix3.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Light, Object);
SE_IMPLEMENT_STREAM(Light);
SE_IMPLEMENT_DEFAULT_NAME_ID(Light, Object);

//SE_REGISTER_STREAM(Light);

//----------------------------------------------------------------------------
Light::Light(LightType eType)
    :
    Type(eType),
    Ambient(0.0f, 0.0f, 0.0f),
    Diffuse(0.0f, 0.0f, 0.0f),
    Specular(0.0f, 0.0f, 0.0f),
    Position(0.0f, 0.0f, 0.0f),
    RVector(1.0f, 0.0f, 0.0f),
    UVector(0.0f, 1.0f, 0.0f),
    DVector(0.0f, 0.0f, 1.0f)
{
    Constant = 1.0f;
    Linear = 0.0f;
    Quadratic = 0.0f;
    Intensity = 1.0f;
    Angle = Mathf::PI;
    CosAngle = -1.0f;
    SinAngle = 0.0f;
    Exponent = 1.0f;
}
//----------------------------------------------------------------------------
Light::~Light()
{
}
//----------------------------------------------------------------------------
void Light::SetAngle(float fAngle)
{
    SE_ASSERT( 0.0f < fAngle && fAngle <= Mathf::PI );

    Angle = fAngle;
    CosAngle = Mathf::Cos(fAngle);
    SinAngle = Mathf::Sin(fAngle);
}
//----------------------------------------------------------------------------
void Light::SetDirection(const Vector3f& rDirection, bool bUnitLength)
{
    DVector = rDirection;
    Vector3f::GetOrthonormalBasis(UVector, RVector, DVector, bUnitLength);
}
//----------------------------------------------------------------------------
bool Light::IsValidFrame() const
{
    float fTest = DVector.Dot(UVector);
    if( Mathf::FAbs(fTest) > Mathf::ZERO_TOLERANCE )
    {
        return false;
    }

    fTest = DVector.Dot(RVector);
    if( Mathf::FAbs(fTest) > Mathf::ZERO_TOLERANCE )
    {
        return false;
    }

    fTest = UVector.Dot(RVector);
    if( Mathf::FAbs(fTest) > Mathf::ZERO_TOLERANCE )
    {
        return false;
    }

    fTest = DVector.Dot(RVector.Cross(UVector));

    return Mathf::FAbs(1.0f - fTest) <= Mathf::ZERO_TOLERANCE;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Light::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    // native data
    rStream.Read((int&)Type);
    rStream.Read(Position);
    rStream.Read(RVector);
    rStream.Read(UVector);
    rStream.Read(DVector);
    rStream.Read(Ambient);
    rStream.Read(Diffuse);
    rStream.Read(Specular);
    rStream.Read(Intensity);
    rStream.Read(Constant);
    rStream.Read(Linear);
    rStream.Read(Quadratic);
    rStream.Read(Angle);
    rStream.Read(CosAngle);
    rStream.Read(SinAngle);
    rStream.Read(Exponent);

    SE_END_DEBUG_STREAM_LOAD(Light);
}
//----------------------------------------------------------------------------
void Light::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool Light::Register(Stream& rStream) const
{
    return Object::Register(rStream);
}
//----------------------------------------------------------------------------
void Light::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    // native data
    rStream.Write((int)Type);
    rStream.Write(Position);
    rStream.Write(RVector);
    rStream.Write(UVector);
    rStream.Write(DVector);
    rStream.Write(Ambient);
    rStream.Write(Diffuse);
    rStream.Write(Specular);
    rStream.Write(Intensity);
    rStream.Write(Constant);
    rStream.Write(Linear);
    rStream.Write(Quadratic);
    rStream.Write(Angle);
    rStream.Write(CosAngle);
    rStream.Write(SinAngle);
    rStream.Write(Exponent);

    SE_END_DEBUG_STREAM_SAVE(Light);
}
//----------------------------------------------------------------------------
int Light::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Object::GetDiskUsed(rVersion) +
        sizeof(Type) +
        sizeof(Position) +
        sizeof(RVector) +
        sizeof(UVector) +
        sizeof(DVector) +
        sizeof(Ambient) +
        sizeof(Diffuse) +
        sizeof(Specular) +
        sizeof(Intensity) +
        sizeof(Constant) +
        sizeof(Linear) +
        sizeof(Quadratic) +
        sizeof(Angle) +
        sizeof(CosAngle) +
        sizeof(SinAngle) +
        sizeof(Exponent);
}
//----------------------------------------------------------------------------
StringTree* Light::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, (const char*)GetName()));
    pTree->Append(Format("type =", (int)Type));
    pTree->Append(Format("position =", Position));
    pTree->Append(Format("r vector =", RVector));
    pTree->Append(Format("u vector =", UVector));
    pTree->Append(Format("d vector =", DVector));
    pTree->Append(Format("ambient =", Ambient));
    pTree->Append(Format("diffuse =", Diffuse));
    pTree->Append(Format("specular =", Specular));
    pTree->Append(Format("intensity =", Intensity));
    pTree->Append(Format("attn constant =", Constant));
    pTree->Append(Format("attn linear =", Linear));
    pTree->Append(Format("attn quadratic =", Quadratic));
    pTree->Append(Format("angle =", Angle));
    pTree->Append(Format("exponent =", Exponent));

    // children
    pTree->Append(Object::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
