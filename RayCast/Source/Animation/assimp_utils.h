#ifndef ASSIMP_UTILS_H
#define ASSIMP_UTILS_H

#include <assimp/matrix4x4.h>
#include <glm.hpp>
#include <assimp/vector3.h>
#include <assimp/quaternion.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

class AssimpUtils {
public:
	static inline glm::mat4 AiMatrixToGLM(const aiMatrix4x4& matrix) {
		glm::mat4 result;
		result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
		result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
		result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
		result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;

		return result;
	}

	static inline glm::vec3 AiVectorToGLM(const aiVector3D& vector) {
		return glm::vec3(vector.x, vector.y, vector.z);
	}

	static inline glm::quat AiQuatToGLM(const aiQuaternion& quat) {
		return glm::quat(quat.w, quat.x, quat.y, quat.z);
	}

};


#endif