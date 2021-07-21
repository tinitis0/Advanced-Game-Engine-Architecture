#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <map>
#include "systems/logger.h"
#include "independent/Rendering/VertexNormalised.h"
#include "Platform/Renderer/3D_Renderer.h"
#include "include/independent/Platform/EnTT/Components/render.h"
namespace Engine {


	struct Mesh
	{
		std::vector<VertexNormalised> vertices;
		std::vector<uint32_t> indices;
		std::shared_ptr<Material> material;
	};

	
	namespace Loader
	{
		static std::string s_workingDirectory = "";
		static std::vector<std::shared_ptr<Material>> s_material;
		static std::vector<glm::vec4> s_transfroms;
		

		static void ASSIMPProcessMesh(aiMesh *assimpMesh, const aiScene *scene, Engine::Mesh& mesh, glm::mat4& meshTranform)
		{
			std::multimap<uint32_t, std::pair<uint32_t, float>> vertexBoneWeights;
			Logger::info("BONES");
			// Iterate through bones
			for (uint32_t i = 0; i < assimpMesh->mNumBones; i++)
			{
				aiBone* bone = assimpMesh->mBones[i];

				aiMatrix4x4 transform = bone->mOffsetMatrix;
				Logger::info("RELATIVE TRANSFORM FOR BONE: {0} Name: {1}", i, bone->mName.C_Str());
				Logger::info("{0} {1} {2} {3}", transform.a1, transform.a2, transform.a3, transform.a4);
				Logger::info("{0} {1} {2} {3}", transform.b1, transform.b2, transform.b3, transform.b4);
				Logger::info("{0} {1} {2} {3}", transform.c1, transform.c2, transform.c3, transform.c4);
				Logger::info("{0} {1} {2} {3}", transform.d1, transform.d2, transform.d3, transform.d4);

				Logger::info("WEIGHTS");
				for (uint32_t j = 0; j < bone->mNumWeights; j++)
				{
					Logger::info("Bone idx: {0} VertexID: {1} Weight: {2}", i, bone->mWeights[j].mVertexId, bone->mWeights[j].mWeight);
					vertexBoneWeights.insert(std::pair<uint32_t, std::pair<uint32_t, float>>
						(bone->mWeights[j].mVertexId, std::pair<uint32_t, float>(i, bone->mWeights[j].mWeight)));
				}
			}

			// Find vertex properties
			bool hasPositions = assimpMesh->HasPositions();
			bool hasNormals = assimpMesh->HasNormals();
			bool hasTangents = assimpMesh->HasTangentsAndBitangents();
			uint32_t numColourChannels = assimpMesh->GetNumColorChannels();
			uint32_t numUVChannels = assimpMesh->GetNumUVChannels();

			Logger::info("VERTICES");
			// Iterate through vertices
			for (uint32_t i = 0; i < assimpMesh->mNumVertices; i++)
			{
				// Get vertex data
				glm::vec3 position, normal, tangent, biTangent;
				std::vector<glm::vec4> colours(numColourChannels);
				std::vector<glm::vec2> texCoords(numUVChannels);

				if (hasPositions) position = glm::vec3(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z);
				if (hasNormals) normal = glm::vec3(assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z);
				if (hasTangents)
				{
					tangent = glm::vec3(assimpMesh->mTangents[i].x, assimpMesh->mTangents[i].y, assimpMesh->mTangents[i].z);
					biTangent = glm::vec3(assimpMesh->mBitangents[i].x, assimpMesh->mBitangents[i].y, assimpMesh->mBitangents[i].z);
				}

				for (uint32_t j = 0; j < numColourChannels; j++)
				{
					colours[j].r = assimpMesh->mColors[j][i].r;
					colours[j].g = assimpMesh->mColors[j][i].g;
					colours[j].b = assimpMesh->mColors[j][i].b;
					colours[j].a = assimpMesh->mColors[j][i].a;
				}

				for (uint32_t j = 0; j < numUVChannels; j++)
				{
					texCoords[j] = glm::vec2(assimpMesh->mTextureCoords[j][i].x, assimpMesh->mTextureCoords[j][i].y);
				}

				mesh.vertices.push_back(VertexNormalised(position, Normal::normalise(normal), Normal::normalise(texCoords[0])));

				uint32_t boneIds[4] = { 0, 0, 0, 0 };
				float boneWeights[4] = { 0.f, 0.f, 0.f, 0.f };

				auto boneData = vertexBoneWeights.equal_range(i); // i is the vertexID
				int j = 0;
				for (auto it = boneData.first; it != boneData.second; ++it)
				{
					if (j > 4) Logger::error("More than four bones influence this vertex");
					auto pair = it->second;
					boneIds[j] = pair.first;
					boneWeights[j] = pair.second;
					j++;
				}

				// Log part - assume postion, normal and UV coords
				if (texCoords.size() > 0)Logger::info("P x:{0}, y:{1}, z:{2}, N x:{3}, y:{4}, z:{5}, T u:{6}, v{7}", position.x, position.y, position.z, normal.x, normal.y, normal.z, texCoords[0].x, texCoords[0].y);
				else Logger::info("P x:{0}, y:{1}, z:{2}, N x:{3}, y:{4}, z:{5}, NO TEXTURE", position.x, position.y, position.z, normal.x, normal.y, normal.z);
				if (j != 0)Logger::info("Bone IDs: {0}, {1}, {2}, {3} Weights: {4}, {5}, {6}, {7}", boneIds[0], boneIds[1], boneIds[2], boneIds[3], boneWeights[0], boneWeights[1], boneWeights[2], boneWeights[3]);
			}

			Logger::info("INDICES");
			uint32_t elementCount = 0;
			for (uint32_t i = 0; i < assimpMesh->mNumFaces; i++)
			{
				aiFace face = assimpMesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (uint32_t j = 0; j < face.mNumIndices; j++)
				{
					uint32_t index = face.mIndices[j]; elementCount++;
				}

				// Log part - assume all faces are trinalge and therefore ahve 3 indices
				Logger::info("Face {0}: {1} {2} {3}", i, face.mIndices[0], face.mIndices[1], face.mIndices[2]);
				mesh.indices.push_back(face.mIndices[0]);
				mesh.indices.push_back(face.mIndices[1]);
				mesh.indices.push_back(face.mIndices[2]);
			}
			Logger::info("Num vertices {0} Num indices {1}", assimpMesh->mNumVertices, elementCount);
					   
			std::vector<aiTextureType> types = {
				aiTextureType_NONE,
				aiTextureType_DIFFUSE,
				aiTextureType_SPECULAR,
				aiTextureType_AMBIENT,
				aiTextureType_EMISSIVE,
				aiTextureType_HEIGHT,
				aiTextureType_NORMALS,
				aiTextureType_SHININESS,
				aiTextureType_OPACITY,
				aiTextureType_DISPLACEMENT,
				aiTextureType_LIGHTMAP,
				aiTextureType_REFLECTION,
				aiTextureType_BASE_COLOR,
				aiTextureType_NORMAL_CAMERA,
				aiTextureType_EMISSION_COLOR,
				aiTextureType_METALNESS,
				aiTextureType_DIFFUSE_ROUGHNESS,
				aiTextureType_AMBIENT_OCCLUSION,
				aiTextureType_UNKNOWN
			};


			std::shared_ptr<Shader> TPShader;
			TPShader.reset(Shader::create("./assets/shaders/texturedPhong.glsl"));
			mesh.material.reset(new Material(TPShader));
			mesh.material->setTint(glm::vec4(1.0));
			aiMaterial* material = scene->mMaterials[assimpMesh->mMaterialIndex];

			for (auto type : types)
			{
				for (uint32_t i = 0; i < material->GetTextureCount(type); i++)
				{
					aiString str;
					material->GetTexture(type, i, &str);
					if (aiTextureType_DIFFUSE)
					{
						std::string fn(str.C_Str());
						auto extnLoc = fn.find(".DDS");
						if (extnLoc != std::string::npos) { fn.replace(extnLoc, extnLoc + 4, ".bmp"); }
						Logger::info("Texture type:{0} filepath:{1}", type,fn);
						std::shared_ptr<Textures> texture;
						texture.reset(Textures::create((s_workingDirectory + fn).c_str()));
						if(texture->getChannels() < 5)mesh.material->setMainTexture(texture);
					}			

				}
			}

			aiString stringValue;
			int intValue;
			float floatValue;
			aiColor3D colorValue;
			if (AI_SUCCESS == material->Get(AI_MATKEY_NAME, stringValue)) Logger::info("Material name: {0}", stringValue.C_Str());

			if (AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, intValue))
			{
				if (intValue == aiShadingMode_Flat) Logger::info("Material shading model: Flat shading");
				if (intValue == aiShadingMode_Gouraud) Logger::info("Material shading model: Gouraud");
				if (intValue == aiShadingMode_Phong) Logger::info("Material shading model: Phong");
				if (intValue == aiShadingMode_Blinn) Logger::info("Material shading model: Blinn");
				if (intValue == aiShadingMode_Toon) Logger::info("Material shading model: Toon");
				if (intValue == aiShadingMode_OrenNayar) Logger::info("Material shading model: Oren Nayar");
				if (intValue == aiShadingMode_Minnaert) Logger::info("Material shading model: Minnaert");
				if (intValue == aiShadingMode_CookTorrance) Logger::info("Material shading model: Cook Torrance");
				if (intValue == aiShadingMode_Fresnel) Logger::info("Material shading model: Fresnel");
				if (intValue == aiShadingMode_NoShading) Logger::info("Material shading model: No shading");
			}

			if (AI_SUCCESS == material->Get(AI_MATKEY_ENABLE_WIREFRAME, intValue))
			{
				if (intValue == 0) Logger::info("Material wireframe: false");
				else if (intValue == 1) Logger::info("Material wireframe: true");
				else Logger::info("Material wireframe: unknown");
			}


			if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, floatValue)) Logger::info("Material shininess: {0}", floatValue);
			if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS_STRENGTH, floatValue)) Logger::info("Material shininess strength: {0}", floatValue);
			if (AI_SUCCESS == material->Get(AI_MATKEY_REFLECTIVITY, floatValue)) Logger::info("Material reflectivity: {0}", floatValue);
			if (AI_SUCCESS == material->Get(AI_MATKEY_REFRACTI, floatValue)) Logger::info("Material refraction index: {0}", floatValue);
			if (AI_SUCCESS == material->Get(AI_MATKEY_TRANSPARENCYFACTOR, floatValue)) Logger::info("Material transprancy factor: {0}", floatValue);
			if (AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, floatValue)) Logger::info("Material opacity: {0}", floatValue);

			if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, colorValue)) Logger::info("Material ambient colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);

			if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, colorValue)) Logger::info("Material diffuse colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
			if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, colorValue)) Logger::info("Material specular colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
			if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_EMISSIVE, colorValue)) Logger::info("Material emissive colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
			if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_REFLECTIVE, colorValue)) Logger::info("Material reflective colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
			if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_TRANSPARENT, colorValue)) Logger::info("Material tranparent colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);

		}

		static void ASSIMPProcessNode(aiNode *node, const aiScene *scene, Engine::Mesh& mesh, glm::mat4& parentTransform)
		{
			std::string parentName = "Null";
			if (node->mParent != nullptr) parentName = node->mParent->mName.C_Str();
			if (node->mNumMeshes > 0) Logger::info("MESHED NODE: {0} PARENT: {1}", node->mName.C_Str(), parentName);
			if (node->mNumMeshes == 0) Logger::info("UNMESHED NODE: {0} PARENT: {1}", node->mName.C_Str(), parentName);

			aiMatrix4x4 *transform = &node->mTransformation;
			glm::mat4 localTransform(
				transform->a1, transform->a2, transform->a3, transform->a4,
				transform->b1, transform->b2, transform->b3, transform->b4,
				transform->c1, transform->c2, transform->c3, transform->c4,
				transform->d1, transform->d2, transform->d3, transform->d4);

			glm::mat4 globalTransform = parentTransform * localTransform;

			// process all the node's meshes
			for (uint32_t i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *assimpMesh = scene->mMeshes[node->mMeshes[i]];
				ASSIMPProcessMesh(assimpMesh, scene, mesh, globalTransform);
			}

			//  Process child nodes
			for (uint32_t i = 0; i < node->mNumChildren; i++)
			{
				ASSIMPProcessNode(node->mChildren[i], scene, mesh, globalTransform);
			}
		}
		static void ASSIMPLoad(const std::string& filepath, Mesh& mesh)
		{
			auto lastSlashLoc = filepath.find_last_of("\\/");
			if (lastSlashLoc != std::string::npos) { s_workingDirectory = filepath.substr(0, lastSlashLoc + 1); } // found slash
				

			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(filepath, aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_GenSmoothNormals);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				Logger::error("Cannot load: {0}, ASSIMP Error {1}", filepath, importer.GetErrorString());
				return;
			}
			ASSIMPProcessNode(scene->mRootNode, scene, mesh, glm::mat4(1.0f));

			Logger::info("ANIMATIONS");

			for (int i = 0; i < scene->mNumAnimations; i++)
			{
				aiAnimation* anim = scene->mAnimations[i];

				Logger::info("TicksPerSecond: {0} Duration: {1}", anim->mTicksPerSecond, anim->mDuration);

				for (int j = 0; j < anim->mNumChannels; j++)
				{
					aiNodeAnim* nodeAnim = anim->mChannels[j];
					Logger::info("Bone: {0}", nodeAnim->mNodeName.C_Str());

					Logger::info("Position keyframes:");
					for (int k = 0; k < nodeAnim->mNumPositionKeys; k++)
					{
						aiVectorKey key = nodeAnim->mPositionKeys[k];
						Logger::info("Time: {0} Position: {1}, {2}, {3}", key.mTime, key.mValue.x, key.mValue.y, key.mValue.z);
					}

					Logger::info("Rotation keyframes:");
					for (int k = 0; k < nodeAnim->mNumRotationKeys; k++)
					{
						aiQuatKey key = nodeAnim->mRotationKeys[k];
						Logger::info("Time: {0} Rotation (Quat): {1}, {2}, {3}, {4}", key.mTime, key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z);
					}

					Logger::info("Scaling keyframes:");
					for (int k = 0; k < nodeAnim->mNumScalingKeys; k++)
					{
						aiVectorKey key = nodeAnim->mScalingKeys[k];
						Logger::info("Time: {0} Scaling: {1}, {2}, {3}", key.mTime, key.mValue.x, key.mValue.y, key.mValue.z);
					}

					// Could do the same for mesh and morph mesh animations
				}

			}


		}
	}
}