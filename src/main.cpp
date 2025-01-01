#include <3ds.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include "frda.h"

#define NINTENDO_TEXT CONSOLE_YELLOW "Nintendo" CONSOLE_CYAN
#define NEXTENDO_TEXT CONSOLE_MAGENTA "Nextendo" CONSOLE_CYAN

int main(int argc, char *argv[])
{
    frdaInit();
    gfxInitDefault();
    PrintConsole bottomConsole;
    consoleInit(GFX_BOTTOM, &bottomConsole);

    // Set Client SDK Version
    FRDA_SetClientSdkVersion(0x70000C8);
    FRDA_Save();
    FRDA_UnloadLocalAccount();

    std::string serverName = "Nintendo";
    u8 accountId = 1;
    NASType nastype = NAS_LIVE;
    NASEnvironment nasenv = NAS_ENV_L;

    consoleClear();

    printf("\n");
    printf(CONSOLE_CYAN "== Nextendo Account Switcher ==\n" CONSOLE_RESET);
    printf("\n");
    printf(CONSOLE_CYAN "Please select a network:\n" CONSOLE_RESET);
    printf(CONSOLE_CYAN "Press A to switch to " NINTENDO_TEXT " Account.\n" CONSOLE_RESET);
    printf(CONSOLE_CYAN "Press X to switch to " NEXTENDO_TEXT " Account.\n" CONSOLE_RESET);
    printf("\n");
    printf(CONSOLE_CYAN "Press START to exit.\n" CONSOLE_RESET);

    while (aptMainLoop())
    {
        gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_A)
        {
            serverName = "Nintendo";
            accountId = 1;
            nastype = NAS_LIVE; // Switch to nasc live/prod url
            nasenv = NAS_ENV_L;
            FRDA_LoadLocalAccount(accountId);
            printf("\n");
            printf(CONSOLE_CYAN " Patching " NINTENDO_TEXT " network.." CONSOLE_RESET);
            svcSleepThread(3000000000);
            break;
        }

        if (kDown & KEY_X)
        {
            serverName = "Nextendo";
            accountId = 2;
            nastype = NAS_TEST; // Switch to nasc test url
            nasenv = NAS_ENV_L;
            FRDA_CreateLocalAccount(accountId, nastype, nasenv, 1);
            FRDA_LoadLocalAccount(accountId);
            printf("\n");
            printf(CONSOLE_CYAN " Patching " NEXTENDO_TEXT " network.." CONSOLE_RESET);
            svcSleepThread(3000000000);
            break;
        }

        if (kDown & KEY_START)
        {
            printf("\n");
            printf(CONSOLE_RED "Exiting..\n" CONSOLE_RESET);
            svcSleepThread(3000000000);
            break;
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    frdaExit();
    return 0;
}