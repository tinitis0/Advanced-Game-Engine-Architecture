/*! \file FollowCamera3D.cpp */

#include "engine_pch.h"
#include "Camera/FollowCamera3D.h"
#include "independent/core/inputPoller.h"
#include "independent/Events/codes.h"

Engine::FollowCamera3D::FollowCamera3D(float fovY, float aspectRatio, float nearClip, float farClip, glm::mat4 * transform, glm::vec3 offset)
{
	m_entityTransform = transform;
	m_offset = offset;
	m_camera.projection = glm::perspective(fovY, aspectRatio, nearClip, farClip);

	angle = atan2(-m_offset.z, m_offset.x);

	glm::vec3 right = { (*m_entityTransform)[0][0], (*m_entityTransform)[0][1], (*m_entityTransform)[0][2] };
	glm::vec3 up = { (*m_entityTransform)[1][0], (*m_entityTransform)[1][1], (*m_entityTransform)[1][2] };
	glm::vec3 forward = { (*m_entityTransform)[2][0], (*m_entityTransform)[2][1], (*m_entityTransform)[2][2] };
	m_entityPosition = { (*m_entityTransform)[3][0], (*m_entityTransform)[3][1], (*m_entityTransform)[3][2] };

	glm::vec3 posDelta(0.f);
	posDelta += forward * m_offset.z;
	posDelta += right * m_offset.x;
	posDelta += glm::vec3(0, 1, 0) * m_offset.y;

	m_position = m_entityPosition + posDelta;
	
	glm::vec3 camForward = -posDelta;
	glm::vec3 camRight = glm::cross({ 0, 1, 0 }, posDelta);
	glm::vec3 camUp = glm::vec3(0, 1, 0); //glm::normalize(glm::cross(camRight, camForward));

	m_camera.view = glm::lookAt(m_position, m_entityPosition, camUp);
}

void Engine::FollowCamera3D::onUpdate(float t)
{
	float speed = 40.f;

	if (InputPoller::isKeyPressed(NG_KEY_LEFT_CONTROL))
	{
		speed = 10.f;
	}

	if (InputPoller::isKeyPressed(NG_KEY_LEFT_SHIFT))
	{
		speed = 80.f;
	}

	if (InputPoller::isKeyPressed(NG_KEY_LEFT))
	{
		angle = angle - glm::radians(speed * t);
		if (angle < -180)
		{
			angle = angle + 360;
		}
		float mag = sqrtf(m_offset.x * m_offset.x + m_offset.z * m_offset.z);
		m_offset.x = cos(angle) * mag;
		m_offset.z = -sin(angle) * mag;
	}
	if (InputPoller::isKeyPressed(NG_KEY_RIGHT))
	{
		angle = angle + glm::radians(speed * t);
		if (angle > 180)
		{
			angle -= 360;
		}
		float mag = sqrtf(m_offset.x * m_offset.x + m_offset.z * m_offset.z);
		m_offset.x = cos(angle) * mag;
		m_offset.z = -sin(angle) * mag;
	}
	glm::vec3 right = { (*m_entityTransform)[0][0], (*m_entityTransform)[0][1], (*m_entityTransform)[0][2] };
	glm::vec3 up = { (*m_entityTransform)[1][0], (*m_entityTransform)[1][1], (*m_entityTransform)[1][2] };
	glm::vec3 forward = { (*m_entityTransform)[2][0], (*m_entityTransform)[2][1], (*m_entityTransform)[2][2] };
	m_entityPosition = { (*m_entityTransform)[3][0], (*m_entityTransform)[3][1], (*m_entityTransform)[3][2] };

	glm::vec3 posDelta(0.f);
	posDelta += glm::vec3(0, 0, 1) * m_offset.z; //forward * m_offset.z;
	posDelta += right * m_offset.x; //right * m_offset.x;
	posDelta += glm::vec3(0, 1, 0) * m_offset.y;

	m_position = m_entityPosition + m_offset;

	glm::vec3 camForward = -posDelta;
	glm::vec3 camRight = glm::cross({ 0, 1, 0 }, posDelta);
	glm::vec3 camUp = glm::vec3(0, 1, 0); //glm::normalize(glm::cross(camRight, camForward));

	m_camera.view = glm::lookAt(m_position, m_entityPosition, camUp);
}
