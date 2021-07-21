#include "engine_pch.h"

#include "systems/AudioManager.h"
#include "systems/Logger.h"

namespace Engine
{
	int32_t AudioManager::errorCheck(FMOD_RESULT result) const
	{
		if (result != FMOD_OK)
		{
			Logger::error("FMOD ERROR: {0}", result); //!< Log the error result
			return 1; //!< Return the error
		}
		return 0; //!< Return no error
	}

	FMOD_VECTOR AudioManager::GLMVecToFmod(const glm::vec3 & vec)
	{
		FMOD_VECTOR result;

		// Converting GLM vector to a FMOD vector
		result.x = vec.x;
		result.y = vec.y;
		result.z = vec.z;
		return result;
	}

	void AudioManager::start(SystemSignal init, ...)
	{
		errorCheck(FMOD::Studio::System::create(&m_studioSystem)); // Checking for errors on system creation (Studio)
		errorCheck(m_studioSystem->initialize(m_maxChannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));

		uint32_t version;
		errorCheck(FMOD::System_Create(&m_lowLevelSystem)); // Checking for errors on system creation (Low Level)
		errorCheck(m_lowLevelSystem->getVersion(&version)); // Error checking the system version

		if (version < FMOD_VERSION)
		{
			Logger::error("FMOD lib version {0} does not match the header version {1}", version, FMOD_VERSION); // Checking that the lib & header versions match
		}

		errorCheck(m_lowLevelSystem->init(m_maxChannels, FMOD_INIT_NORMAL, NULL));
		errorCheck(m_lowLevelSystem->set3DSettings(1.f, 1.f, 1.f)); // Setting the 3D settings (dopplerscale, distancefactor, rolloffscale) & error checks
		errorCheck(m_lowLevelSystem->setGeometrySettings(50.f)); // Setting geometry settings (maxworldsize) & error checks
	}

	void AudioManager::stop(SystemSignal close, ...)
	{
		for (auto& pair : m_events) errorCheck(pair.second->release()); // Release any events
		for (auto& pair : m_banks) errorCheck(pair.second->unload()); // Unload any banks

		errorCheck(m_studioSystem->unloadAll()); // Unload any audio in system
		errorCheck(m_studioSystem->flushCommands()); // Flush all commands
		errorCheck(m_studioSystem->release()); // Release the system

		for (auto& pair : m_sounds) errorCheck(pair.second->release()); // Release any audio added
		errorCheck(m_lowLevelSystem->close()); // Close the low level system & check for any errors in process
		errorCheck(m_lowLevelSystem->release());
	}

	void AudioManager::update()
	{
		// Delete any channels from the map when finished playing
		std::vector<std::map<int32_t, FMOD::Channel*>::iterator> m_StoppedChannels; // A map of channels, which is iterated through for the stopped channels
		for (auto it = m_channels.begin(); it != m_channels.end(); ++it)
		{
			bool isPlaying = false; // Boolean value for whether the audio is playing
			it->second->isPlaying(&isPlaying);
			if (!isPlaying)
			{
				m_StoppedChannels.push_back(it);
			}
		}
		for (auto& it : m_StoppedChannels)
		{
			m_channels.erase(it);
		}

		// Updating the low level system & checking for any errors
		errorCheck(m_lowLevelSystem->update());

		// Updating the studio system & checking for any errors
		errorCheck(m_studioSystem->update());

	}

	void AudioManager::loadBank(const std::string & strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
	{
		auto it = m_banks.find(strBankName); // Find bank file
		if (it != m_banks.end())
			return;
		FMOD::Studio::Bank* bank; // Studio Bank
		errorCheck(m_studioSystem->loadBankFile(strBankName.c_str(), flags, &bank)); // Load bank file, flags & studio bank

		if (bank)
		{
			m_banks[strBankName] = bank; // The bank is the bank file
		}
	}

	void AudioManager::loadEvent(const std::string & strEventName)
	{
		auto it = m_events.find(strEventName);
		if (it != m_events.end())
			return;
		FMOD::Studio::EventDescription* eventDescription = NULL;
		errorCheck(m_studioSystem->getEvent(strEventName.c_str(), &eventDescription));
		if (eventDescription)
		{
			FMOD::Studio::EventInstance* eventInstance = NULL;
			errorCheck(eventDescription->createInstance(&eventInstance));
			if (eventInstance)
			{
				m_events[strEventName] = eventInstance;
			}
		}
	}

	void AudioManager::loadSound(const std::string & strSoundName, bool b3d, bool bLooping, bool bStream, float minDist, float maxDist, RollOff rollOff)
	{
		auto it = m_sounds.find(strSoundName); // Find audio file
		if (it != m_sounds.end())
			return;
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D : FMOD_2D;
		eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

		switch (rollOff)
		{
		case RollOff::Linear:
			eMode |= FMOD_3D_LINEARROLLOFF;
			break;
		case RollOff::LinearSquared:
			eMode |= FMOD_3D_LINEARSQUAREROLLOFF;
			break;
		case RollOff::InverseTapered:
			eMode |= FMOD_3D_INVERSETAPEREDROLLOFF;
		}

		FMOD::Sound* sound = nullptr;
		errorCheck(m_lowLevelSystem->createSound(strSoundName.c_str(), eMode, 0, &sound)); // Create sound with audio file & rolloff mode

		if (b3d)
		{
			sound->set3DMinMaxDistance(minDist, maxDist);
		}
		if (sound != nullptr)
		{
			m_sounds[strSoundName] = sound;
		}
	}

	void AudioManager::unLoadSound(const std::string & strSoundName)
	{
		auto it = m_sounds.find(strSoundName); // Find audio file
		if (it == m_sounds.end())
			return;
		errorCheck(it->second->release()); // Release audio & error check process
		m_sounds.erase(it); // Erase the audio
	}

	void AudioManager::set3dListenerAndOrientation(const glm::mat4 & transform, const glm::vec3 & velocity)
	{
		FMOD_VECTOR lastPos, lastVel, lastForward, latUp;

		glm::vec3 up = { transform[1][0], transform[1][1], transform[1][2] };
		glm::vec3 forward = { transform[2][0], transform[2][1], transform[2][2] };
		glm::vec3 position = { transform[3][0], transform[3][1], transform[3][2] };

		auto listenerPos = GLMVecToFmod(position);
		auto listenerForward = GLMVecToFmod(forward);
		auto listenerUp = GLMVecToFmod(up);
		auto listenerVelocity = GLMVecToFmod(velocity);

		FMOD_3D_ATTRIBUTES f;
		f.position = listenerPos;
		f.forward = listenerForward;
		f.up = listenerUp;
		f.velocity = listenerVelocity;

		errorCheck(m_lowLevelSystem->set3DListenerAttributes(0, &listenerPos, &listenerVelocity, &listenerForward, &listenerUp));
		errorCheck(m_studioSystem->setListenerAttributes(0, &f));
	}

	void AudioManager::addGeometry(const std::string & label, const AudioGeometryDefinition & def)
	{
		FMOD::Geometry *geometry; // Defining geometry

		int32_t numPolys = def.indices->size() / 3; // Number of polygons
		int32_t numVert = def.vertices->size(); // Number of vertices
		errorCheck(m_lowLevelSystem->createGeometry(numPolys, numVert, &geometry)); // Create the geometry with the polygons and vertices & error checks

		m_geometry[label] = geometry;
		FMOD_VECTOR triangle[3]; // Triangle is a vector of 3
		FMOD_VECTOR vert = { 0, 0, 0 }; // Empty vector for vertices
		int32_t polygonIndex;

		for (int32_t i = 0, j = 0; i < def.indices->size(); i++)
		{
			vert = GLMVecToFmod(def.vertices->at(def.indices->at(i)));
			triangle[j] = vert;
			j++;

			if (j == 3)
			{
				geometry->addPolygon(def.directOcclusion, def.reverbOcclusion, true, 3, triangle, &polygonIndex); // Create a polyon when 3 vertices are created
				j = 0; // J then resets back to zero
			}
		}
		geometry->setScale(&GLMVecToFmod(def.scale)); // Setting the scale of the geometry
		geometry->setPosition(&GLMVecToFmod(def.position)); // Set position of the geometry
		geometry->setRotation(&GLMVecToFmod(def.forward), &GLMVecToFmod(def.up)); // Set rotation of the geometry
	}

	void AudioManager::moveGeometry(const std::string & label, const glm::vec3 & position, const glm::vec3 & forward, const glm::vec3 & up, const glm::vec3 & scale)
	{
		m_geometry[label]->setScale(&GLMVecToFmod(scale)); // Change scale of labelled geometry
		m_geometry[label]->setPosition(&GLMVecToFmod(position)); // Change position of labelled geometry
		m_geometry[label]->setRotation(&GLMVecToFmod(forward), &GLMVecToFmod(up)); // Change rotation of labelled geometry
	}

	int32_t AudioManager::playSound(const std::string & strSoundName, const glm::vec3 & vPos)
	{
		int32_t channelID = m_nextChannelID++; // Setting chasnnel ID to next available ID in list
		auto it = m_sounds.find(strSoundName); // Finding audio
		// IF NO AUDIO IS FOUND...
		if (it == m_sounds.end())
		{
			loadSound(strSoundName);
			it = m_sounds.find(strSoundName);
			if (it == m_sounds.end())
			{
				return channelID;
			}
		} // LOAD THE SOUND

		FMOD::Channel* channel = nullptr;
		errorCheck(m_lowLevelSystem->playSound(it->second, 0, true, &channel));
		if (channel)
		{
			FMOD_MODE currentMode;
			it->second->getMode(&currentMode);
			if (currentMode & FMOD_3D)
			{
				FMOD_VECTOR FVposition = GLMVecToFmod(vPos); // Change position
				FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
				errorCheck(channel->set3DAttributes(&FVposition, &vel));
			}
			errorCheck(channel->setPaused(false));
			m_channels[channelID] = channel;
		}
		return channelID;
	}

	void AudioManager::playEvent(const std::string & strEventName)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
		{
			loadEvent(strEventName);
			it = m_events.find(strEventName);
			if (it == m_events.end())
			{
				return;
			}
			it->second->start();
		}
	}

	void AudioManager::toggleChannelPause(int32_t nChannelID)
	{
		auto it = m_channels.find(nChannelID); // Finding the channel ID
		if (it == m_channels.end())
			return;

		bool paused;
		errorCheck(it->second->getPaused(&paused));
		paused = !paused;
		errorCheck(it->second->setPaused(paused));
	}

	void AudioManager::stopEvent(const std::string & strEventName, bool bImmediate)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
		{
			return;
		}
		FMOD_STUDIO_STOP_MODE eMode;
		eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
		errorCheck(it->second->stop(eMode));
	}

	void AudioManager::getEventParameter(const std::string & strEventName, const std::string & strEventParameter, float * value)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;

		errorCheck(it->second->getParameterByName(strEventParameter.c_str(), value));

	}

	void AudioManager::setEventParameter(const std::string & strEventName, const std::string & strParameterName, float value)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;

		errorCheck(it->second->setParameterByName(strParameterName.c_str(), value));
	}

	void AudioManager::setEvent3DAttributes(const std::string & strEventName, const glm::mat4 & transform, const glm::vec3 & velocity)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;

		glm::vec3 up = { transform[1][0], transform[1][1], transform[1][2] };
		glm::vec3 forward = { transform[2][0], transform[2][1], transform[2][1] };
		glm::vec3 position = { transform[3][0], transform[3][1], transform[3][2] };
		FMOD_3D_ATTRIBUTES attributes;
		attributes.position = GLMVecToFmod(position);
		attributes.forward = GLMVecToFmod(forward);
		attributes.up = GLMVecToFmod(up);
		errorCheck(it->second->set3DAttributes(&attributes));
	}

	void AudioManager::togglePauseAllChannels()
	{
		for (auto it = m_channels.begin(); it != m_channels.end(); ++it)
		{
			bool paused;
			errorCheck(it->second->getPaused(&paused));
			paused = !paused;
			errorCheck(it->second->setPaused(paused));
		}
	}

	void AudioManager::setChannel3dAttributes(int32_t nChannelID, const glm::vec3 & position, const glm::vec3 & velocity)
	{
		auto it = m_channels.find(nChannelID); // Find channel with chosen ID
		// IF NO CHANNEL WITH ID IS FOUND...
		if (it == m_channels.end())
			return;
		FMOD_VECTOR pos = GLMVecToFmod(position); // Pos is the position
		FMOD_VECTOR vel = GLMVecToFmod(velocity); // Vel is the velocity
		errorCheck(it->second->set3DAttributes(&pos, &vel));

	}

	bool AudioManager::isPlaying(int32_t nChannelID) const
	{
		auto it = m_channels.find(nChannelID); // Find channel
		// IF NO CHANNEL WITH ID IS FOUND...
		if (it == m_channels.end())
			return false; // Return false as no instance of channel

		bool playing;
		errorCheck(it->second->isPlaying(&playing)); // Check if playing
		return playing; // Return boolean for playing (True / False)

	}

	bool AudioManager::isEventPlaying(const std::string & strEventName) const
	{
		auto it = m_events.find(strEventName); // Find event name
		// IF NO EVENT WITH NAME IS FOUND...
		if (it == m_events.end())
			return false; // Return false as no instance of event is found
		// IF  EVENT IS FOUND...
		FMOD_STUDIO_PLAYBACK_STATE state = FMOD_STUDIO_PLAYBACK_FORCEINT;
		it->second->getPlaybackState(&state); // Get the state of the event
		if (state = FMOD_STUDIO_PLAYBACK_PLAYING) // If State of event is playing...
		{
			return true; // Return true for playing
		}
	}
}





