#include "c/methods/MetadataKVPMethods.h"

extern "C"
{
  void modioGetMetadataKVP(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMetadataKVP* metadata_kvp_array, u32 metadata_kvp_array_size))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/metadatakvp/";

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_metadata_kvp_callbacks[call_number] = new GetMetadataKVPParams;
    get_metadata_kvp_callbacks[call_number]->callback = callback;
    get_metadata_kvp_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetMetadataKVP);
  }

  void modioAddMetadataKVP(void* object, u32 mod_id, char** metadata_kvp_array, u32 metadata_kvp_array_size, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_metadata_kvp_callbacks[call_number] = new AddMetadataKVPParams;
    add_metadata_kvp_callbacks[call_number]->callback = callback;
    add_metadata_kvp_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/metadatakvp";

    for(u32 i=0; i<metadata_kvp_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += std::string("metadata[]=") + metadata_kvp_array[i];
    }

    modio::curlwrapper::post(call_number, url, headers, data, &modioOnAddMetadataKVP);
  }

  void modioDeleteMetadataKVP(void* object, u32 mod_id, char** metadata_kvp_array, u32 metadata_kvp_array_size, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_metadata_kvp_callbacks[call_number] = new DeleteMetadataKVPParams;
    delete_metadata_kvp_callbacks[call_number]->callback = callback;
    delete_metadata_kvp_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/metadatakvp";

    for(u32 i=0; i<metadata_kvp_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += std::string("metadata[]=") + metadata_kvp_array[i];
    }

    modio::curlwrapper::deleteCall(call_number, url, headers, &modioOnDeleteMetadataKVP);
  }
}