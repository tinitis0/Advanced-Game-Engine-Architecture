#pragma once

#include "system.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_studio.hpp"
#include <stdint.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>

struct AudioGeometryDefinition
{
	std::vector<glm::vec3>* vertices; //!< Vertices
	std::vector<uint32_t>* indices; //!< Indices
	glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 forward = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
	float directOcclusion = 1.0f;
	float reverbOcclusion = 0.3f;
};


enum class RollOff	{Inverse, InverseTapered, Linear, LinearSquared};

namespace Engine
{
	class AudioManager : public System
	{
	private:
		FMOD::Studio::System* m_studioSystem;
		FMOD::System* m_lowLevelSystem;

		static const int32_t m_maxChannels = 32;
		int32_t m_nextChannelID = 0;

		std::map<std::string, FMOD::Sound*> m_sounds;
		std::map<int32_t, FMOD::Channel*> m_channels;
		std::map<std::string, FMOD::Geometry*> m_geometry;
		std::map<std::string, FMOD::Studio::EventInstance*> m_events;
		std::map<std::string, FMOD::Studio::Bank*> m_banks;

		int32_t errorCheck(FMOD_RESULT result) const;
		FMOD_VECTOR GLMVecToFmod(const glm::vec3& vec);
	
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override; //!< Start the system
		void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Close down the system
	
		void update(); //!< Update
		void loadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags); //!< Loading bank
		void loadEvent(const std::string& strEventName); //!< Loading the event
		void loadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false,
			float minDist = 0.25f, float maxDist = 1000.f, RollOff rollOff = RollOff::Inverse);
		void unLoadSound(const std::string &strSoundName); //!< Unload a sound
		void set3dListenerAndOrientation(const glm::mat4& transform, const glm::vec3& velocity); //!< Listener
		void addGeometry(const std::string& label, const AudioGeometryDefinition& def); //!< Add audio geometry
		void moveGeometry(const std::string & label, const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, const glm::vec3& scale);
		int32_t playSound(const std::string& strSoundName, const glm::vec3& vPos = glm::vec3{ 0, 0, 0 }); //!< Play Audio
		void playEvent(const std::string &strEventName); //!< Play the event
		void toggleChannelPause(int32_t nChannelID); //!< Pause a channel
		void stopEvent(const std::string& strEventName, bool bImmediate = false); //!< Stop Event
		void getEventParameter(const std::string &strEventName, const std::string &strEventParameter, float* value); //!< Event parameters
		void setEventParameter(const std::string & strEventName, const std::string &strParameterName, float value); //!< Set event parameter
		void setEvent3DAttributes(const std::string & strEventName, const glm::mat4 & transform, const glm::vec3 & velocity); //!< 3D Event Attributes
		void togglePauseAllChannels(); //!< Pause all audio channels
		void setChannel3dAttributes(int32_t nChannelID, const glm::vec3 & position, const glm::vec3 & velocity); //!< Audio channel 3D attributes
		bool isPlaying(int32_t nChannelID) const; //!< Audio Playing
		bool isEventPlaying(const std::string &strEventName) const; //!< Event playing
	};

}