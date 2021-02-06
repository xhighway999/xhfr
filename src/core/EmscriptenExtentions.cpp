#include "EmscriptenExtentions.hpp"

#include "debug.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>

void xhfr::emscripten_download_data(const char* ptr,
                                    size_t l,
                                    const char* downloadFileName,
                                    std::string mimeType) {
  EM_ASM(
      {
        function downloadURI(uri, name) {
          var link = document.createElement("a");
          link.download = name;
          link.href = uri;
          document.body.appendChild(link);
          link.click();
          document.body.removeChild(link);
          delete link;
        };

        // var textFile = null;
        function makeFile(dt, fileName, datatype = 'text/plain') {
          var data = new Blob([dt], {
            type:
              datatype
          });

          // If we are replacing a previously generated file we need to
          // manually revoke the object URL to avoid memory leaks.

          var textFile = window.URL.createObjectURL(data);
          downloadURI(textFile, fileName);
          window.URL.revokeObjectURL(textFile);
        };

        function dataFromCArray(ptr, size) {
          var bytes = new Uint8Array(size);
          for (let i = 0; i < size; i++) {
            bytes[i] = getValue(ptr + i, "i8")
          }
          return bytes;
        };

        var data = dataFromCArray($0, $1);
        var fileName = UTF8ToString($2);
        makeFile(data, fileName);
        console.log(data);
      },
      ptr, l, downloadFileName);
}

void xhfr::emscripten_download_file(std::string path,
                                    std::string displayName,
                                    std::string mimeType) {
  xhfr::File f;
  if (f.open(path, false)) {
    // even valid for binary stuff
    std::string data = f.readAll();
    std::string fileName = xhfr::fs::getFileInfo(path).name;
    emscripten_download_data(&data[0], data.size(), displayName.c_str(),
                             mimeType);
  } else {
    XHFR_ERROR("Could not open file {}", path);
  }
}
#else

void xhfr::emscripten_download_data(const char* ptr,
                                    size_t l,
                                    const char* downloadFileName,
                                    std::string mimeType) {
  abort();
}

void xhfr::emscripten_download_file(std::string path,
                                    std::string displayName,
                                    std::string mimeType) {
  abort();
}
#endif
