#include "main.h"

int main(int argc, char *argv[])
{
    gfxInitDefault();
    
    Result rc = frdaInit();
    if (R_FAILED(rc)) {
        printf(CONSOLE_RED "Failed to initialize FRDA: 0x%08lX\n" CONSOLE_RESET, rc);
        gfxExit();
        return 0;
    }

    // TODO: Add to top screen and fix the text showing bug in top screen
    PrintConsole bottomScreen;
    consoleInit(GFX_BOTTOM, &bottomScreen);
    consoleSelect(&bottomScreen);

    {
        FRDA_SetClientSdkVersion(0x70000C8);
        FRDA_Save();
        rc = FRDA_UnloadLocalAccount();
        if(R_FAILED(rc) && rc != (Result)0xC8A0C433) {
            printf(CONSOLE_RED "Failed to unload local account: 0x%08lX\n" CONSOLE_RESET, rc);
            frdaExit();
            gfxExit();
            return 0;
        }
    }

    {
        ndmuInit();
        NDMU_SuspendDaemons(NDM_DAEMON_MASK_FRIENDS);
        ndmuExit();
    }

    u8 actId = 1;
    NASType nasType = NAS_LIVE;
    NASEnvironment nasEnv = NAS_ENV_L;

    std::vector<NASAccount> nasAccountList;

    for (int i = 0; i <= 255; i++)
	{
		u8 id = (u8)i;
		Result rc = FRDA_LoadLocalAccount(id);
		if (R_SUCCEEDED(rc))
		{
			NASType type;
			NASEnvironment env;
			u8 envNum;
			FRDA_GetServerTypes(&type, &env, &envNum);
			NASAccount localAccount = {.actId = id, .nasType = type, .nasEnv = env, .envNum = envNum};
			FriendKey key;
			FRDA_GetMyFriendKey(&key);
			localAccount.pid = key.principalId;
			nasAccountList.push_back(localAccount);
			FRDA_UnloadLocalAccount();
		}
	}

    FRDA_UnloadLocalAccount();

    auto search = std::find_if(nasAccountList.begin(), nasAccountList.end(), [actId, nasType, nasEnv](NASAccount const &n)
							   { return (n.actId == actId) && (n.nasEnv == nasEnv) && (n.nasType == nasType); });

	std::optional<NASAccount> existingAccount = std::nullopt;
	if (search != nasAccountList.end())
		existingAccount = *search;

    u32 kDown = 0;
    while(aptMainLoop()) {
        consoleClear();
        printf(CONSOLE_CYAN "== Nextendo Account Switcher ==\n\n" CONSOLE_RESET);
        printf(CONSOLE_CYAN "%c " NINTENDO_TEXT "\n", selection == 0 ? '>' : ' ', CONSOLE_RESET);
        printf(CONSOLE_CYAN "%c " NEXTENDO_TEXT "\n", selection == 1 ? '>' : ' ', CONSOLE_RESET);
        printf(CONSOLE_CYAN "Press START to exit.\n" CONSOLE_RESET);

        gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

        kDown = hidKeysDown();
        if(kDown & KEY_DOWN) {
            selection++;
            if(selection > 1) selection = 0;
        } else if (kDown & KEY_UP) {
            selection--;
            if (selection < 0) selection = 1;
        } else if (kDown & KEY_A) {
            // TODO: Add can't load/create an account without Wi-Fi
            if(existingAccount) {
                FRDA_LoadLocalAccount(actId);
            } else {
                FRDA_CreateLocalAccount(actId, nasType, nasEnv, 1);
            }
            printf(CONSOLE_GREEN "Success !\n" CONSOLE_RESET);
            svcSleepThread(500UL * (1000 * 1000));
            break;
        } else if (kDown & KEY_START) {
            break;
        }
    }

    if(selection >= 0) {
        // TODO: Add Pretendo service
        switch(selection) {
            default:
            case 0:
                actId = 1;
                nasType = NAS_LIVE;
                nasEnv = NAS_ENV_L;
                break;
            case 1:
                actId = 2;
                nasType = NAS_TEST;
                nasEnv = NAS_ENV_L;
                break;
        }
    }

    frdaExit();
    gfxExit();
    return 0;
}
