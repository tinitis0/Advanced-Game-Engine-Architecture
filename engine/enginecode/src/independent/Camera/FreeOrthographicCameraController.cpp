/*! \file FreeOrthographicCameraController.cpp */

#include "engine_pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera/Free2DOrthographicCamera.h"
#include "independent/core/inputPoller.h"
#include "independent/Events/codes.h"

namespace Engine
{
	Free2dOrthographicCamera::Free2dOrthographicCamera(Free2DParams& params) : m_params(params), m_aspectRatio(params.width / params.height)
	{
		m_camera.projection = glm::ortho(params.left, params.right, params.top, params.bottom);
		m_camera.view = glm::mat4(1.f); //!< Mat4 of 1
	}

	void Free2dOrthographicCamera::onUpdate(float t)
	{
		if (InputPoller::isKeyPressed(NG_KEY_W)) 
		{
			m_params.m_position.x += -sin(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for downwards movement on x
			m_params.m_position.y +=  cos(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for downwards movement on Y
		} //!< If W is pressed

		if (InputPoller::isKeyPressed(NG_KEY_S))
		{
			m_params.m_position.x -= -sin(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for forward movement on x
			m_params.m_position.y -= cos(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for forward movement on y
		} //!< If S is pressed

		if (InputPoller::isKeyPressed(NG_KEY_A))
		{
			m_params.m_position.x += cos(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for right movement on x
			m_params.m_position.y += sin(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for right movement on y
		}  //!< If A is pressed

		if (InputPoller::isKeyPressed(NG_KEY_D))
		{
			m_params.m_position.x -= cos(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for left movement on x
			m_params.m_position.y -= sin(glm::radians(m_params.m_rotation)) * m_params.m_translationSpeed * t; //!< Calculation for left movement on y
		}  //!< If D is pressed

		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_params.m_position.x, m_params.m_position.y, 1.f)); //!< Translate Camera (Movement Calculation)
		glm::mat4 rotate = glm::rotate(glm::mat4(1.f), m_params.m_rotation, { 0.f, 0.f, 1.f }); //!< Rotate Camera (Rotation Calculation)
		m_camera.view = glm::inverse(translate * rotate); //!< View is inverse of translate multiplied by rotate
	}
}