/* \file graphicsContext.h */
#pragma once

namespace
{
	/* \class GraphicsContext */
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void init() = 0; //!< Initialise grahics context for given windowing API
		virtual void swapBuffers() = 0; //!< Swap front and back buffers (double buffering)
		virtual void updateViewport(int32_t width, int32_t height) = 0;
	};
}