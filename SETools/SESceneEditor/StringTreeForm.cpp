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

#include "SESceneEditorPCH.h"
#include "StringTreeForm.h"

using namespace Swing;
using namespace Swing::Tools::SceneEditor;

//----------------------------------------------------------------------------
void StringTreeForm::CreateStringTree(SEStringTree* pTree)
{
    // Don't paint the TreeView object until all the nodes have been created.
    treeViewStringTree->BeginUpdate();

    // Clear the TreeView object of any current nodes.
    treeViewStringTree->Nodes->Clear();

    if( pTree )
    {
        TreeNode^ thRoot = gcnew TreeNode();
        thRoot->Text = gcnew String("Root");
        treeViewStringTree->Nodes->Add(thRoot);
        CreateTreeRecursive(thRoot, pTree, NodeType::NT_CLASS);
    }

    // Now paint the TreeView object.
    treeViewStringTree->EndUpdate();
}
//----------------------------------------------------------------------------
void StringTreeForm::CreateTreeRecursive(TreeNode^ thParent, SEStringTree* 
    pTree, NodeType eType)
{
    TreeNode^ thCurNode = gcnew TreeNode();
    thParent->Nodes->Add(thCurNode);

    if( pTree->GetStringCount() <= 0 )
    {
        throw gcnew Exception("String count is zero.");
    }

    if( strncmp(pTree->GetString(0), "Swing", 5) == 0 )
    {
        // String tree rooted at an Object-derived object.

        // Add object.  Strip off the "Swing." prefix (the "+ 6" term).
        char* acName = pTree->GetString(0) + 6;
        thCurNode->Text = gcnew String(acName);

        if( eType == NodeType::NT_CLASS )
        {
            thCurNode->ImageIndex = 0;
            thCurNode->SelectedImageIndex = 0;
        }
        else if( eType == NodeType::NT_SUBCLASS )
        {
            thCurNode->ImageIndex = 0;
            thCurNode->SelectedImageIndex = 0;
        }
        else
        {
            throw gcnew Exception("Unknown node type is found.");
        }

        // Add subclass of object.
        int iStart;
        if( strncmp(pTree->GetString(0), "Swing.SEObject", 14) != 0)
        {
            CreateTreeRecursive(thCurNode, pTree->GetChild(0), 
                NodeType::NT_SUBCLASS);
            iStart = 1;
        }
        else
        {
            iStart = 0;
        }

        // Add strings.
        int i;
        for( i = 1; i < pTree->GetStringCount(); i++ )
        {
            TreeNode^ thCurStringNode = gcnew TreeNode();
            thCurStringNode->Text = gcnew String(pTree->GetString(i));
            thCurStringNode->ImageIndex = 1;
            thCurStringNode->SelectedImageIndex = 1;
            thCurNode->Nodes->Add(thCurStringNode);
        }

        // Add children.
        for( i = iStart; i < pTree->GetChildCount(); i++ )
        {
            SEStringTree* pCTree = pTree->GetChild(i);
            if( pCTree->GetStringCount() <= 0 )
            {
                throw gcnew Exception("String count is zero.");
            }

            if( strncmp(pCTree->GetString(0), "Swing", 5) == 0 )
            {
                eType = NodeType::NT_CLASS;
            }
            else
            {
                eType = NodeType::NT_DATA;
            }

            CreateTreeRecursive(thCurNode, pCTree, eType);
        }
    }
    else
    {
        // String tree represents a native type (for example, an array).

        // Add object.
        thCurNode->Text = gcnew String(pTree->GetString(0));
        thCurNode->ImageIndex = 0;
        thCurNode->SelectedImageIndex = 0;

        // Add strings.
        int i;
        for( i = 1; i < pTree->GetStringCount(); i++ )
        {
            TreeNode^ thCurStringNode = gcnew TreeNode();
            thCurStringNode->Text = gcnew String(pTree->GetString(i));
            thCurStringNode->ImageIndex = 1;
            thCurStringNode->SelectedImageIndex = 1;
            thCurNode->Nodes->Add(thCurStringNode);
        }

        // Add children.
        for( i = 0; i < pTree->GetChildCount(); i++ )
        {
            SEStringTree* pCTree = pTree->GetChild(i);
            if( pCTree->GetStringCount() <= 0 )
            {
                throw gcnew Exception("String count is zero.");
            }

            if( strncmp(pCTree->GetString(0), "Swing", 5) == 0 )
            {
                eType = NodeType::NT_CLASS;
            }
            else
            {
                eType = NodeType::NT_DATA;
            }

            CreateTreeRecursive(thCurNode, pCTree, eType);
        }
    }
}
//----------------------------------------------------------------------------