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
#include <iomanip>
#include <variant>
#include <chrono>

// Phyisics
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

// Mathmatics
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
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

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H

// utf
#include "utf8.h"

// Window Settings
#define DEFAULT_WIDTH  800
#define DEFAULT_HEIGHT 600
#define DEFAULT_CAPTION "Roll-A-Ball"

#define ASSETS_PATH "assets/"
#define SHADERS_PATH ASSETS_PATH "shaders/"
#define MODELS_PATH ASSETS_PATH "models/"
#define FONTS_PATH ASSETS_PATH "fonts/"
#define TEXTURES_PATH ASSETS_PATH "textures/"

// Shaders
#define RENDERER_SHADER_DEFAULT "render_default"
#define RENDERER_SHADER_TEXT "render_text"
#define RENDERER_SHADER_PARTRICLE "render_particle"
#define RENDERER_SHADER_CANVAS "render_canvas"
#define COMPUTE_SHADER_PARTICLE "compute_particle"

// Fonts
#define FONT_NOTOSANS_JP "NotoSansJP-Regular.ttf"

// Textures
#define TEXTURE_WHITE TEXTURES_PATH "white.png"
#define TEXTURE_PARTICLE TEXTURES_PATH "particle.png"

#define TEXTURE_PLAYER_ALBEDO TEXTURES_PATH "player/albedo.jpg"
#define TEXTURE_PLAYER_NORMAL TEXTURES_PATH "player/normal.jpg"
#define TEXTURE_PLAYER_METALNESS TEXTURES_PATH "player/metalness.jpg"
#define TEXTURE_PLAYER_ROUGHNESS TEXTURES_PATH "player/roughness.jpg"
#define TEXTURE_PLAYER_DISPLACEMENT TEXTURES_PATH "player/displacement.jpg"

#define TEXTURE_GROUND_ALBEDO TEXTURES_PATH "ground/albedo.jpg"
#define TEXTURE_GROUND_NORMAL TEXTURES_PATH "ground/normal.jpg"
#define TEXTURE_GROUND_ROUGHNESS TEXTURES_PATH "ground/roughness.jpg"
#define TEXTURE_GROUND_DISPLACEMENT TEXTURES_PATH "ground/displacement.jpg"

#define TEXTURE_WALL_ALBEDO TEXTURES_PATH "wall/albedo.jpg"
#define TEXTURE_WALL_NORMAL TEXTURES_PATH "wall/normal.jpg"
#define TEXTURE_WALL_ROUGHNESS TEXTURES_PATH "wall/roughness.jpg"
#define TEXTURE_WALL_DISPLACEMENT TEXTURES_PATH "wall/displacement.jpg"

#define TEXTURE_COLLECTABLE_ALBEDO TEXTURES_PATH "collectable/albedo.jpg"
#define TEXTURE_COLLECTABLE_NORMAL TEXTURES_PATH "collectable/normal.jpg"
#define TEXTURE_COLLECTABLE_ROUGHNESS TEXTURES_PATH "collectable/roughness.jpg"
#define TEXTURE_COLLECTABLE_DISPLACEMENT TEXTURES_PATH "collectable/displacement.jpg"

#define TEXTURE_BURSTPARTICLE_COLOR_OVER_LIFETIME TEXTURES_PATH "particle/colorOverLifetime_01.png"


class Scene;
class Entity;
class Mesh;
class Font;
class Shader;
class Texture;

using ScenePtr = std::shared_ptr<Scene>;
using MeshPtr = std::shared_ptr<Mesh>;
using FontPtr = std::shared_ptr<Font>;
using ShaderPtr = std::shared_ptr<Shader>;
using TexturePtr = std::shared_ptr<Texture>;

#endif //!ROLL_A_BALL_INCLUDE_CONFIG_H_