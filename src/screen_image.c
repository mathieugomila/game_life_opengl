#include "screen_image.h"

GLuint create_screen_image()
{
    GLuint vaoID;
    GLuint vboID;
    float vertices[] = {
        // first triangle
        1.0f, 1.0f, 0.0f,   // top right
        1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, 1.0f, 0.0f,  // top left
                            // second triangle
        1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f   // top left
    };

    // Create vao object and storing its id in vaoID[1]
    glGenVertexArrays(1, &vaoID);

    // Binding vao so that we can use it
    glBindVertexArray(vaoID);

    // same for vbo
    glGenBuffers(1, &vboID);

    // VBO 1
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    // Give information about the attrib 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vaoID;
}
