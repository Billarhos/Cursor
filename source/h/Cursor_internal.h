/*
 * Internal header for the Cursor extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 *
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#ifndef CURSOR_INTERNAL_H
#define CURSOR_INTERNAL_H

#include "Cursor.h"
#include "Cursor_autodefs.h"


struct CursorGlobals
{
    bool m_CursorRunning;
};

/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult CursorInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult CursorInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void CursorTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void CursorTerminate_platform();

/**
 * Platform-specific code to display message box.
 */

bool Show_Cursor(bool bShow);

int32 Get_Cursor();

void Set_Cursor(int32 cursor);

/**
 * Called by platform code when dialog has been closed.
 */
void CursorComplete();

#endif /* !CURSOR_INTERNAL_H */
