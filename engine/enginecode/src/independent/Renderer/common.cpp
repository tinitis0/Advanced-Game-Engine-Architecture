#include "engine_pch.h"
#include "Platform/Renderer/RendererCommon.h"
#include "Include.h"
#include "core/application.h"

namespace Engine
{
	std::array<int16_t, 3> Normal::normalise(const glm::vec3& normal)
	{
		std::array<int16_t, 3> result;

		if (normal.x == 1.0) result.at(0) = INT16_MAX; //!< INT Max Value
		else if (normal.x == -1.0) result.at(0) = INT16_MIN; //!< INT Min Value
		else result.at(0) = static_cast<int16_t> (normal.x * static_cast<float> (INT16_MAX)); //!< Result is normal.x multiplied by converted INT16_MAX to float

		if (normal.y == 1.0) result.at(1) = INT16_MAX; //!< INT Max Value
		else if (normal.y == -1.0) result.at(1) = INT16_MIN; //!< INT Min Value
		else result.at(1) = static_cast<int16_t> (normal.y * static_cast<float> (INT16_MAX)); //!< Result is normal.y multiplied by converted INT16_MAX to float

		if (normal.z == 1.0) result.at(2) = INT16_MAX; //!< INT Max Value
		else if (normal.z == -1.0) result.at(2) = INT16_MIN; //!< INT Min Value
		else result.at(2) = static_cast<int16_t> (normal.z * static_cast<float> (INT16_MAX)); //!< Result is normal.z multiplied by converted INT16_MAX to float

		return result;
	} //!< Normalise array of int16_t of size 3

	std::array<int16_t, 2> Normal::normalise(const glm::vec2& UV)
	{
		std::array < int16_t, 2> result;

		if (UV.x == 1.0) result.at(0) = INT16_MAX; //!< INT Max Value
		else if (UV.x == -1.0) result.at(0) = INT16_MIN; //!< INT Min Value
		else result.at(0) = static_cast<int16_t> (UV.x * static_cast<float> (INT16_MAX)); //!< Result is UV.x multiplied by converted INT16_MAX to float

		if (UV.y == 1.0) result.at(1) = INT16_MAX; //!< INT Max Value
		else if (UV.y == -1.0) result.at(1) = INT16_MIN; //!< INT Min Value
		else result.at(1) = static_cast<int16_t> (UV.y * static_cast<float> (INT16_MAX)); //!< Result is UV.y multiplied by converted INT16_MAX to float

		return result;
	} //!< Normalise array of int16_t of size 2

	uint32_t Normal::pack(const glm::vec4& colour)
	{
		uint32_t result = 0; //!< Result defaulted to 0
		uint32_t red = (static_cast<uint32_t>(colour.r * 255.0f)) << 0; //!< Coverts colour red from 0 - 1 to 0 - 255 (000R)
		uint32_t green = (static_cast<uint32_t>(colour.g * 255.0f)) << 8; //!< Coverts colour green from 0 - 1 to 0 - 255 (00B0)
		uint32_t blue = (static_cast<uint32_t>(colour.b * 255.0f)) << 16; //!< Coverts colour blue from 0 - 1 to 0 - 255 (0B00)
		uint32_t alpha = (static_cast<uint32_t>(colour.a * 255.0f)) << 24; //!< Coverts alpha from 0 - 1 to 0 - 255 (A000)

		result = (red | green | blue | alpha);
		return result;
	}

	uint32_t Normal::pack(const glm::vec3& colour)
	{
		return pack({ colour.x, colour.y,colour.z, 1.0f }); //!< RGBA
	}
}