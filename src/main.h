#pragma once

#include <3ds.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <optional>
#include <algorithm>
#include "frda.h"
#include "acta.h"
#include "version.h"

#define NINTENDO_TEXT CONSOLE_YELLOW "Nintendo" CONSOLE_CYAN
#define NEXTENDO_TEXT CONSOLE_BLUE "Nextendo" CONSOLE_CYAN

int selection = 0;

struct NASAccount 
{
    u32 pid;
    u8 actId;
    NASType nasType;
    NASEnvironment nasEnv;
    u8 envNum;
};
