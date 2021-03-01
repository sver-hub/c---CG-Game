#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};



class Image {
    public:
    explicit Image(const std::string &a_path);
    explicit Image(int a_width, int a_height, int a_channels);
    Image() {};
  

    int save(const std::string &a_path);

    int getWidth()    const { return width; }
    int getHeight()   const { return height; }
    int getChannels() const { return channels; }
    size_t getSize()  const { return size; }
    Pixel* getData()        { return  data; }

    Pixel getPixel(int x, int y) { return data[width * y + x];}
    void  putPixel(int x, int y, const Pixel &pix) {data[width* y + x] = pix; }
    void  putTile (int x, int y, Image &tile, int offset_x = 0, int offset_y = 0, int shift_x = 0, int shift_y = 0);
    void  clearTile(int x, int y);
    void  initTile(Image &from, int x, int y);
    void  mirror(Image &from);

    ~Image();

    private:
    int width = -1;
    int height = -1;
    int channels = 3;
    size_t size = 0;
    Pixel *data = nullptr;
    bool self_allocated = false;
};



#endif //MAIN_IMAGE_H
