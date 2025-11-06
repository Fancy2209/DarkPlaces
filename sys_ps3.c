/*
 * Include this BEFORE darkplaces.h because it breaks wrapping
 * _Static_assert. Cloudwalk has no idea how or why so don't ask.
 */
//#include <SDL.h>
#include <sys/systime.h>
#include <ppu-types.h>

#include "darkplaces.h"

//#ifdef WIN32
//#ifdef _MSC_VER
//#pragma comment(lib, "sdl2.lib")
//#pragma comment(lib, "sdl2main.lib")
//#endif
//#endif


u64 sys_sdl_ps3_ticks_start = 0;

// =======================================================================
// General routines
// =======================================================================

void Sys_SDL_Shutdown(void)
{
	// TODO
}

// Sys_Error early in startup might screw with automated
// workflows or something if we show the dialog by default.
static qbool nocrashdialog = true;
void _nullcb(int a, void *b) {}
void Sys_SDL_Dialog(const char *title, const char *string)
{
	if(!nocrashdialog)
		msgDialogOpen(MSG_DIALOG_ERROR|MSG_DIALOG_BTN_TYPE_OK, string, nullcb, NULL, NULL);
}

char *Sys_SDL_GetClipboardData (void)
{
	return NULL;
}

void Sys_SDL_Init(void)
{
	sys_sdl_ps3_ticks_start = sysGetSystemTime();

	// COMMANDLINEOPTION: sdl: -nocrashdialog disables "Engine Error" crash dialog boxes
	if(!Sys_CheckParm("-nocrashdialog"))
		nocrashdialog = false;
}

qbool sys_supportsdlgetticks = true;
unsigned int Sys_SDL_GetTicks (void)
{
	return (u32)(((sysGetSystemTime() - sys_sdl_ps3_ticks_start)/1000) & 0xFFFFFFFF);
}
void Sys_SDL_Delay (unsigned int milliseconds)
{
	sysUsleep(milliseconds*1000);
}

int main(int argc, char *argv[])
{
	return Sys_Main(argc, argv);
}
