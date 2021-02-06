#include "ogls/mesh.hpp"

namespace ogls {

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<unsigned int>& indices, const Material& material)
    : vertices{vertices}, indices{indices}, material{material} {
  // setup VBO, EBO, VAO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), GL_STATIC_DRAW);

  // EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               indices.data(), GL_STATIC_DRAW);

  // position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(0));
  // normal
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, normal)));

  // texcoords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, texcoords)));

  glBindVertexArray(0);
}

void Mesh::destroy() {
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  vertices.clear();
  indices.clear();
}

void Mesh::draw(const Shader& shader,
                const std::vector<Texture>& textures) const {
  // set texture uniform
  if (material.diffuseMap) {
    shader.setUniformTexture("diffuseMap",
                             textures[material.diffuseMap.value()].id, 0);
  }
  if (material.specularMap) {
    shader.setUniformTexture("specularMap",
                             textures[material.specularMap.value()].id, 1);
  }

  // set material
  if (material.diffuseMap) {
    shader.setUniform("kd", glm::vec3(0));
  } else {
    shader.setUniform("kd", material.kd);
  }
  if (material.specularMap) {
    shader.setUniform("ks", glm::vec3(0));
  } else {
    shader.setUniform("ks", material.ks);
  }
  shader.setUniform("ka", material.ka);
  shader.setUniform("shininess", material.shininess);

  // draw mesh
  glBindVertexArray(VAO);
  shader.activate();
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  shader.deactivate();
  glBindVertexArray(0);

  // reset texture uniform
  shader.setUniformTexture("diffuseMap", 0, 0);
  shader.setUniformTexture("specularMap", 0, 0);
}

}  // namespace ogls