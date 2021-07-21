/*! \file Free2DOrthographicCamera.h*/
#pragma once
#include "Camera.h"

namespace Engine
{
	struct Free2DParams
	{
		float m_rotation = 0.f; //!< Rotation Speed
		float m_translationSpeed = 40.f; //!< Movement Speed
		glm::vec3 m_position = { 0, 0, 0 }; //!< Cam Position
		float width = 4.f;
		float height = 3.f;
		float top = 1024.f;
		float bottom = 0.f;
		float left = 0.f;
		float right = 800.f;
	};

	/*! \class Free2DOrthographicCamera */
	class Free2dOrthographicCamera : public CameraController
	{
	public:
		Free2dOrthographicCamera(Free2DParams& params); //!< Constructor that takes 4 floats
		virtual void onUpdate (float t) override; //!< On Update 
	private:
		Free2DParams m_params;
		float m_aspectRatio;
	};
}