#include <nfd.h>
#include <string>
namespace xhfr {

class FileDialog {
 public:
  static std::string getOpenFileName(std::string filter = "*");
  static std::string getSaveFileName(std::string filter = "*",
                                     std::string defaultName = "save");
};

}  // namespace xhfr
