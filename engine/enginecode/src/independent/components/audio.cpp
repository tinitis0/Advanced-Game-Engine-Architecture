#include "engine_pch.h"
#include "Platform/EnTT/Components/audio.h"
#include "Platform/EnTT/Components/transform.h"
#include "Platform/EnTT/Components/physics.h"

namespace Engine
{
	playableSoundComponent::playableSoundComponent(const char * audioFilePath, bool looping) :
		soundName(audioFilePath),
		setToLoop(looping),
		channel(-1)
	{
		auto& audioManager = Application::getInstance().getAudioManager();
		audioManager->loadSound(soundName, true, setToLoop, false);
	}

	void playableSoundComponent::Play(glm::vec3 & location)
	{
		auto& audioManager = Application::getInstance().getAudioManager();

		if (channel > -1)
		{
			if (!audioManager->isPlaying(channel))
			{
				audioManager->toggleChannelPause(channel);
			}
			else
			{
				channel = audioManager->playSound(soundName, location);
			}
		}
	}

	void playableSoundComponent::Pause()
	{
		if (channel > -1)
		{
			auto& audioManager = Application::getInstance().getAudioManager();
			audioManager->toggleChannelPause(channel);
		}
	}

	ParametricSoundComponent::ParametricSoundComponent(const char * BankFilePath, const char * BankStringsFilePath, const char * pEventName) :
		eventName(eventName)
	{
		auto& audioManager = Application::getInstance().getAudioManager();
		audioManager->loadBank(BankFilePath, FMOD_STUDIO_LOAD_BANK_NORMAL);
		audioManager->loadBank(BankStringsFilePath, FMOD_STUDIO_LOAD_BANK_NORMAL);
		audioManager->loadEvent(eventName);
		audioManager->playEvent(eventName);
	}

	namespace AudioSystem
	{
		void updatePositions()
		{
			auto& registry = Application::getInstance().m_registry;
			auto& audioManager = Application::getInstance().getAudioManager();

			// LISTNER
			auto& listenerView = registry.view<CurrentListenerComponent>();
			{
				auto entity = listenerView.front();
				auto& t = registry.get<TransformComponent>(entity);
				auto& transform = t.getTransform();

				glm::vec3 velocity(0.f);

				if (registry.has<RigidBodyComponent>(entity))
				{
					auto& rb = registry.get<RigidBodyComponent>(entity);
					auto rbVel = rb.m_body->getLinearVelocity();
					velocity = glm::vec3(rbVel.x, rbVel.y, rbVel.z);
				}

				audioManager->set3dListenerAndOrientation(transform, velocity);
			}

			// PLAYABLE AUDIO
			auto& playView = registry.view<TransformComponent, playableSoundComponent>();
			
			for (auto entity : playView)
			{
				auto&[t, playable] = registry.get<TransformComponent, playableSoundComponent>(entity);
				auto& transform = t.getTransform();

				glm::vec3 position = glm::vec3(transform[3][0], transform[3][1], transform[3][2]);
				glm::vec3 velocity(0.f);

				if (registry.has<RigidBodyComponent>(entity))
				{
					auto& rb = registry.get<RigidBodyComponent>(entity);
					auto rbVel = rb.m_body->getLinearVelocity();
					velocity = glm::vec3(rbVel.x, rbVel.y, rbVel.z);
				}
				audioManager->setChannel3dAttributes(playable.channel, position, velocity);
			}

			// AUDIO EVENTS
			auto& eventView = registry.view<ParametricSoundComponent>();

			for (auto entity : eventView)
			{
				auto&[t, paraAudio] = registry.get<TransformComponent, ParametricSoundComponent>(entity);
				auto& transform = t.getTransform();

				glm::vec3 position = glm::vec3(transform[3][0], transform[3][1], transform[3][2]);
				glm::vec3 velocity(0.f);

				if (registry.has<RigidBodyComponent>(entity))
				{
					auto& rb = registry.get<RigidBodyComponent>(entity);
					auto rbVel = rb.m_body->getLinearVelocity();
					velocity = glm::vec3(rbVel.x, rbVel.y, rbVel.z);
				}

				audioManager->setEvent3DAttributes(paraAudio.eventName, transform, velocity);
			}

		}
	}

	AudioOcclusionComponent::AudioOcclusionComponent(const char * pName, const AudioGeometryDefinition & geometryDef) :
		name(pName)
	{
		auto& audioManager = Application::getInstance().getAudioManager();

		audioManager->addGeometry(name, geometryDef);
	}

}
