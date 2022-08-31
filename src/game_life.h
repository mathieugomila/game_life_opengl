#ifndef GAME_LIFE_H
#define GAME_LIFE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void game_of_life_init(int w, int h);
unsigned int generate_texture();
void update_game_of_life();
void modifiate_texture(unsigned int texture);
#endif