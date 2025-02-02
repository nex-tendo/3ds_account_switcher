/*
* file main.h
* Copyright 2025 Nextendo Network Contributors
* Licensed under MIT License
*/
#pragma once

#include <3ds.h>
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

#define NINTENDO_TEXT CONSOLE_YELLOW "Nintendo Network"
#define PRETENDO_TEXT CONSOLE_MAGENTA "Nintendo Network"
#define NEXTENDO_TEXT CONSOLE_BLUE "Nextendo Network"

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
