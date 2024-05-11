//
// Created by micha on 1/26/2024.
//

#ifndef CESIUM_SHADER_H
#define CESIUM_SHADER_H
// clang-format off
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
// clang-format on
class Shader {
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec3(const std::string &name, glm::vec3 value) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif // CESIUM_SHADER_H
