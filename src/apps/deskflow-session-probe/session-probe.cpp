/*
 * Deskflow Etumen fork — macOS session/TCC probe.
 * SPDX-License-Identifier: MIT
 */

#include <ApplicationServices/ApplicationServices.h>
#include <SystemConfiguration/SystemConfiguration.h>

#include <unistd.h>

#include <iostream>
#include <string>

namespace {

std::string cfStringToUtf8(CFStringRef value)
{
  if (value == nullptr) {
    return {};
  }

  CFIndex maxSize = CFStringGetMaximumSizeForEncoding(CFStringGetLength(value), kCFStringEncodingUTF8) + 1;
  std::string result(static_cast<size_t>(maxSize), '\0');
  if (!CFStringGetCString(value, result.data(), maxSize, kCFStringEncodingUTF8)) {
    return {};
  }

  result.resize(std::char_traits<char>::length(result.c_str()));
  return result;
}

std::string jsonEscape(const std::string &value)
{
  std::string out;
  out.reserve(value.size());
  for (const char ch : value) {
    switch (ch) {
    case '\\':
      out += "\\\\";
      break;
    case '"':
      out += "\\\"";
      break;
    case '\n':
      out += "\\n";
      break;
    case '\r':
      out += "\\r";
      break;
    case '\t':
      out += "\\t";
      break;
    default:
      out += ch;
      break;
    }
  }
  return out;
}

const char *boolJson(bool value)
{
  return value ? "true" : "false";
}

} // namespace

int main()
{
  uid_t consoleUid = static_cast<uid_t>(-1);
  gid_t consoleGid = static_cast<gid_t>(-1);
  CFStringRef consoleUserRef = SCDynamicStoreCopyConsoleUser(nullptr, &consoleUid, &consoleGid);
  const std::string consoleUser = cfStringToUtf8(consoleUserRef);
  if (consoleUserRef != nullptr) {
    CFRelease(consoleUserRef);
  }

  const bool accessibilityTrusted = AXIsProcessTrusted();
  const bool listenEventAllowed = CGPreflightListenEventAccess();
  const bool postEventAllowed = CGPreflightPostEventAccess();

  std::cout << "{"
            << "\"uid\":" << getuid() << ","
            << "\"euid\":" << geteuid() << ","
            << "\"consoleUid\":" << consoleUid << ","
            << "\"consoleGid\":" << consoleGid << ","
            << "\"consoleUser\":\"" << jsonEscape(consoleUser) << "\","
            << "\"accessibilityTrusted\":" << boolJson(accessibilityTrusted) << ","
            << "\"listenEventAllowed\":" << boolJson(listenEventAllowed) << ","
            << "\"postEventAllowed\":" << boolJson(postEventAllowed)
            << "}" << std::endl;

  return 0;
}
