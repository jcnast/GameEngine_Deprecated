#pragma once

namespace Core
{
	// OpenGL versions
	struct ContextInfo
	{
		int MajorVersion;
		int MinorVersion;
		// verions go <MajorVersion>.<MinorVersion>

		bool Core;

		ContextInfo()
		{
			MajorVersion = 3;
			MinorVersion = 3;

			Core = true; // true = NOT in compatability mode, false = IN compatability mode
		}

		ContextInfo(int majorVersion, int minorVersion, bool core)
		{
			MajorVersion = majorVersion;
			MinorVersion = minorVersion;

			Core = core;
		}

		// copy constructor
		ContextInfo(const ContextInfo& contextInfo)
		{
			MajorVersion = contextInfo.MajorVersion;
			MinorVersion = contextInfo.MinorVersion;

			Core = contextInfo.Core;
		}

		// assignment operator
		ContextInfo& operator=(const ContextInfo& contextInfo)
		{
			MajorVersion = contextInfo.MajorVersion;
			MinorVersion = contextInfo.MinorVersion;

			Core = contextInfo.Core;

			return (*this);
		}
	};
}
