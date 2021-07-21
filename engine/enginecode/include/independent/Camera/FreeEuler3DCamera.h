/*! \file FreeEuler3DCamera.h */
#pragma once

#include "Camera/Camera.h"

namespace Engine
{
	class FreeEuler3DCamera : public CameraController
	{
	public:
		FreeEuler3DCamera(float fovY, float aspectRatio, float nearClip, float farClip); //!< Constrcutor with floats
		virtual void onUpdate(float t) override; //!< Update function
		virtual glm::vec3 getPosition() override { return m_position; } //!< Getter for position
	private:
		float m_rotationSpeed = 1.f; //!< Rotation Speed
		float m_translationSpeed = 20.f; //!< Movement Speed
		glm::mat4 m_transform; //!< Transform Matrix
		glm::vec2 m_lastMousePos; //!< Last mouse position
		float m_rotationX = 0.f; //!< Rotation X
		float m_rotationY = 0.f; //!< Rotation Y
		float m_rotationZ = 0.f; //!< Rotation Z
		float sensitivity = 20; //!< Sensitivity
		glm::mat4 m_orientation; //!< Orientation
		glm::vec3 m_position = { 0, 0, 0 }; //!< Camera Position
	};
}