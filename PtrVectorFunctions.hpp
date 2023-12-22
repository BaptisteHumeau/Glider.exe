#include <vector>
#include <SFML\Graphics.hpp>

// Helper functions to assist with management of vectors that contain pointers to objects

/**
 * @brief Clears vector of pointer
 *
 * @tparam T datatype within vector
 * @param vect reference to vector
 */
template <typename T>
void clear_ptr_vector(std::vector<T *> &vect)
{
    for (T *object : vect) // empty obstacle vector
    {
        delete object;
        object = nullptr;
    }
    vect.clear();
}

/**
 * @brief draws objects within pointer vector - assumes object have a public .draw() function
 *
 * @tparam T datatype within vector
 * @param vect reference to vector
 * @param window reference to sfml window in which to draw objects
 */
template <typename T>
void draw_ptr_vector(std::vector<T *> &vect, sf::RenderWindow &window)
{
    if (vect.size() > 0)
    {
        for (T *object : vect)
        {
            object->draw(window);
        }
    }
}

/**
 * @brief delete first object in a vector of pointers
 *
 * @tparam T datatpye within vector
 * @param vect reference to vector
 */
template <typename T>
void pop_front_ptr_vector(std::vector<T *> &vect)
{
    delete vect.front();
    vect.front() = nullptr;
    vect.erase(vect.begin());
}

/**
 * @brief pushes a pointer to a new instance of an object to the back of a vector of pointers
 *
 * @tparam T datatype within vector
 * @ObjectCreationFunction function to be used for object creation (ie: createRandomObstacle) - should return an object
 * @tparam Args arguments to be used for object creation
 */
template <typename T, typename... Args>
using ObjectCreationFunction = T (*)(Args...);

template <typename T, typename... Args>
void push_back_ptr_vector(std::vector<T *> &vect, ObjectCreationFunction<T, Args...> createFunction, Args... args)
{
    T *newObject = new T(createFunction(args...));
    vect.push_back(newObject);
}
