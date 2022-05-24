#ifndef XHFR_CLIPBOARD_HPP
#define XHFR_CLIPBOARD_HPP

#include "Image.hpp"

namespace xhfr {

namespace Clipboard {

    bool isImage();
    xhfr::Image getImage();
    std::vector<unsigned char> getImageData();

}

} // namespace xhfr

#endif // XHFR_CLIPBOARD_HPP
