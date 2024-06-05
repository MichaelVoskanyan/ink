//
// Created by micha on 1/26/2024.
//

#ifndef CESIUM_SHADER_H
#define CESIUM_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Shader {
public:
  // ID or shader handle
  unsigned int ID;

  // Constructor, must have path to vertex and fragment shaders.
  // Local path is accepted, must be prepended with '/'
  Shader(const char* vertexPath, const char* fragmentPath);

  // Binds shader for use
  void use();

  // Setting shader uniforms
  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetVec3(const std::string& name, glm::vec3 value) const;
  void SetVec3(const std::string& name, float x, float y, float z) const;
  void SetMat4(const std::string& name, glm::mat4 value) const;
};

#endif // CESIUM_SHADER_H
