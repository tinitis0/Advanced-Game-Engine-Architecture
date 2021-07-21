/*! \file shaderDataType.h */
#pragma once
#include <cstdint>

namespace Engine
{
	/*! \enum class shaderDataType
	*/
	enum class shaderDataType
	{
		None = 0, Byte, Byte2, Byte3, Byte4, Short, Short2, Short3, Short4, 
		Float, Float2, Float3, Float4, Mat3, Mat4, Int
	};

	namespace SDT
	{
		static uint32_t size(shaderDataType type)
		{
			switch (type)
			{
				// Byte - 1 byte
			case shaderDataType::Byte: return 1; //!< Byte = 1 bytes
			case shaderDataType::Byte2: return 1 * 2; //!< Byte 2 = 2 bytes
			case shaderDataType::Byte3: return 1 * 3; //!< Byte 3 = 3 bytes
			case shaderDataType::Byte4: return 1 * 4; //!< Byte 4 = 4 bytes
				// Short - 2 byte
			case shaderDataType::Short: return 2; //!< Short = 2 bytes
			case shaderDataType::Short2: return 2 * 2; //!< Short 2 = 4 bytes
			case shaderDataType::Short3: return 2 * 3; //!< Short 3 = 6 bytes
			case shaderDataType::Short4: return 2 * 4; //!< Short 4 = 8 bytes
				// Float - 4 bytes
			case shaderDataType::Float: return 4; //!< Float = 4 bytes
			case shaderDataType::Float2: return 4 * 2; //!< Float 2 = 8 bytes
			case shaderDataType::Float3: return 4 * 3; //!< Float 3 = 12 bytes
			case shaderDataType::Float4: return 4 * 4; //!< Flat 4 = 16 bytes
				// Mat - Matrix
			case shaderDataType::Mat3: return 4 * 3 * 3; //!< 4 by 3 by 3 matrix
			case shaderDataType::Mat4: return 4 * 4 * 4; //!< 4 by 4 by 4 matrix
				// Int - 4 bytes
			case shaderDataType::Int: return 4; //!< Integer = 4 bytes
			default: return 0; //!< Default return 0

			}
		}


		static uint32_t componentCount(shaderDataType type)
		{
			switch (type)
			{
				// Byte
			case shaderDataType::Byte: return 1; //!< Return one component
			case shaderDataType::Byte2: return 2; //!< Return two component
			case shaderDataType::Byte3: return 3; //!< Return three component
			case shaderDataType::Byte4: return 4; //!< Return four component
				// Short
			case shaderDataType::Short: return 1; //!< Return one component
			case shaderDataType::Short2: return 2; //!< Return two component
			case shaderDataType::Short3: return 3; //!< Return three component
			case shaderDataType::Short4: return 4; //!< Return four component
				// Float
			case shaderDataType::Float: return 1; //!< Return one component
			case shaderDataType::Float2: return 2; //!< Return two component
			case shaderDataType::Float3: return 3; //!< Return three component
			case shaderDataType::Float4: return 4; //!< Return four component
				// Mat - Matrix
			case shaderDataType::Mat3: return 3 * 3; //!< 3 by 3 components
			case shaderDataType::Mat4: return 4 * 4; //!< 4 by 4 components
				// Int
			case shaderDataType::Int: return 1; //!< Return one component
			default: return 0;
			}
		}

		static uint32_t std140Alignment(shaderDataType type)
		{
			switch (type)
			{
				// Byte - 1 byte
			case shaderDataType::Byte: return 1; //!< Byte = 1 bytes
			case shaderDataType::Byte2: return 1 * 2; //!< Byte 2 = 2 bytes
			case shaderDataType::Byte3: return 1 * 4; //!< Byte 3 = 3 bytes : 3 component has to be multiplied by 4 for alignment
			case shaderDataType::Byte4: return 1 * 4; //!< Byte 4 = 4 bytes
				// Short - 2 byte
			case shaderDataType::Short: return 2; //!< Short = 2 bytes
			case shaderDataType::Short2: return 2 * 2; //!< Short 2 = 4 bytes
			case shaderDataType::Short3: return 2 * 4; //!< Short 3 = 6 bytes : 3 component has to be multiplied by 4 for alignment
			case shaderDataType::Short4: return 2 * 4; //!< Short 4 = 8 bytes
				// Float - 4 bytes
			case shaderDataType::Float: return 4; //!< Float = 4 bytes
			case shaderDataType::Float2: return 4 * 2; //!< Float 2 = 8 bytes
			case shaderDataType::Float3: return 4 * 4; //!< Float 3 = 12 bytes : 3 component has to be multiplied by 4 for alignment
			case shaderDataType::Float4: return 4 * 4; //!< Flat 4 = 16 bytes
				// Mat - Matrix
			case shaderDataType::Mat3: return 4 * 3 * 3; //!< 4 by 3 by 3 matrix
			case shaderDataType::Mat4: return 4 * 4 * 4; //!< 4 by 4 by 4 matrix
			default: return 0; //!< Default return 0

			}
		}
	}
}