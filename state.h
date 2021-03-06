#pragma once

typedef enum
{
	BUILD_RECTANGLE,
	BUILD_TRIANGLE,
	BUILD_CIRCLE,
	BUILD_LINE,
	BUILD_COLLECTION,
    BUILD_CUBE,
    BUILD_SPHERE,
	BUILD_TERRAIN,
	ACTION_SELECT,
	ACTION_GROUPSELECT,
	ACTION_TRANSLATE,
	ACTION_ROTATE,
    ACTION_RESIZE,
    CAMERA
}   AppState;

typedef enum
{
	MODE_2D,
	MODE_3D,
	MODE_MODEL
}   AppMode;

typedef enum
{
	DISPLACEMENT,
	CUBE,
	NONE
}   ShaderMode;
