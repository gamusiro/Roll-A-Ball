#ifndef ROLL_A_BALL_INCLUDE_CONFIG_H_
#define ROLL_A_BALL_INCLUDE_CONFIG_H_

// Standard
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <map>
#include <queue>

// Phyisics
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

// Mathmatics
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

// GLFW
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

// GLAD
#include <glad/glad.h>

// spdlog
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// entt
#include <entt/entt.hpp>

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Window Settings
#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480
#define DEFAULT_CAPTION "Roll-A-Ball"

#define ASSETS_PATH "assets/"
#define SHADERS_PATH ASSETS_PATH "shaders/"
#define MODELS_PATH ASSETS_PATH "models/"

// Shaders
#define SHADER_DEFAULT_3D "default3D"


class Scene;
class Entity;
class Mesh;
class Shader;

using ScenePtr = std::shared_ptr<Scene>;
using MeshPtr = std::shared_ptr<Mesh>;
using ShaderPtr = std::shared_ptr<Shader>;


#endif //!ROLL_A_BALL_INCLUDE_CONFIG_H_