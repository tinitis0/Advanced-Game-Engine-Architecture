/*! \file Follow Camera3D.h */
#pragma once

#include "Camera/Camera.h"

namespace Engine
{
	class FollowCamera3D : public CameraController
	{
	public:
		FollowCamera3D(float fovY, float aspectRatio, float nearClip, float farClip, glm::mat4 * transform, glm::vec3 offset); //!< Constructor
		virtual void onUpdate(float t) override; //!< On Update Function
		glm::mat4 *getEntity() { return m_entityTransform; } //!< Getter for entity
		glm::vec3 getOffset() { return m_offset; }
	private:
		glm::vec3 m_entityPosition; //!< Entity (Player) Position
		glm::mat4 *m_entityTransform; //!< Entity Transform
		glm::vec3 m_offset; //!< Offset
		glm::vec3 m_position; //!< Position
		float movementSpeed = 20.f; //!< Movement Speed
		float angle = 0.f;
	};
}