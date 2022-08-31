#include "game_life.h"

unsigned char *data = NULL;
unsigned char *game_life_state = NULL;
int grid_width, grid_height;

void game_of_life_init(int w, int h)
{
    data = (unsigned char *)calloc(w * h * 3, sizeof(unsigned char));
    game_life_state = (unsigned char *)calloc(w * h, sizeof(unsigned char));

    grid_width = w;
    grid_height = h;

    // init grid : just one pixel for now
    struct timeval te;
    gettimeofday(&te, NULL);
    srand(te.tv_sec * 1000 + te.tv_usec);
    for (int x = 0; x < grid_width; x++)
    {
        for (int y = 0; y < grid_height; y++)
        {
            if (rand() < (int)((float)(RAND_MAX) / 2.4f))
            {
                game_life_state[x * grid_height + y] = 1;
            }
        }
    }
}

unsigned int generate_texture()
{
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    modifiate_texture(texture);

    return texture;
}

void update_game_of_life()
{
    unsigned char *new_game_life_state = (unsigned char *)calloc(grid_width * grid_height, sizeof(unsigned char));
    for (int x = 0; x < grid_width; x++)
    {
        for (int y = 0; y < grid_height; y++)
        {
            // Getting data of neighbor
            int number_of_alive_neighbor = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    // if still in bord
                    if (x + i >= 0 && x + i < grid_width && y + j >= 0 && y + j < grid_height)
                    {
                        if (game_life_state[(x + i) * grid_height + y + j] == 1 && (i != 0 || j != 0))
                        {
                            number_of_alive_neighbor++;
                        }
                    }
                }
            }
            // 0, 1, 4, or more neighbors alive ==> dead
            if (number_of_alive_neighbor < 2 || number_of_alive_neighbor > 3)
            {
                new_game_life_state[x * grid_height + y] = 0;
            }
            // 2 neighbor : stay in same state
            else if (number_of_alive_neighbor == 2)
            {
                new_game_life_state[x * grid_height + y] = game_life_state[x * grid_height + y];
            }
            else // 3 neighbors ==> alive
            {
                new_game_life_state[x * grid_height + y] = 1;
            }
        }
    }

    free(game_life_state);
    game_life_state = new_game_life_state;
}

void modifiate_texture(unsigned int texture)
{
    for (int x = 0; x < grid_width; x++)
    {
        for (int y = 0; y < grid_height; y++)
        {
            if (game_life_state[x * grid_height + y] == 0)
            {
                data[3 * (y * grid_width + x)] = 0;
                data[3 * (y * grid_width + x) + 1] = 0;
                data[3 * (y * grid_width + x) + 2] = 0;
            }
            else
            {
                data[3 * (y * grid_width + x)] = 255;
                data[3 * (y * grid_width + x) + 1] = 255;
                data[3 * (y * grid_width + x) + 2] = 255;
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, grid_width, grid_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}