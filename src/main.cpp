/*
* file main.c
* Copyright 2025 Nextendo Network Contributors
* Licensed under MIT License
*/
#include "main.h"

Language currentLanguage = ENGLISH;

int main(int argc, char *argv[])
{
	gfxInitDefault();
	frdaInit();
	cfguInit();

	PrintConsole topConsole;
	consoleInit(GFX_TOP, &topConsole);
	consoleSelect(&topConsole);

	Result rc = 0;

	{
		ndmuInit();
		NDMU_SuspendDaemons(NDM_DAEMON_MASK_FRIENDS);
		ndmuExit();
	}

	{
		FRDA_SetClientSdkVersion(0x70000C8);
		FRDA_Save();
		rc = FRDA_UnloadLocalAccount();
		if (R_FAILED(rc) && rc != (Result)0xC8A0C4EE)
		{
			printf(CONSOLE_RED "Failed to unload local account.\n" CONSOLE_RESET);
			svcSleepThread(500000000UL);
			frdaExit();
			gfxExit();
			return 0;
		}
	}

	std::vector<NASLocalAccount> nasAccountList;

	u8 ids[] = {1, 2, 3};
	for (u8 id : ids)
	{
		Result rc = FRDA_LoadLocalAccount(id);
		if (R_SUCCEEDED(rc))
		{
			NASType type;
			NASEnvironment env;
			u8 envNum;
			FRDA_GetServerTypes(&type, &env, &envNum);
			NASLocalAccount localAccount = {.accountId = id, .type = type, .env = env, .envNum = envNum};
			nasAccountList.push_back(localAccount);
			FRDA_UnloadLocalAccount();
		}
	}

	FRDA_UnloadLocalAccount();

	consoleClear();

	u8 accountId = 1;
	NASType accountType = NAS_LIVE;
	NASEnvironment accountEnv = NAS_ENV_L;

	u8 language;
	CFGU_GetSystemLanguage(&language);

	switch (language) {
		case CFG_LANGUAGE_JP:
			currentLanguage = JAPANESE;
			break;
		case CFG_LANGUAGE_FR:
			currentLanguage = FRENCH;
			break;
		case CFG_LANGUAGE_EN:
		default:
			currentLanguage = ENGLISH;
			break;
	}

	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[0][currentLanguage]);
	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[1][currentLanguage]);
	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[2][currentLanguage]);
	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[3][currentLanguage]);
	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[4][currentLanguage]);
	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[5][currentLanguage]);
	printf(CONSOLE_CYAN "%s" CONSOLE_RESET, texts[6][currentLanguage]);

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_A) {
			accountId = NINTENDO_ACCOUNT_ID;
			accountType = NAS_LIVE;
			accountEnv = NAS_ENV_L;
			break;
		} else if (kDown & KEY_Y) {
			accountId = PRETENDO_ACCOUNT_ID;
			accountType = NAS_TEST;
			accountEnv = NAS_ENV_L;
			break;
		} else if (kDown & KEY_X) {
			accountId = NEXTENDO_ACCOUNT_ID;
			accountType = NAS_DEV;
			accountEnv = NAS_ENV_L;
			break;
		} else if (kDown & KEY_START) {
			printf(CONSOLE_RED "\nExiting..\n" CONSOLE_RESET);
			svcSleepThread(500000000UL);
			return 0;
		}
	}

	std::optional<NASLocalAccount> existingAccount = std::nullopt;

	for (const auto& n : nasAccountList) {
    	if (n.accountId == accountId && n.env == accountEnv && n.type == accountType) {
        	existingAccount = n;
        	break;
    	}
	}

	{
		if (existingAccount)
		{
			rc = FRDA_LoadLocalAccount(accountId);
			printf("DEBUGGER: Account Exist.\n");
		}
		else
		{
			rc = FRDA_CreateLocalAccount(accountId, accountType, accountEnv, 1);
			printf("DEBUGGER: Account Doesnt Exist.\n");
		}

		if (R_FAILED(rc))
		{
			printf(CONSOLE_RED "Failed to load/create an account.\n" CONSOLE_RESET, rc);
			svcSleepThread(500000000UL);
			return 0;
		}
		else
		{
			printf(CONSOLE_GREEN "Success !\n" CONSOLE_RESET);
			svcSleepThread(500000000UL);
			return 0;
		}
	}

	u8 id;
	rc = FRDA_GetMyLocalAccountId(&id);
	if (R_FAILED(rc)) {
		FRDA_LoadLocalAccount(NINTENDO_ACCOUNT_ID);
	}

	cfguExit();
	frdaExit();
	gfxExit();
	return 0;
}
