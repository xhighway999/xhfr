#include "FileDialog.hpp"

std::string xhfr::FileDialog::getOpenFileName(std::string filter) {
  NFD_Init();

  nfdchar_t* outPath;
  nfdfilteritem_t filterItem;
  nfdresult_t result;
  if (filter != "") {
    nfdfilteritem_t filterItem[1] = {{filter.c_str(), filter.c_str()}};
    result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);

  } else {
    result = NFD_OpenDialog(&outPath, NULL, 0, NULL);
  }
  if (result == NFD_OKAY) {
    // puts("Success!");
    // puts(outPath);
    return outPath;
    // NFD_FreePath(outPath);
  } else if (result == NFD_CANCEL) {
    // puts("User pressed cancel.");
  } else {
    // printf("Error: %s\n", NFD_GetError());
  }

  NFD_Quit();
  return "";
}

std::string xhfr::FileDialog::getSaveFileName(std::string filter,
                                              std::string defaultName) {
  NFD_Init();

  nfdchar_t* inPath;
  nfdfilteritem_t filterItem;
  nfdresult_t result;
  if (filter != "") {
    nfdfilteritem_t filterItem[1] = {{filter.c_str(), filter.c_str()}};
    result = NFD_SaveDialog(&inPath, filterItem, 1, NULL, defaultName.c_str());

  } else {
    result = NFD_SaveDialog(&inPath, NULL, 0, NULL, defaultName.c_str());
  }
  if (result == NFD_OKAY) {
    // puts("Success!");
    // puts(outPath);
    return inPath;
    // NFD_FreePath(outPath);
  } else if (result == NFD_CANCEL) {
    // puts("User pressed cancel.");
  } else {
    // printf("Error: %s\n", NFD_GetError());
  }

  NFD_Quit();
  return "";
}
