#include <3ds.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include "frda.h"
#include "version.h"

#define ESCAPE_GO_BACK_1_LINE "\x1b[1A"

#define NINTENDO_TEXT CONSOLE_YELLOW "Nintendo" CONSOLE_CYAN
#define NEXTENDO_TEXT CONSOLE_MAGENTA "Nextendo" CONSOLE_CYAN

Result checkInternetConnection() {
    u32 wifiStatus = 0;
    Result rc = ACU_GetWifiStatus(&wifiStatus);

    if (R_FAILED(rc) || wifiStatus == 0) {
        return rc;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    gfxInitDefault();
    PrintConsole bottomConsole;
    consoleInit(GFX_BOTTOM, &bottomConsole);

    Result rc = frdaInit();
    if (R_FAILED(rc))
    {
        printf(CONSOLE_RED "Failed to initialize FRDA: 0x%08lX\n", rc);
        svcSleepThread(3000000000);
        gfxExit();
        return 0;
    }

    rc = checkInternetConnection();
    if (R_FAILED(rc)) {
        printf("Wi-Fi connection error: 0x%08lX\n", rc);
        svcSleepThread(3000000000);
        gfxExit();
        return 0;
    }

    FRDA_SetClientSdkVersion(0x70000C8);
    FRDA_Save();

    rc = FRDA_UnloadLocalAccount();
    if (R_FAILED(rc))
    {
        printf(CONSOLE_RED "Failed to unload local account: 0x%08lX\n", rc);
        svcSleepThread(3000000000);
        gfxExit();
        return 0;
    }

    u8 accountId = 1;
    NASType nastype = NAS_LIVE;
    NASEnvironment nasenv = NAS_ENV_L;

    consoleClear();

    printf("\n");
    printf(CONSOLE_CYAN "== Nextendo Account Switcher ==\n" CONSOLE_RESET);
    printf("\n");
    printf(CONSOLE_CYAN "Please select a network:\n" CONSOLE_RESET);
    printf(CONSOLE_CYAN "Press Y to switch to " NINTENDO_TEXT " Account.\n" CONSOLE_RESET);
    printf(CONSOLE_CYAN "Press X to switch to " NEXTENDO_TEXT " Account.\n" CONSOLE_RESET);
    printf("\n");
    printf(CONSOLE_CYAN "Press START to exit.\n" CONSOLE_RESET);
    printf("\n");
    printf("\n");
    printf(CONSOLE_CYAN "Account Switcher Version: %s\n", VERSION CONSOLE_RESET);

    while (aptMainLoop())
    {
        gspWaitForVBlank();
	    gfxSwapBuffers();
	    hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_Y)
        {
            accountId = 1;
            nastype = NAS_LIVE;
            nasenv = NAS_ENV_L;
            FRDA_LoadLocalAccount(accountId);
            printf("\n");
            printf(CONSOLE_CYAN " Patching " NINTENDO_TEXT " network..", ESCAPE_GO_BACK_1_LINE CONSOLE_RESET);
            svcSleepThread(3000000000);
            break;
        }

        if (kDown & KEY_X)
        {
            accountId = 2;
            nastype = NAS_TEST;
            nasenv = NAS_ENV_L;
            FRDA_CreateLocalAccount(accountId, nastype, nasenv, 1);
            FRDA_LoadLocalAccount(accountId);
            printf("\n");
            printf(CONSOLE_CYAN " Patching " NEXTENDO_TEXT " network..", ESCAPE_GO_BACK_1_LINE CONSOLE_RESET);
            svcSleepThread(3000000000);
            break;
        }

        if (kDown & KEY_START)
        {
            printf("\n");
            printf(CONSOLE_RED "Exiting..\n", ESCAPE_GO_BACK_1_LINE CONSOLE_RESET);
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
