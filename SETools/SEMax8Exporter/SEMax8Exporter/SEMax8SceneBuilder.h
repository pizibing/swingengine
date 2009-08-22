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

#ifndef Swing_Max8SceneBuilder_H
#define Swing_Max8SceneBuilder_H

#include "SwingFoundation.h"
#include "SEMax8ExportSettings.h"
#include "SEMax8Materials.h"
#include "SEMax8MaterialTree.h"
#include "SEMax8UnimaterialMesh.h"
#include "max.h"
#include "stdmat.h"
#include <vector>

using namespace std;

//----------------------------------------------------------------------------
// 名称:Max8SceneBuilder类
// 说明:根据Max场景视图,构建Swing Engine场景视图.
// 作者:Sun Che
// 时间:20080815
//----------------------------------------------------------------------------
class Max8SceneBuilder
{
public:
    Max8SceneBuilder(const TCHAR* acFilename, BOOL bExportSelected, 
        Max8ExportSettings* pSettings, ExpInterface* pExport, Interface* pMax,
        INode* pRootNode);

    ~Max8SceneBuilder(void);

private:
    class AnimationTiming
    {
    public:
        AnimationTiming() : Active(FALSE), Start(0), End(0) { /**/ }

        BOOL Active;
        TimeValue Start;
        TimeValue End;
    };

    class ModifierInfo
    {
    public:
        INode* Node;
        vector<Modifier*> Modifiers;
    };

    enum KeyType
    {
        KT_TRANSLATION,
        KT_ROTATION,
        KT_SCALE
    };

    class KeyInfo
    {
    public:
        KeyInfo(TimeValue iTime, KeyType eType)
        {
            Time = iTime;
            Type = eType;
        }

        TimeValue Time;
        KeyType Type; 
    };

    class BoneWeight
    {
    public:
        BoneWeight(void)
        {
            BoneID = -1;
            Weight = -1.0f;
        }

        bool operator == (const BoneWeight& rBoneWeight) const
        {
            return Weight == rBoneWeight.Weight;
        }
        bool operator < (const BoneWeight& rBoneWeight) const
		{
            return Weight < rBoneWeight.Weight;
		}

        int BoneID;
        float Weight;
    };

    // 场景遍历
    bool Traverse(INode* pMaxNode, Swing::Spatial* pSENode);

    // node处理
    Swing::Spatial* BuildGeometry(INode* pMaxNode, Swing::Spatial* pSENode);
    Swing::Spatial* BuildSpatial(INode* pMaxNode, Swing::Spatial* pSENode);
    Swing::Spatial* BuildMesh(INode* pMaxNode, Swing::Spatial* pSENode);
    Swing::Transformation GetLocalTransform(INode* pNode, TimeValue iTime);

    // mesh处理
    TriObject* GetTriObject(INode* pNode, bool* pbNeedDel);
    void SplitGeometry(Mesh* pMaxMesh, int iMtlID,
        vector<Max8UnimaterialMesh*>& rUMeshes);
    Swing::Vector3f GetVertexNormal(Mesh* pMaxMesh, int iFace, int iVertex);  
    void PackColors(Max8UnimaterialMesh* pMesh, Mesh* pMaxMesh,
        vector<int>& rPartition);
    void PackTextures(Max8UnimaterialMesh* pUniMesh, Mesh* pMaxMesh,
        vector<int>& rPartition);
    void PackVertices(Max8UnimaterialMesh* pUniMesh, Mesh* pMaxMesh,
        vector<int>& rPartition, Swing::Vector3f* aNormal);

    // material处理
    void ConvertMaterials(INode* pTopNode);
    void CollectMaterials(INode* pNode);
    void ConvertMaterialTree(Mtl& rMtl, int iMtlID, int iSubNo,
        Max8MaterialTree& rTree);
    void ConvertTextureTree(Texmap& rTex, Class_ID ClassID, int iSubNo,
        Max8TextureTree& rTree);

    Max8Materials m_MtlList;
    std::vector<Max8MaterialTree> m_MtlTree;
    static const TCHAR* ms_aacMapName[NTEXMAPS];
    static const char* ms_aacEnvName[5];
    static const TCHAR* ms_acMapEnvironment;
    static const TCHAR* ms_acMapGeneric;

    // light处理
    void BuildAmbientLight(void);
    void BuildLight(INode* pMaxNode, Swing::Spatial* pSENode);
    Swing::Vector3f GetLightLocation(INode* pNode);
    Swing::Light* BuildPointLight(INode* pNode);
    Swing::Light* BuildSpotLight(INode* pNode, LightState& rLightState);
    Swing::Light* BuildDirectionalLight(INode* pNode);

    // animation处理
    static bool AreEqual(const Point3& rPoint1, const Point3& rPoint2);
    static bool AreEqual(const Quat& rQuat1, const Quat& rQuat2);
    static bool CompareKeyTimes(KeyInfo* pFirst, KeyInfo* pSecond);
    void BuildKeyFrameController(INode* pMaxNode, Swing::Spatial* pSENode);
    void BuildFrameController(INode* pNode, Swing::Spatial* pSENode);
    bool GetAnimationTiming(INode* pNode, AnimationTiming& rTTiming, 
        AnimationTiming& rRTiming, AnimationTiming& rSTiming);
    void GetTrnKeyInfo(int &riNumKeys, Class_ID& rClassID,
        IKeyControl* pKeyCon, AnimationTiming& rTTiming,
        vector<KeyInfo*>& rKeyInfo);
    void GetRotKeyInfo(int& riNumKeys, Class_ID& rClassID,
        IKeyControl* pKeyCon, AnimationTiming& rRTiming,
        vector<KeyInfo*>& rKeyInfo);
    void GetScaleKeyInfo(int& riNumKeys, Class_ID& rClassID,
        IKeyControl* pKeyCon, AnimationTiming& rSTiming,
        vector<KeyInfo*>& rKeyInfo);

    // modifier处理
    void ApplyModifiers(void);
    void FindModifiers(INode* pNode, vector<Modifier*>& rModifiers);
    void ProcessSkin(INode* pNode, Modifier* pSkinMod);
    void ProcessMorpher(INode* pNode, Modifier* pMorpherMod);

    TCHAR* m_acFilename;
    BOOL m_bExportSelected;
    Max8ExportSettings* m_pSettings;
    ExpInterface* m_pExport;
    Interface* m_pMax;
    INode* m_pRootNode;
    int m_iTicksPerFrame;
    TimeValue m_iTimeStart;
    TimeValue m_iTimeEnd;
    TimeValue m_iTimeOffset;
    Swing::NodePtr m_spSEScene;
    vector<ModifierInfo*> m_ModList;

    static const float ATTENUATION;
    static const float MIN_DIFFERENCE;
};

#endif



