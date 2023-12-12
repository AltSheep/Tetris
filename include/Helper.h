#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

class Helper
{
    public:

        inline static vec3 WORLD_UP_VECTOR = vec3(0.0f, 1.0f, 0.0f);

        static void printMatrix(const glm::mat4& matrix) 
        {
            for (int i = 0; i < 4; ++i) 
            {
                for (int j = 0; j < 4; ++j) 
                {
                    printf("[%.2f]", matrix[i][j]);
                }
                std::cout << std::endl;
            }
        }

        static void printVector(vec3 vec3) 
        {
            printf("<%.2f, %.2f, %.2f>\n", vec3[0], vec3[1], vec3[2]);
        }

        static void printVector(vec4 vec4) 
        {
            printf("<%.2f, %.2f, %.2f, %.2f>\n", vec4[0], vec4[1], vec4[2], vec4[2]);
        }
};


