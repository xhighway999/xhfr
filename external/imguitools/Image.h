#ifndef IT_IMAGE_H
#define IT_IMAGE_H

namespace it {
    class Image
    {
#ifdef IT_USE_STB
    bool loadFromFile(const char *);
#endif
    };
}

#endif // IT_IMAGE_H
