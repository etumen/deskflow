/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2015 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <QString>

#include <functional>

enum class OSXLoginHelperStatus
{
  Unsupported,
  NotRegistered,
  Enabled,
  RequiresApproval,
  NotFound
};

void requestOSXNotificationPermission();
bool isOSXDevelopmentBuild();
OSXLoginHelperStatus osxLoginHelperStatus();
bool setOSXLoginHelperEnabled(bool enabled, QString *errorMessage = nullptr);
void openOSXLoginItemsSettings();
bool showOSXNotification(const QString &title, const QString &body);
bool isOSXInterfaceStyleDark();
void forceAppActive();
void macOSNativeHide();
void installQuitHandler(std::function<bool()> shouldQuit);
