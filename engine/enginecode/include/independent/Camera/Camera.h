/*! \file Camera.h */
#pragma once

#include "Events/Event.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	/*! \class Camera */
	class Camera
	{
	public:
		glm::mat4 view; //!< View
		glm::mat4 projection; //!< Projection
		void updateView(const glm::mat4& transform)
		{
			view = glm::inverse(transform); //!< View is the inverse of the transform
		} //!< Update the view
	};

	/*! \class CameraController */
	class CameraController
	{
	public:
		Camera& getCamera() { return m_camera; } //!< Getter for camera
		virtual void onUpdate(float t) {}; //!< Update Camera
		virtual void onEvent(Events& e) {}; //!< Update Event
		virtual glm::vec3 getPosition() { return glm::vec3(0.f); };

	protected:
		Camera m_camera; //!< Camera
	};
}