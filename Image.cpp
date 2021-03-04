#include "Image.h"
#include "config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "CameraController.h"
#include <iostream>


Image::Image(const std::string &a_path) {
    if((data = (Pixel*)stbi_load(a_path.c_str(), &width, &height, &channels, 0)) != nullptr) {
        size = width * height * channels;
        Pixel *fliped = new Pixel[width*height];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                fliped[j * width + i] = data[(height - j - 1)* width + i];
            }
        }
        data = fliped;
    }
}

Image::Image(int a_width, int a_height, int a_channels) {
    data = new Pixel[a_width * a_height ]{};

    if (data != nullptr) {
        width = a_width;
        height = a_height;
        size = a_width * a_height * a_channels;
        channels = a_channels;
        self_allocated = true;
    }
}

void  Image::multPixel(int x, int y, float scale) {
    data[width* y + x].r *= scale;
    data[width* y + x].g *= scale;
    data[width* y + x].b *= scale;
}

void Image::addPixel(int x, int y, const Pixel &pix, float scale) {
    data[width* y + x].r = (data[width* y + x].r + (uint8_t)(pix.r * scale)) /2;
    data[width* y + x].g = (data[width* y + x].g + (uint8_t)(pix.g * scale)) /2;
    data[width* y + x].b = (data[width* y + x].b + (uint8_t)(pix.b * scale)) /2;
}

void Image::initTile(Image &from, int x, int y) {
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {      
            putPixel(i, j, from.getPixel(x + i, y + j));
        }
    }
}

void Image::initWord(Image &from, int x, int y, int len_x, int len_y) {
    int x_offset = (SCREEN_WIDTH - len_x)/2;
    int y_offset = (SCREEN_HEIGHT - len_y)/2;
    for (int j = 0; j < len_y; j++) {
        for (int i = 0; i < len_x; i++) {      
            putPixel(x_offset + i, y_offset + j, from.getPixel(x + 4*i, y + 4*j));
        }
    }
}

void Image::putScreen(Image& screen) {
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {      
            putPixel(i, j, screen.getPixel(i, j));
        }
    }
}

void Image::mirror(Image &from) {
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {      
                putPixel(i, j, from.getPixel((TILE_SIZE - i - 1), j));
        }
    }
}

void Image::putSprite(int x, int y, Image &sprite, CameraController camera) {
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {
            if (sprite.getPixel(i,j).isEmpty()) continue;
            int w = x - camera.x0 + i + (SCREEN_WIDTH-2*camera.radius)/2;
            int h = y - camera.y0 + j + (SCREEN_HEIGHT-2*camera.radius)/2 - TILE_SIZE;
            if (w < 0 || w > SCREEN_WIDTH || h < 0 || h > SCREEN_HEIGHT) continue;
            
            putPixel(x - camera.x0 + i + (SCREEN_WIDTH-2*camera.radius)/2 ,
                     y - camera.y0 + j + (SCREEN_HEIGHT-2*camera.radius)/2 - TILE_SIZE, sprite.getPixel(i,j));
        }
    }
}

void Image::putTile (int x, int y, Image &tile, int offset_x, int offset_y) {
    if (offset_y > 0)
        offset_y = (GRID_SIZE - offset_y - 1);
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {
        
            if (tile.getPixel(offset_x * TILE_SIZE + i , offset_y * TILE_SIZE + j).isEmpty()) continue;

            putPixel(x * TILE_SIZE + i, (GRID_SIZE - y - 1) * TILE_SIZE + j,
            tile.getPixel(offset_x * TILE_SIZE + i, offset_y * TILE_SIZE + j));
        }
    }
}

void Image::clearTile(int x, int y) {
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {
            putPixel(x * TILE_SIZE + i, (GRID_SIZE - y - 1) * TILE_SIZE + j, empty);
        }
    }
}

int Image::save(const std::string &a_path) {
    auto extPos = a_path.find_last_of('.');
    if (a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG") {
        stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
    } else if (a_path.substr(extPos, std::string::npos) == ".jpg" || a_path.substr(extPos, std::string::npos) == ".JPG" ||
            a_path.substr(extPos, std::string::npos) == ".jpeg" || a_path.substr(extPos, std::string::npos) == ".JPEG") {
        stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
    } else {
        std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path << "\n";
        return 1;
    }
    return 0;
}

Image::~Image() {
    if(self_allocated)
        delete [] data;
    else {
        stbi_image_free(data);
    }
}