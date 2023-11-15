#ifndef __RESOURCE_H_
#define __RESOURCE_H_

#include <iostream>

using namespace std;

class Resource
{
public:
	Resource();
	Resource(string, bool flipYaxis = false);
	virtual ~Resource();


public:
	inline unsigned char* getSpriteSheet() {
		return spriteSheet;
	}

	inline int getWidth() {
		return width;
	}

	inline int getHeight() {
		return height;
	}

	inline int getchannel() {
		return channel;
	}


private:
	unsigned char *spriteSheet = nullptr;
	int width = 0;
	int height = 0;
	int channel = 0;
};

#endif /* __RESOURCE_H_ */
