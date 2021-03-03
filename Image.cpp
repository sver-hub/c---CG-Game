#include "Image.h"
#include "config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

void Image::initTile(Image &from, int x, int y) {
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {      
            putPixel(i, j, from.getPixel(x + i, y + j));
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

void Image::putTile (int x, int y, Image &tile, int offset_x, int offset_y, int shift_x, int shift_y) {
    if (offset_y > 0)
        offset_y = (GRID_SIZE - offset_y - 1);
    for (int j = 0; j < TILE_SIZE; j++) {
        for (int i = 0; i < TILE_SIZE; i++) {
            if (i + shift_x < 0 || i + shift_x > TILE_SIZE - 1 
            || j + shift_y < 0 || j + shift_y > TILE_SIZE - 1) continue;

            Pixel pix = tile.getPixel(offset_x * TILE_SIZE + i + shift_x, offset_y * TILE_SIZE + j + shift_y);
            if (pix.r == 0 && pix.g == 0 && pix.b == 0 && pix.a == 0) continue;
            
            putPixel(x * TILE_SIZE + i, (GRID_SIZE - y - 1) * TILE_SIZE + j,
            tile.getPixel(offset_x * TILE_SIZE + i + shift_x, offset_y * TILE_SIZE + j + shift_y));
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