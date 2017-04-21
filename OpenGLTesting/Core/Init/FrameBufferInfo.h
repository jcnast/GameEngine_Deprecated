#pragma once

#include "../../Dependencies/glew/glew.h"
#include "../../Dependencies/freeglut/freeglut.h"

namespace Core
{
	struct FrameBufferInfo
	{
		unsigned int Flags;

		bool MSAA; // to enable or disable (multisampling anti aliasing?) when we need it

		FrameBufferInfo()
		{
			Flags = GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH;

			MSAA = false;
		}

		FrameBufferInfo(bool color, bool depth, bool stencil, bool msaa)
		{
			Flags = GLUT_DOUBLE; // this is a must
			if (color)
			{
				Flags |= GLUT_RGBA | GLUT_ALPHA;
			}
			if (depth)
			{
				Flags |= GLUT_DEPTH;
			}
			if (depth)
			{
				Flags |= GLUT_STENCIL;
			}
			if (msaa)
			{
				Flags |= GLUT_MULTISAMPLE;
			}

			MSAA = msaa;
		}

		// copy constructor
		FrameBufferInfo(const FrameBufferInfo& frameBufferInfo)
		{
			Flags = frameBufferInfo.Flags;

			MSAA = frameBufferInfo.MSAA;
		}

		// assignment operator
		FrameBufferInfo& operator=(const FrameBufferInfo& frameBufferInfo)
		{
			Flags = frameBufferInfo.Flags;

			MSAA = frameBufferInfo.MSAA;

			return (*this);
		}
	};
}