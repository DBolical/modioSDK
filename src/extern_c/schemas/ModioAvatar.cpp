#include "extern_c/schemas/ModioAvatar.h"

extern "C"
{
  void modioInitAvatar(ModioAvatar* avatar, json avatar_json)
  {
    avatar->filename = NULL;
    if(modio::hasKey(avatar_json, "filename"))
    {
      std::string filename_str = avatar_json["filename"];
      avatar->filename = new char[filename_str.size() + 1];
      strcpy_s(avatar->filename, filename_str.size() + 1, filename_str.c_str());
    }

    avatar->original = NULL;
    if(modio::hasKey(avatar_json, "original"))
    {
      std::string original_str = avatar_json["original"];
      avatar->original = new char[original_str.size() + 1];
      strcpy_s(avatar->original, original_str.size() + 1, original_str.c_str());
    }

    avatar->thumb_50x50 = NULL;
    if(modio::hasKey(avatar_json, "thumb_50x50"))
    {
      std::string thumb_50x50_str = avatar_json["thumb_50x50"];
      avatar->thumb_50x50 = new char[thumb_50x50_str.size() + 1];
      strcpy_s(avatar->thumb_50x50, thumb_50x50_str.size() + 1, thumb_50x50_str.c_str());
    }

    avatar->thumb_100x100 = NULL;
    if(modio::hasKey(avatar_json, "thumb_100x100"))
    {
      std::string thumb_100x100_str = avatar_json["thumb_100x100"];
      avatar->thumb_100x100 = new char[thumb_100x100_str.size() + 1];
      strcpy_s(avatar->thumb_100x100, thumb_100x100_str.size() + 1, thumb_100x100_str.c_str());
    }
  }

  void modioFreeAvatar(ModioAvatar* avatar)
  {
    delete[] avatar->filename;
    delete[] avatar->original;
    delete[] avatar->thumb_50x50;
    delete[] avatar->thumb_100x100;

    delete avatar;
  }
}
