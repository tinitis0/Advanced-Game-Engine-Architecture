#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	class TransformComponent
	{
	public:
		glm::vec3 translation = { 0.f, 0.f, 0.f }; //!< Translation predefinition
		glm::vec3 scale = { 1.f, 1.f, 1.f }; //!< Scale predefinition
		TransformComponent() { transform = glm::mat4(1.0f); } //!< Plain transform component constructor, gives a transform of nothing but 1s.
		TransformComponent(glm::vec3 t, glm::vec3 r, glm::vec3 s) //!< Transform constructor that takes the position, rotation and scale
		{
			rotEuler = r; //!< Set rotEuler to r
			setTransform(t, r, s); //!< Set the transform using the given values
		} // Transform with translate, rotation & scale

		glm::mat4& setTransform(glm::vec3 t, glm::vec3 r, glm::vec3 s)
		{
			translation = t;		//!< Set the new position
			rotation = glm::quat(r); //!< Set the new rotation
			scale = s;				//!< Set the new scale

			return updateTransform(); //!< Update the transform
		} // Setting the transform using the translation, rotation & scale

		glm::mat4& setTransform(glm::vec3 t, glm::quat r, glm::vec3 s)
		{
			translation = t; //!< Set the new position
			rotation = r;	 //!< Set the new rotation
			scale = s;		 //!< Set the new scale

			return updateTransform(); //!< Update the transform
		} // Setting the transform using the translation, rotation & scale

		glm::mat4& setTransform(glm::mat4& parentTransform, glm::vec3 t, glm::quat r, glm::vec3 s)
		{
			translation = t; //!< Set the new position
			rotation = r;	 //!< Set the new rotation
			scale = s;		 //!< Set the new scale

			return updateTransform(parentTransform); //!< Update the transform with the parent's transform
		} // Setting the transform using the translation, rotation & scale

		glm::mat4& setTransform(glm::mat4& parentTransform, glm::vec3 t, glm::vec3 r, glm::vec3 s)
		{
			translation = t; //!< Set the new position
			rotation = glm::quat(r); //!< Set the new rotation
			scale = s; //!< Set the new scale

			return updateTransform(parentTransform); //!< Update the transform with the parent's transform
		} // Setting the transform using the translation, rotation & scale

		glm::mat4& updateTransform()
		{
			//glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), rotation.x, { 1.f, 0.f, 0.f });
			//glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), rotation.y, { 0.f, 1.f, 0.f });
			//glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), rotation.z, { 0.f, 0.f, 1.f });
			//glm::mat4 rot = rotX * rotY * rotZ;

			transform = glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale); //!< Create the new transform using the position, rotation and scale

			return transform; //!< Return the new transform
		}

		glm::vec3& getPosition() //!< Getter for the position
		{
			return translation; //!< Return the position
		}

		glm::mat4& setPosition(glm::vec3& position)
		{
			translation = position; //!< set the new position
			return updateTransform(); //!< Update the transform with the new position
		}

		glm::mat4& updateTransform(glm::mat4& parentTransform) //!< update transform with a parent's transform
		{
			transform = parentTransform * updateTransform(); //!< Multiply the updated transform by the parent's transform to keep it updated with the parent's transform

			return transform; //!< Return the new transform
		} // Updating with a parent transform

		glm::mat4& getTransform() { return transform; } //!< Getter for the transform

		void addRotation(glm::vec3& eulerAngles)
		{
			glm::quat rotationDelta(eulerAngles); //!< Turn the given euler angles into a quaternion
			rotation *= rotationDelta; //!< apply the new rotation
		}

		glm::mat4& getRotation() { return glm::toMat4(rotation); } //!< Getter for the rotation as a matrix 4x4

		glm::quat& getRotationQuat() { return rotation; } //!< Getter for the rotation quaternion

		glm::vec3& getRotationEuler()  //!< Getter for the rotation in euler angles
		{
			return rotEuler; //!< Return the rotation in euler angles.
		}

		glm::mat4& setRotationDegrees(glm::vec3 r)
		{
			r = glm::vec3(glm::radians(r.x), glm::radians(r.y), glm::radians(r.z)); //!< Turn all of the rotation vector's angles into radians from degrees
			rotation = glm::quat(r); //!< Set rotation to the new rotation (Turned into a quaternion)								
			return updateTransform();  //!< Update the transform with the new quaternion rotation
		}

		glm::mat4& setRotation(glm::vec3 r)
		{
			rotation = glm::quat(r); //!< Set rotation to the new rotation (Turned into a quaternion)
			return updateTransform(); //!< Update the transform with the new quaternion rotation 
		}

		glm::mat4& setRotation(glm::mat4 r)
		{
			rotation = glm::quat(r); //!< Set rotation to the new rotation (Turned into a quaternion)
			return updateTransform(); //!< Update the transform with the new quaternion rotation
		}

		glm::vec3& getScale()
		{
			return scale; //!< Getter for the scale
		}

		glm::mat4& setScale(glm::vec3 _scale)
		{
			scale = _scale; //!< Set the scale to the new scale
			return updateTransform(); //!< Update the transforms with the new scale
		}

	private:
		glm::mat4 transform; //!< Transform of the object
		glm::quat rotation; //!< Quaternion rotation of the object
		glm::vec3 rotEuler; //!< Rotation of the object in euler angles
	};
}