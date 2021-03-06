// This file is part of Wintermute Engine
// For conditions of distribution and use, see copyright notice in license.txt

#ifndef __WmeSoundDataSource_H__
#define __WmeSoundDataSource_H__


#include "Object.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#	include <al.h>
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#	include <OpenAL/al.h>
#else
#	include <AL/al.h>
#endif


namespace Wme
{
	class WmeDllExport SoundDataSource : public Object
	{
	public:
		SoundDataSource();
		virtual ~SoundDataSource();

		virtual bool InitializeFromFile(const WideString& fileName) = 0;
		virtual size_t ReadData(size_t size, byte* buffer) = 0;
		virtual bool IsEof() const = 0;
		virtual void SkipToTime(float seconds) = 0;
		virtual float GetTotalTime() const = 0;
		virtual float GetCurrentTime() const = 0;
		virtual int GetNumChannels() const = 0;
		virtual size_t GetBufferSize() const = 0;
		virtual float GetBufferLengthSec() const = 0;
		virtual ALenum GetFormat() const = 0;
		virtual int GetFrequency() const = 0;

	protected:
		bool m_Initialized;
	};
}

#endif // __WmeSoundDataSource_H__
