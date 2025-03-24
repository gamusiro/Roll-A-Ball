#ifndef ROLL_A_BALL_INCLUDE_UTILS_H_
#define ROLL_A_BALL_INCLUDE_UTILS_H_
#include "Config.h"
#include "Logger.h"

// defines
#define LOG_INFO_GLM_VEC3(str, vec) printf("%s:\t x: %6f y: %6f z: %6f\n", str, vec.x, vec.y, vec.z)
#define LOG_INFO_GLM_VEC4(str, vec) printf("%s:\t x: %6f y: %6f z: %6f w: %6f\n", str, vec.x, vec.y, vec.z, vec.w)
#define LOG_INFO_GLM_QUAT(str, qut) printf("%s:\t w: %6f x: %6f y: %6f z: %6f\n", str, qut.w, qut.x, qut.y, qut.z)

#define LOG_INFO_GLM_MAT4(str, mat) printf("%s\n", str);\
								    printf("%4f %4f %4f %4f\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);\
								    printf("%4f %4f %4f %4f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);\
								    printf("%4f %4f %4f %4f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);\
								    printf("%4f %4f %4f %4f\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);\

#define LOG_INFO_TRANSFORM(str, transform)	printf("%s\n", str);\
                                            LOG_INFO_GLM_VEC3("Position", transform.GetPosition());\
                                            LOG_INFO_GLM_QUAT("Rotation", transform.GetRotationQuat());\
                                            LOG_INFO_GLM_VEC3("Scale", transform.GetScale());\
                                            LOG_INFO_GLM_VEC3("Dir F", transform.GetForward());\
                                            LOG_INFO_GLM_VEC3("Dir R", transform.GetRight());\
                                            LOG_INFO_GLM_VEC3("Dir U", transform.GetUp());\
                                            LOG_INFO_GLM_MAT4("Local", transform.GetLocalMatrix());\
                                            LOG_INFO_GLM_MAT4("World", transform.GetWorldMatrix());\

#define VEC3_GLM_2_BT(vec) btVector3(vec.x, vec.y, vec.z)
#define VEC4_GLM_2_BT(vec) btVector4(vec.x, vec.y, vec.z, vec.w)
#define QUAT_GLM_2_BT(quat) btQuaternion(quat.w, quat.x, quat.y, quat.z)
#define VEC3_BT_2_GLM(vec) glm::vec3(vec.x(), vec.y(), vec.z())
#define VEC4_BT_2_GLM(vec) glm::vec4(vec.x(), vec.y(), vec.z(), vec.w())
#define QUAT_BT_2_GLM(quat) glm::quat(quat.w(), quat.x(), quat.y(), quat.z())


#endif //!ROLL_A_BALL_INCLUDE_UTILS_H_