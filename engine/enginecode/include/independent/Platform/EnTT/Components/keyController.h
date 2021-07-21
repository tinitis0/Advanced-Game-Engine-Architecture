#pragma once

#include <stdint.h>
#include "Events/codes.h"

namespace Engine
{
	class KeyController
	{
	public:
		KeyController() = default; //!< Default constructor
		KeyController(uint32_t flags) { movementFlags = flags; } //!< Constructor that takes flags
		// Movement Keys
		int32_t forwardKey = NG_KEY_W;
		int32_t leftKey = NG_KEY_A;
		int32_t backKey = NG_KEY_S;
		int32_t rightKey = NG_KEY_D;
		int32_t rollLeft = NG_KEY_Q;
		int32_t rollRight = NG_KEY_E;
		int32_t yawUp = NG_KEY_LEFT;
		int32_t yawDown = NG_KEY_RIGHT;
		int32_t pitchUp = NG_KEY_UP;
		int32_t pitchDown = NG_KEY_DOWN;
		uint32_t movementFlags;

		// Flags
		static const uint32_t forwardBackFlag = 1 << 0;
		static const uint32_t leftRightFlag = 1 << 1;
		static const uint32_t rollFlag = 1 << 2;
		static const uint32_t pichFlag = 1 << 3;
		static const uint32_t yawFlag = 1 << 4;
		// Flags with & without rotation
		static const uint32_t stdNoRotationFlags = forwardBackFlag | leftRightFlag;
		static const uint32_t stdWithRotationFlags = forwardBackFlag | leftRightFlag | rollFlag | pichFlag | yawFlag;
		// Setting Keys
		bool isSet(uint32_t flags)
		{
			return flags & movementFlags;
		}
	};
}