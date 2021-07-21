/*! \file cameras.h */
#pragma once

#include "Camera/Camera.h"
#include <glm/glm.hpp>

namespace Engine
{
	enum class CameraTypes {FreeEuler, Follow};

	struct PerspectiveCameraParams
	{
		float fovY = 45.f; //!< FOV
		glm::vec2 size = { 800.f, 600.f }; //!< Size of the window for the camera to match
		float nearClip = 0.1f; //!< Near plane of the camera
		float farClip = 100.f; //!< Far plane of the camera
		glm::vec3 offset = { 0.0f, 0.0f, 0.0f }; //!< Offset of the camera
		CameraTypes cameraType = CameraTypes::FreeEuler; //!< Type of camera, default a free euler
	};

	class PerspectiveCameraComponent
	{
	public:
		PerspectiveCameraComponent(PerspectiveCameraParams& params, glm::mat4 transform) : settings(params) //!< Constructor
		{
			view = glm::inverse(transform); //!< Set the view
			projection = glm::perspective(settings.fovY, settings.size.x / settings.size.y, settings.nearClip, settings.farClip); //!< Set the projection
		}

		glm::mat4 view; //!< View matrix
		glm::mat4 projection; //!< Projection matrix

		PerspectiveCameraParams settings; //!< Camera params
	};
}
