#pragma once

typedef enum
{
	BUILD_RECTANGLE,
	BUILD_TRIANGLE,
	BUILD_CIRCLE,
	BUILD_LINE,
	BUILD_COLLECTION,
	ACTION_SELECT,
	ACTION_GROUPSELECT,
	ACTION_TRANSLATE,
	ACTION_ROTATE,
	ACTION_RESIZE
}   AppState;

typedef enum
{
	MODE_2D,
	MODE_3D
}   AppMode;