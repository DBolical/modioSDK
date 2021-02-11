#include "c++/methods/callbacks/ExternalAuthenticationInstanceCallbacks.h"
#include "c++/schemas/Response.h"
#include "c++/schemas/Terms.h"

namespace modio
{
std::map<u32, GenericCall *> galaxy_auth_calls;
std::map<u32, GenericCall *> oculus_auth_calls;
std::map<u32, GenericCall *> steam_auth_calls;
std::map<u32, GenericCall *> steam_auth_encoded_calls;
std::map<u32, GenericCall *> link_external_account_calls;
std::map<u32, GetTermsCall *> get_terms_calls;

void onGalaxyAuth(void *object, ModioResponse modio_response)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;

  response.initialize(modio_response);

  galaxy_auth_calls[call_id]->callback(response);

  delete galaxy_auth_calls[call_id];
  galaxy_auth_calls.erase(call_id);
}

void onOculusAuth(void *object, ModioResponse modio_response)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;

  response.initialize(modio_response);

  oculus_auth_calls[call_id]->callback(response);

  delete oculus_auth_calls[call_id];
  oculus_auth_calls.erase(call_id);
}

void onSteamAuth(void *object, ModioResponse modio_response)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;

  response.initialize(modio_response);

  steam_auth_calls[call_id]->callback(response);

  delete steam_auth_calls[call_id];
  steam_auth_calls.erase(call_id);
}

void onSteamAuthEncoded(void *object, ModioResponse modio_response)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;

  response.initialize(modio_response);

  steam_auth_encoded_calls[call_id]->callback(response);

  delete steam_auth_encoded_calls[call_id];
  steam_auth_encoded_calls.erase(call_id);
}

void onLinkExternalAccount(void *object, ModioResponse modio_response)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;

  response.initialize(modio_response);

  link_external_account_calls[call_id]->callback(response);

  delete link_external_account_calls[call_id];
  link_external_account_calls.erase(call_id);
}

void onGetTerms(void* object, ModioResponse modio_response, ModioTerms* modio_terms)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  modio::Terms terms;

  response.initialize(modio_response);
  terms.initialize(*modio_terms);

  get_terms_calls[call_id]->callback(response, terms);

  delete get_terms_calls[call_id];
  get_terms_calls.erase(call_id);
}

void clearExternalAuthenticationRequestCalls()
{
  for (auto galaxy_auth_call : galaxy_auth_calls)
    delete galaxy_auth_call.second;
  galaxy_auth_calls.clear();

  for (auto oculus_auth_call : oculus_auth_calls)
    delete oculus_auth_call.second;
  oculus_auth_calls.clear();

  for (auto steam_auth_call : steam_auth_calls)
    delete steam_auth_call.second;
  steam_auth_calls.clear();

  for (auto steam_auth_encoded_call : steam_auth_encoded_calls)
    delete steam_auth_encoded_call.second;
  steam_auth_encoded_calls.clear();

  for (auto link_external_account_call : link_external_account_calls)
    delete link_external_account_call.second;
  link_external_account_calls.clear();

  for (auto get_terms_call : get_terms_calls)
    delete get_terms_call.second;
  get_terms_calls.clear();
}
} // namespace modio
