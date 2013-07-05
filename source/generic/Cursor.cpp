
/*
Generic implementation of the Cursor extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

/**
 * @page EDKExtensionCursorSource Mac Address Extension Source Code and Project Files
 *
 * Cursor.mkf (includes this extension as a subproject):
 * @include Cursor.mkf
 *
 * Internal header (source/h/Cursor_internal.h):
 * @include ../h/Cursor_internal.h
 *
 * Generic source (source/generic/CursorApp.cpp):
 * @include Cursor.cpp
 *
 * Windows source (source/windows/Cursor_platform.cpp):
 * @include ../windows/Cursor_platform.cpp
 */

#include "Cursor_internal.h"
#include "s3eEdk.h"

s3eResult CursorInit()
{
    //Add any generic initialisation code here
    return CursorInit_platform();
}

void CursorTerminate()
{
    //Add any generic termination code here
   CursorTerminate_platform();
}

void CursorComplete()
{
    CURSORGLOBALS->m_CursorRunning = false;
}


bool ShowCursor(bool bShow)
{
	CURSORGLOBALS->m_CursorRunning = true;

 	 int32 address = (int32)(intptr_t)s3eEdkThreadRunOnOS((s3eEdkThreadFunc)Show_Cursor, 0);
	 while (CURSORGLOBALS->m_CursorRunning)
        {
            s3eEdkThreadSleep(1);
        }
	 return (address) ? true : false;
}

int32 GetCursor(void)
{
	CURSORGLOBALS->m_CursorRunning = true;

 	 int32 address = (int32)(intptr_t)s3eEdkThreadRunOnOS((s3eEdkThreadFunc)Get_Cursor, 0);
	 while (CURSORGLOBALS->m_CursorRunning)
        {
            s3eEdkThreadSleep(1);
        }
	 return address;
}

void SetCursor(int32 cursor)
{
	CURSORGLOBALS->m_CursorRunning = true;
	 s3eEdkThreadRunOnOS((s3eEdkThreadFunc)Set_Cursor, 0);
	 while (CURSORGLOBALS->m_CursorRunning)
        {
            s3eEdkThreadSleep(1);
        }
}




