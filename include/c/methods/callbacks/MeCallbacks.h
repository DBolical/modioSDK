#ifndef MODIO_MECALLBACKS_H
#define MODIO_MECALLBACKS_H

#include "c/schemas/ModioResponse.h"
#include "c/schemas/ModioUser.h"
#include "c/schemas/ModioMod.h"
#include "Globals.h"
#include "ModUtility.h"

struct GetAuthenticatedUserParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response, ModioUser user);
};

struct GetUserSubscriptionsParams
{
  void* object;
  std::string url;
  bool is_cache;
  void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size);
};

struct GetUserModsParams
{
  void* object;
  std::string url;
  bool is_cache;
  void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size);
};

struct GetUserModfilesParams
{
  void* object;
  std::string url;
  bool is_cache;
  void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size);
};

extern std::map< u32, GetAuthenticatedUserParams* > get_authenticated_user_callbacks;
extern std::map< u32, GetUserSubscriptionsParams* > get_user_subscriptions_callbacks;
extern std::map< u32, GetUserModsParams* > get_user_mods_callbacks;
extern std::map< u32, GetUserModfilesParams* > get_user_modfiles_callbacks;

void modioOnGetAuthenticatedUser(u32 call_number, u32 response_code, json response_json);
void modioOnGetUserSubscriptions(u32 call_number, u32 response_code, json response_json);
void modioOnGetUserMods(u32 call_number, u32 response_code, json response_json);
void modioOnGetUserModfiles(u32 call_number, u32 response_code, json response_json);

#endif