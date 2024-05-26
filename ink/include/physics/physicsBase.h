#ifndef INK_PHYSICSBASE_H
#define INK_PHYSICSBASE_H

#include <glm/glm.hpp>

// Class basically exists to handle the translation of acceleration & velocity
// into changes in position. 
// position = d(velocity) /dt
// velocity = d(acceleration) / dt

// In other words
// velocity = 1/2 acceleration ^ 2
// position = 1/2 velocity ^ 2 = 1/6 acceleration ^ 3

// Every game object has a defined world position. Position is influenced by velocity and 
// acceleration forces. Should be able to set velocity or acceleration in code. 

class PhysicsBody {
private:
    glm::vec3 _acceleration;
    glm::vec3 _velocity;

    glm::vec3 _position; // reference to world position of the object

public:
    void velocity(glm::vec3);
    glm::vec3 velocity();

    void acceleration(glm::vec3);
    glm::vec3 acceleration();


    // Get and set world position of game object
    void getPosition();     // returns void since it's going to update member position
    void setPosition();     // type void because it will eventually be passed ref to the actual object position


};

#endif // INK_PHYSICSBASE_H