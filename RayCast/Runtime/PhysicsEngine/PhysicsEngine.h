#pragma once

#include <gtx/quaternion.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace PhysicUtils {
	static glm::vec3 BtVec3ToGLM(btVector3 vector) {
	
		return glm::vec3(vector.x(), vector.y(), vector.z());
	}

	static btVector3 GLMToBtVec3(glm::vec3 vector) {
		return btVector3(vector.x, vector.y, vector.z);
	}

	static glm::quat BtQuatToGLM(btQuaternion quat) {
		return glm::quat(quat.w(), quat.x(), quat.y(), quat.z());
	}

	static btQuaternion GLMQuatToBt(glm::quat quat) {
		return btQuaternion(quat.x, quat.y, quat.z, quat.w);
	}
}