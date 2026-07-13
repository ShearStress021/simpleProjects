#pragma once
#include <string>
#include <stdint.h>

using texture = int;
using mesh = int;
//using myColor = struct()


bool init_window(int width, int height, const std::string_view title);

void window_shutdown(void);
void window_reset(void);
bool windowShouldClose(void);



texture loadTextureRGBA(const uint8_t *rgba, int w, int h);
texture loadTextureFile(const std::string_view path);
