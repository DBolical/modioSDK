#include "c/methods/callbacks/AuthenticationCallbacks.h"
#include "Utility.h" // for hasKey

std::map<u32, GenericRequestParams *> email_request_params;
std::map<u32, GenericRequestParams *> email_exchange_params;

void modioOnEmailRequested(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  email_request_params[call_number]->callback(email_request_params[call_number]->object, response);
  delete email_request_params[call_number];
  email_request_params.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnEmailExchanged(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if (response.code == 200)
  {
    std::string access_token = "";
    if (modio::hasKey(response_json, "access_token"))
    {
      modio::updateAuthenticatedUser(response_json["access_token"]);
    }
    else
    {
      modio::writeLogLine("Could not retreive access token from server.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  email_exchange_params[call_number]->callback(email_exchange_params[call_number]->object, response);

  delete email_exchange_params[call_number];
  email_exchange_params.erase(call_number);

  modioFreeResponse(&response);
}

void clearAuthenticationCallbackParams()
{
  for (auto email_request_param : email_request_params)
    delete email_request_param.second;
  email_request_params.clear();

  for (auto email_exchange_param : email_exchange_params)
    delete email_exchange_param.second;
  email_exchange_params.clear();
}
