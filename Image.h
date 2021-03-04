#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>
struct CameraController;

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    bool isEmpty() {
        return r == 0 && g == 0 && b == 0 && a == 0;
    }
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
    void  putPixel(int x, int y, const Pixel &pix) { data[width* y + x] = pix; }
    void  multPixel(int x, int y, float scale);
    void  addPixel(int x, int y, const Pixel &pix, float scale);
    void  putTile (int x, int y, Image &tile, int offset_x = 0, int offset_y = 0);
    void  putSprite(int x, int y, Image &sprite, CameraController camera);
    void  clearTile(int x, int y);
    void  initTile(Image &from, int x, int y);
    void  mirror(Image &from);
    void  initWord(Image &from, int x, int y, int len_x, int len_y);
    void putScreen(Image& screen);

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
