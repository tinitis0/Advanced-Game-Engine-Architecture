#pragma once

#include "Rendering/vertexArray.h"
namespace Engine
{
	class ResourceManager
	{
	private:
		float force = 0; //!< Current force value
		uint8_t currentLevel = 1; //!< Current level
		//uint8_t as it will only ever be 1, 2 or 3
	public:
		int maxStrokes = 2; //!< Maximum strokes
		int strokes = 0; //!< Strokes taken
		
		bool reset = false; //!< Should the ball be reset?
		bool nextLevel = false; //!< Should the ball move to the next level?
		bool finished = false; //!< Is the game finished?

		float getForce() { return force; } //!< Getter for the force
		void setForce(float _force) { force = _force; } //!< Setter for the force
		uint8_t getCurrentLevel() { return currentLevel; } //!< Getter for the current level
		void setLevel(uint8_t newlvl) { currentLevel = newlvl; } //!< Setter for the level

		std::shared_ptr<vertexArray> sphereVAO; //!< Sphere's vertex array, set in EnTT layer

	};
}