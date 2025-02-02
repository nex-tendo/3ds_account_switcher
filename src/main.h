/*
* file main.h
* Copyright 2025 Nextendo Network Contributors
* Licensed under MIT License
*/
#pragma once

#include <3ds.h>
#include <3ds/services/cfgu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <optional>
#include <vector>
#include <map>
#include <cstdio>
#include <algorithm>
#include <string>
#include "frda.h"
#include "acta.h"
#include "version.h"

#define NINTENDO_TEXT CONSOLE_YELLOW "Nintendo"
#define PRETENDO_TEXT CONSOLE_MAGENTA "Pretendo"
#define NEXTENDO_TEXT CONSOLE_BLUE "Nextendo"

#define NINTENDO_ACCOUNT_ID 1
#define PRETENDO_ACCOUNT_ID 2
#define NEXTENDO_ACCOUNT_ID 3

struct NASLocalAccount
{
    u8 accountId;
    NASType type;
    NASEnvironment env;
    u8 envNum;
};

enum Language {
    ENGLISH,
    FRENCH,
    JAPANESE
};

extern Language currentLanguage;

const char* texts[][3] = {
    {"== Nextendo Account Switcher ==\n", "== Nextendo Account Switcher ==\n", "== Nextendo Account Switcher ==\n"},
    {"\nPlease select a network:\n", "\nVeuillez selectionner un reseau :\n", "\nネットワークを選択してください:\n"},
    {"\nPress A to select " NINTENDO_TEXT ".\n", "\nAppuyez sur A pour selectionner " NINTENDO_TEXT ".\n", "\nAを押して" NINTENDO_TEXT "を選択します。\n"},
    {"Press Y to select " PRETENDO_TEXT ".\n", "Appuyez sur Y pour selectionner " PRETENDO_TEXT ".\n", "Yを押して" PRETENDO_TEXT "を選択します。\n"},
    {"Press X to select " NEXTENDO_TEXT ".\n", "Appuyez sur X pour selectionner " NEXTENDO_TEXT ".\n", "Xを押して" NEXTENDO_TEXT "を選択します。\n"},
    {"\nAccount Switcher Version: %s\n", "\nVersion du commutateur de compte : %s\n", "\nアカウントスイッチャーバージョン：%s\n"},
    {"\nPress START to exit.\n", "\nAppuyez sur START pour quitter.\n", "\n START を押すと終了します\n"}
};
