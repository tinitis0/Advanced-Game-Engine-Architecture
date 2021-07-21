/*! \file RenderAPI.h*/
#pragma once

namespace Engine
{
	/*! \class RenderAPI
	* Used to decide what Render API is used
	*/
	class RenderAPI
	{
	public:
		enum class API { None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3 }; //!< Enum for all API's
		inline static API getAPI() { return s_API; } //!< Getter for API
	private:
		static API s_API; //!< Current API being used
	};
}