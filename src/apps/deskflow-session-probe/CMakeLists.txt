# SPDX-License-Identifier: MIT

if(NOT APPLE)
  return()
endif()

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices REQUIRED)
find_library(SYSTEM_CONFIGURATION_FRAMEWORK SystemConfiguration REQUIRED)

add_executable(deskflow-session-probe
  session-probe.cpp
)

target_link_libraries(deskflow-session-probe PRIVATE
  ${APPLICATION_SERVICES_FRAMEWORK}
  ${SYSTEM_CONFIGURATION_FRAMEWORK}
)

install(
  TARGETS deskflow-session-probe
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
  FILES net.etumen.deskflow.login-probe.plist
  DESTINATION "${CMAKE_PROJECT_PROPER_NAME}.app/Contents/Library/LaunchAgents"
)
