#pragma once
#include <iostream>

class FrameBuffer
{
public:
	FrameBuffer(float width, float height);
	~FrameBuffer();
	unsigned int getFrameTexture();
	void RescaleFrameBuffer(float width, float height);
	void Bind() const;
	void Unbind() const;
	unsigned int texture;
private:
	unsigned int fbo;
	unsigned int rbo;
};

