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

#include "SEToolsCommonPCH.h"
#include "SEColladaInputArray.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEColladaInputArray::SEColladaInputArray(domInputLocalOffset_Array& 
    rDomInputs)
{
    m_iMaxOffset = 0;
    m_iPosition = -1;
    m_iNormal = -1;
    m_iTCoord = -1;
    m_pDomPositionData = 0;
    m_pDomNormalData = 0;
    m_pDomTCoordData = 0;

    SetInputs(rDomInputs);
}
//----------------------------------------------------------------------------
SEColladaInputArray::~SEColladaInputArray()
{
}
//----------------------------------------------------------------------------
void SEColladaInputArray::SetInputs(domInputLocalOffset_Array& rDomInputs)
{
    // Inputs with offsets.
    for( int i = 0; i < (int)rDomInputs.getCount(); i++ )
    {
        int iCurrentOffset  = (int)rDomInputs[i]->getOffset();
        if( m_iMaxOffset < iCurrentOffset )
        {
            m_iMaxOffset++;
        }

        domSource* pDomSource = 
            (domSource*)(domElement*)rDomInputs[i]->getSource().getElement();

        xsNMTOKEN strSemantic = rDomInputs[i]->getSemantic();
        if( strcmp("VERTEX", strSemantic) == 0 )
        {
            m_iPosition = iCurrentOffset;
        } 
        else if( strcmp("NORMAL", strSemantic) == 0 )
        {
            m_iNormal = iCurrentOffset;
            m_pDomNormalData = &pDomSource->getFloat_array()->getValue();
        } 
        else if( strcmp("TEXCOORD", strSemantic) == 0 )
        {
            m_iTCoord = iCurrentOffset;
            m_pDomTCoordData = &pDomSource->getFloat_array()->getValue();
        }
    }
    m_iMaxOffset += 1;

    // Inputs without offsets in vertices.
    domMesh* pDomMesh = 
        (domMesh*)rDomInputs[0]->getParentElement()->getParentElement();
    SE_ASSERT( pDomMesh );
    domVertices* pDomVertices = pDomMesh->getVertices();
    domInputLocal_Array& rDomVerticesInputs = pDomVertices->getInput_array();
    for( int i = 0; i < (int)rDomVerticesInputs.getCount(); i++ )
    {
        domSource* pDomSource = 
            (domSource*)(domElement*)rDomVerticesInputs[i]->getSource(
            ).getElement();

        xsNMTOKEN strSemantic = rDomVerticesInputs[i]->getSemantic();
        if( strcmp("POSITION", strSemantic) == 0 )
        {
            m_pDomPositionData = &pDomSource->getFloat_array()->getValue();
        } 
        else if( strcmp("NORMAL", strSemantic) == 0 )
        {
            m_pDomNormalData = &pDomSource->getFloat_array()->getValue();
            m_iNormal = m_iPosition;
        } 
        else if( strcmp("TEXCOORD", strSemantic) == 0 )
        {
            m_pDomTCoordData = &pDomSource->getFloat_array()->getValue();
            m_iTCoord = m_iPosition;
        }
    }
}
//----------------------------------------------------------------------------