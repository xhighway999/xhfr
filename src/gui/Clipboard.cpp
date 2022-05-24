#include "Clipboard.hpp"

#include "clip/clip.h"
#include "stb_image_write.h"
namespace xhfr {



bool Clipboard::isImage()
{
    return clip::has(clip::image_format());
}

Image Clipboard::getImage()
{

    clip::image img;
    clip::get_image(img);

    auto ximg = xhfr::Image();


    auto format = GL_RGB;
    if(img.spec().bits_per_pixel == 24) {

    }
    else if(img.spec().bits_per_pixel == 32) {
        format = GL_RGBA;
    }

    ximg.loadImageFromRaw(img.spec().width,img.spec().height,(const unsigned char*)img.data(),format);

    return ximg;


}

std::vector<unsigned char> Clipboard::getImageData()
{
    clip::image img;
    clip::get_image(img);
    std::vector<unsigned char> dataVect;

    auto func = [](void *context, void *data, int size) {
        std::vector<unsigned char>* dataVect = (std::vector<unsigned char>*)context;
        dataVect->resize(size);
        std::memcpy(&(*dataVect)[0],data,size);
        return;
    };
    stbi_write_png_to_func(func,&dataVect,img.spec().width,img.spec().height,img.spec().bits_per_pixel/8,img.data(),img.spec().bytes_per_row);
    return dataVect;

}

} // namespace xhfr
