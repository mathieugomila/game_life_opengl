#ifndef MAIN_H
#define MAIN_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <sys/time.h>

#include "shader.h"
#include "screen_image.h"
#include "game_life.h"

int init();
void update();
void terminate();

#endif