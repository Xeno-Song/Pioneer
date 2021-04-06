#pragma once

#ifndef __C_RESOURCE_LIST_H__
#define __C_RESOURCE_LIST_H__

const enum ModelFileType
{
	STL_BINARY,
	STL_ASCII,
	OBJ,
};

namespace ResourceNumber
{
	const enum ImageResourceNumber
	{
		IMG_NONE,
		IMG_TEST_GROUND,
		IMG_TEST_CHARACTOR,

		IMG_RES_MAX // DO NOT CHANGE THIS ELEMENT
	};
}
#endif