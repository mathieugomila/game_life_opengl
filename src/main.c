#include "main.h"

const int W_WIDTH = 1600, W_HEIGHT = 800;
const int GRID_SIZE_WIDTH = 128, GRID_SIZE_HEIGHT = 64;
GLFWwindow *window;
int keep_running = 1;
GLuint vao;
GLuint basic_shader;
unsigned int texture;
long long current_time, previous_time;
long long time_between_update = 60;

int main()
{
    if (init())
    {
        printf("Aborting from main function\n");
        return -1;
    }

    while (keep_running)
    {
        update();
    }

    terminate();

    return 0;
}

int init()
{
    // Initialisating glfw and settings up some parameters
    if (!glfwInit())
    {
        printf("Can't initialize glfw\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Because we are using opengl 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating the window and checking if the windows has been correctly created
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "JEU DE LA VIE", NULL, NULL);

    if (window == NULL)
    {
        printf("Can't create glfw window\n");
        glfwTerminate();
        return -1; // There has been an error
    }

    // Specify which window to use and setting viewport
    glfwMakeContextCurrent(window);
    glViewport(0, 0, W_WIDTH, W_HEIGHT);

    // Setting up glew (opengl)
    if (glewInit() != GLEW_OK)
    {
        printf("Can't initialize glew\n");
        return -1;
    }
    // Setup ended correctly

    // Load contents
    basic_shader = createShader("basic");
    if (basic_shader == 0)
    {
        return -1;
    }

    vao = create_screen_image();

    game_of_life_init(GRID_SIZE_WIDTH, GRID_SIZE_HEIGHT);
    texture = generate_texture();

    struct timeval te;
    gettimeofday(&te, NULL);
    previous_time = te.tv_sec * 1000LL + te.tv_usec / 1000;

    return 0;
}
void update()
{
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
    {
        keep_running = 0;
        return;
    }

    // Update everything :
    struct timeval te;
    gettimeofday(&te, NULL);
    current_time = te.tv_sec * 1000LL + te.tv_usec / 1000;

    if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS)
    {
        if (current_time - previous_time > time_between_update)
        {
            previous_time = current_time;
            update_game_of_life();
            modifiate_texture(texture);
        }
    }

    // Draw everything :
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glBindTexture(GL_TEXTURE_2D, texture);

    glFrontFace(GL_CW);

    glClearColor(0.5, 0.5, 0.5, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(basic_shader);
    GLint size_of_grid_location = glGetUniformLocation(basic_shader, "size_of_grid");
    glUniform2f(size_of_grid_location, (float)GRID_SIZE_WIDTH, (float)GRID_SIZE_HEIGHT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window);
}
void terminate()
{
    glfwTerminate();
    printf("End of terminate function\n");
}