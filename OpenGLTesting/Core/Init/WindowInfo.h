#pragma once

#include <string>

namespace Core
{
	struct WindowInfo
	{
		std::string Name;

		int Width;
		int Height;

		int PositionX;
		int PositionY;
		
		bool Reshapable;

		WindowInfo()
		{
			Name = "Default Window";

			Width = 800;
			Height = 600;

			PositionX = 300;
			PositionY = 300;

			Reshapable = true;
		}

		WindowInfo(std::string name, int width, int height, int positionX, int positionY, bool reshapable)
		{
			Name = name;

			Width = width;
			Height = height;

			PositionX = positionX;
			PositionY = positionY;

			Reshapable = reshapable;
		}

		// copy constructor
		WindowInfo(const WindowInfo& windowInfo)
		{
			Name = windowInfo.Name;

			Width = windowInfo.Width;
			Height = windowInfo.Height;

			PositionX = windowInfo.PositionX;
			PositionY = windowInfo.PositionY;

			Reshapable = windowInfo.Reshapable;
		}

		// assignment operator
		WindowInfo& operator=(const WindowInfo& windowInfo)
		{
			Name = windowInfo.Name;

			Width = windowInfo.Width;
			Height = windowInfo.Height;

			PositionX = windowInfo.PositionX;
			PositionY = windowInfo.PositionY;

			Reshapable = windowInfo.Reshapable;

			return (*this);
		}
	};
}
