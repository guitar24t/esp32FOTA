/*
   esp32 firmware OTA
   Date: December 2018
   Author: Chris Joyce <https://github.com/chrisjoyce911/esp32FOTA/esp32FOTA>
   Purpose: Perform an OTA update from a bin located on a webserver (HTTP Only)
*/

#ifndef esp32fota_h
#define esp32fota_h

#include "Arduino.h"
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <functional>

class esp32FOTA
{
public:
  esp32FOTA(String firwmareType, int firwmareVersion);
  void forceUpdate(String firwmareHost, int firwmarePort, String firwmarePath);
  void execOTA();
  bool execHTTPcheck();
  int getPayloadVersion();
  void setValidationCallback(const std::function<bool(WiFiClient&)> &func);
  bool useDeviceID;
  String checkURL;

private:
  String getDeviceID();
  String _firwmareType;
  int _firwmareVersion;
  int _payloadVersion;
  String _host;
  String _bin;
  int _port;
  std::function<bool(WiFiClient&)> _validationCallback;
};

class secureEsp32FOTA
{
public:
  secureEsp32FOTA(String firwmareType, int firwmareVersion);
  bool execHTTPSCheck();
  void executeOTA();
  int getPayloadVersion();
  String _descriptionOfFirmwareURL;
  char *_certificate;
  unsigned int _securePort = 443;
  WiFiClientSecure clientForOta;
  void setValidationCallback(const std::function<bool(WiFiClientSecure&)> &func);
  String _host;

private:
  bool prepareConnection(String locationOfServer);
  String secureGetContent();
  bool isValidContentType(String line);
  String _firwmareType;
  int _firwmareVersion;
  int _payloadVersion;
  String locationOfFirmware;
  String _bin;
  int _port;
  std::function<bool(WiFiClientSecure&)> _validationCallback;
};

#endif
