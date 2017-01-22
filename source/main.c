#include <3ds.h>
#include <stdio.h>
 
int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    osSetSpeedupEnable(true);
   
    Result nsInitResult;
 
    printf("veryslowpidhax\n");
   
    nsInitResult = nsInit();
    printf("nsInit(): %08X\n\n", (int)nsInitResult);
   
    u64 TitleId = 0x0004001000024000;
    u32 ProcessId;
    u32 LaunchFlags = 0;
    u32 TargetPid = 0x7FFFFFFF - 1;
   
    for (u32 i = 0; i < 0x80000000; i++) {
		NS_LaunchTitle(TitleId, LaunchFlags, &ProcessId);
		printf("ProcessId: %08X\n", (int)ProcessId);
		NS_TerminateProcessTID(TitleId);
		
		if (ProcessId >= TargetPid)
			break;
    }
	
    nsExit();
    printf("\n%08X Current PID\n", (int)ProcessId);
    printf("%08X Target PID\n", (int)ProcessId + 2);
    printf("Done, press start to exit.");
 
    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;
       
        gfxFlushBuffers();
        gfxSwapBuffers();
 
        gspWaitForVBlank();
    }
 
    gfxExit();
    return 0;
}