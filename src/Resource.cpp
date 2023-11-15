/*
 * Resource.cpp
 *
 *  Created on: Feb 28, 2023
 *      Author: kokhoe
 */
#include "Resource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Resource::Resource()
{

}

Resource::Resource(string resourcePath, bool flipYaxis)
{
	if( flipYaxis )
		stbi_set_flip_vertically_on_load(true);
	else
		stbi_set_flip_vertically_on_load(false);

	spriteSheet = stbi_load(resourcePath.c_str(), &width, &height, &channel, STBI_rgb_alpha);
	assert(this->spriteSheet);
}

Resource::~Resource()
{
	stbi_image_free(spriteSheet);
}
