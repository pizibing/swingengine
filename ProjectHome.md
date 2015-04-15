<h1>Swing Engine Version 1 Source Code:</h1>
Most of techniques in the engine are mainly based on David Eberly's <br>
Wild Magic 4 open-source code.The author of Swing Engine learned a lot<br>
from Eberly's experience of architecture and algorithm. Several <br>
sub-systems are totally new,and others are re-implimented or <br>
re-organized based on Wild Magic 4's sub-systems.<br>
Swing Engine Copyright (c) 2007-2010. All Rights Reserved<br>

Eberly's permission:<br>
Geometric Tools, Inc.<br>
<a href='http://www.geometrictools.com'>http://www.geometrictools.com</a><br>
Wild Magic 4.0 Copyright (c) 1998-2006. All Rights Reserved<br>

Progress of Swing Engine project(implemented sub-systems):<br>
Left-hand based math fundation.<br>
Scene graph management system.<br>
Shader-based effect system.<br>
Skeleton-based animation system.<br>
3ds max8 data exporting plug-in.<br>
Collison detection system.<br>
Outdoor terrain system.<br>
DirectX 9.0 renderer system.<br>
DirectX 10.0 renderer system, is suspended.<br>
(I was trying to use Cg D3D10 runtime to construct the DX10 renderer,<br>
but it seems like there are several bugs or issues with this runtime lib,<br>
so I would like to learn and use the D3D10 native APIs to finish the job<br>
in future.)<br>
OpenGL 2.0 renderer system.<br>
OpenGL ES 1.x renderer system with limitational functions.<br>
(because the engine is designed for shader-based engine,but OpenGL ES 1.x<br>
is a fixed-function pipeline).<br>
OpenGL ES 2.0 renderer system.<br>
Simple post-process system.<br>
Multiple render targets system.<br>
Shader profile dectection system(Now it is a legacy since we already<br>
have a layer-based shader sub-system).<br>
Resource(shader program/texture image/model data/sound data) management<br>
system.<br>
Windows application system.<br>
Mac OS X application system.<br>
iPhone application system.<br>
Shaders implemented with Cg:shaodw map, bump map, parallax map, GPU skinning,<br>
vertex texture, traditional lighting, SSAO etc.<br>
3D audio engine, named Swing Audio, and its OpenAL audio renderer,<br>
which only supports PCM wave source data for now.<br>
Tool System library contains a COLLADA importer and an image converter for now.<br>