//! @file     EGE_Graphic.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Graphic Interface
REF_OBJECT_DECL(IDynamicRHI);
REF_OBJECT_DECL(IResourceManagerIORHI);
REF_OBJECT_DECL(IResourceManagerRHI);
REF_OBJECT_DECL(IGraphicFont);
REF_OBJECT_DECL(IGraphicResourceManager);
REF_OBJECT_DECL(IGraphicVertexDeclaration);
REF_OBJECT_DECL(IGraphicBuffer);
REF_OBJECT_DECL(IGraphicVertexBuffer);
REF_OBJECT_DECL(IGraphicIndexBuffer);
REF_OBJECT_DECL(IGraphicVertexArray);
REF_OBJECT_DECL(IGraphicEffect);
REF_OBJECT_DECL(IGraphicSurface);
REF_OBJECT_DECL(IGraphicTexture2D);
REF_OBJECT_DECL(IGraphicTextureCube);
REF_OBJECT_DECL(IGraphicTexture2DSet);
REF_OBJECT_DECL(IGraphicDrawer);
REF_OBJECT_DECL(IGraphicScene);
REF_OBJECT_DECL(IGraphicSceneView);
REF_OBJECT_DECL(IGraphicLight);
REF_OBJECT_DECL(IGraphicMesh);
REF_OBJECT_DECL(IGraphicBackSurface);
REF_OBJECT_DECL(IGraphicViewport);
REF_OBJECT_DECL(IGraphicCanvas);
REF_OBJECT_DECL(IGraphicMirror);
REF_OBJECT_DECL(IGraphicFlatMirror);
REF_OBJECT_DECL(IGraphicSphereMirror);
REF_OBJECT_DECL(IGraphicResObject);
REF_OBJECT_DECL(IGraphicMaskLayer);
REF_OBJECT_DECL(IGraphicVRDevice);
REF_OBJECT_DECL(IGraphicModule);

typedef Array< IGraphicMeshRef > IGraphicMeshRefArray;

}

// Module-Graphic Global Files
#include "Interface/Module/Graphic/RHIResource.h"
#include "Interface/Module/Graphic/RHIInterface.h"
#include "Interface/Module/Graphic/GraphicGlobals.h"
#include "Interface/Module/Graphic/GraphicEvents.h"
#include "Interface/Module/Graphic/GraphicSerialization.h"
using namespace EGE::GraphicEvents;

// Module-Graphic Entry Files
#include "Interface/Module/Entries/EGE_GraphicEntry.h"

// Module-Graphic Interface Files
#include "Interface/Module/Graphic/IGraphicFont.h"
#include "Interface/Module/Graphic/IGraphicEffect.h"
#include "Interface/Module/Graphic/IGraphicResourceManager.h"
#include "Interface/Module/Graphic/IGraphicVertexDeclaration.h"
#include "Interface/Module/Graphic/IGraphicBuffer.h"
#include "Interface/Module/Graphic/IGraphicVertexBuffer.h"
#include "Interface/Module/Graphic/IGraphicIndexBuffer.h"
#include "Interface/Module/Graphic/IGraphicVertexArray.h"
#include "Interface/Module/Graphic/IGraphicSurface.h"
#include "Interface/Module/Graphic/IGraphicTexture2D.h"
#include "Interface/Module/Graphic/IGraphicTextureCube.h"
#include "Interface/Module/Graphic/IGraphicTexture2DSet.h"
#include "Interface/Module/Graphic/IGraphicDrawer.h"
#include "Interface/Module/Graphic/IGraphicScene.h"
#include "Interface/Module/Graphic/IGraphicSceneView.h"
#include "Interface/Module/Graphic/IGraphicLight.h"
#include "Interface/Module/Graphic/IGraphicMesh.h"
#include "Interface/Module/Graphic/IGraphicBackSurface.h"
#include "Interface/Module/Graphic/IGraphicViewport.h"
#include "Interface/Module/Graphic/IGraphicCanvas.h"
#include "Interface/Module/Graphic/IGraphicMirror.h"
#include "Interface/Module/Graphic/IGraphicFilter.h"
#include "Interface/Module/Graphic/IGraphicMaskLayer.h"
#include "Interface/Module/Graphic/IGraphicResObject.h"
#include "Interface/Module/Graphic/IGraphicVRDevice.h"
#include "Interface/Module/Graphic/IGraphicModule.h"

// Module-Graphic Template Files
#include "Interface/Module/Graphic/Template/TGraphicResObject.h"
#include "Interface/Module/Graphic/Template/TGraphicResObject3D.h"