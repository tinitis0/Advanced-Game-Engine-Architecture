#pragma once

#include "independent/core/application.h"

namespace Engine
{
	class playableSoundComponent
	{
	public:
		playableSoundComponent(const char* audioFilePath, bool looping = true);
		void Play(glm::vec3& location);
		void Pause();

		const char * soundName;
		int32_t channel;
		bool isPlaying;
		bool setToLoop;
	};

	class ParametricSoundComponent
	{
	public:
		ParametricSoundComponent(const char * BankFilePath, const char * BankStringsFilePath, const char * pEventName);
		std::string eventName;
	};

	class CurrentListenerComponent
	{
	public:
		CurrentListenerComponent() {}
	};

	namespace AudioSystem
	{
		void updatePositions();
	}

	class AudioOcclusionComponent
	{
	public:
		AudioOcclusionComponent(const char *  pName, const AudioGeometryDefinition& geometryDef);
		const char * name;
	};
}