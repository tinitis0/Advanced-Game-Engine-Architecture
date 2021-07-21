/*! \file FreeEuler3DCameraController.cpp */

#include "engine_pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera/FreeEuler3DCamera.h"
#include "independent/core/inputPoller.h"
#include "independent/Events/codes.h"

namespace Engine
{
	FreeEuler3DCamera::FreeEuler3DCamera(float fovY, float aspectRatio, float nearClip, float farClip)
	{
		m_camera.projection = glm::perspective(fovY, aspectRatio, nearClip, farClip); //!< Projection is perspective
		m_camera.view = glm::mat4(1.f); //!< Mat4 of 1
		m_lastMousePos = InputPoller::getMousePos(); //!< Mouse last position
	}

	void Engine::FreeEuler3DCamera::onUpdate(float t)
	{
		glm::vec3 right = { m_transform[0][0], m_transform[0][1], m_transform[0][2] }; //!< Right movement
		glm::vec3 forward = { -m_transform[2][0], -m_transform[2][1], -m_transform[2][2] }; //!< Forward Movement


		// Left and Right Movement
		if (InputPoller::isKeyPressed(NG_KEY_A)) m_position -= (right * m_translationSpeed * t); //!< A Key Press = Left Movement
		if (InputPoller::isKeyPressed(NG_KEY_D)) m_position += (right * m_translationSpeed * t); //!< D Key Press = Right Movement 
		// Forward and Back Movement
		if (InputPoller::isKeyPressed(NG_KEY_W)) m_position += (forward * m_translationSpeed * t); //!< W Key Press = Forward Movement
		if (InputPoller::isKeyPressed(NG_KEY_S)) m_position -= (forward * m_translationSpeed * t); //!< S Key Press = Backwards Movement
	
		// Up and Down
		if (InputPoller::isKeyPressed(NG_KEY_UP)) m_position += (glm::vec3(0.0f, 1.0f, 0.0f) * m_translationSpeed * t); //!< W Key Press = Forward Movement
		if (InputPoller::isKeyPressed(NG_KEY_DOWN)) m_position -= (glm::vec3(0.0f, 1.0f, 0.0f) * m_translationSpeed * t); //!< S Key Press = Backwards Movement

		if (InputPoller::isKeyPressed(NG_KEY_RIGHT))  m_rotationY -= m_rotationSpeed * t;; //!< W Key Press = Forward Movement
		if (InputPoller::isKeyPressed(NG_KEY_LEFT)) m_rotationY += m_rotationSpeed * t; //!< S Key Press = Backwards Movement
		// Rotation
		if (InputPoller::isKeyPressed(NG_KEY_E)) m_rotationZ += m_rotationSpeed * t; //!< E Key Press = Right Tilt
		if (InputPoller::isKeyPressed(NG_KEY_Q)) m_rotationZ -= m_rotationSpeed * t; //!< Q Key Press = Left Tilt
	
		glm::vec2 currentMousePos = InputPoller::getMousePos(); //!< Mouse last position
		glm::vec2 deltaMousePos = currentMousePos - m_lastMousePos; //!< Direction mouse has moved
		deltaMousePos /= glm::vec2(900.f, 700.f); //!< Mouse Pos in screen

		m_rotationX -= sensitivity * deltaMousePos.y * t; //!< Rotation X
		m_rotationY -= sensitivity * deltaMousePos.x * t; //!< Rotation Y

		m_lastMousePos = currentMousePos; //!< Update the last mouse pos

		glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_rotationX, glm::vec3(1.f, 0.f, 0.f)); //!< Rotation X
		glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_rotationY, glm::vec3(0.f, 1.f, 0.f)); //!< Rotation Y
		glm::mat4 rotZ = glm::rotate(glm::mat4(1.f), m_rotationZ, glm::vec3(0.f, 0.f, 1.f)); //!< Rotation Z
	
		m_orientation = rotX * rotY * rotZ; //!< Multiplying all rotation matrixes

		m_transform = glm::translate(glm::mat4(1.f), m_position) * m_orientation; //!< Movement
		m_camera.view = inverse(m_transform); //!< Cam View
	}
}