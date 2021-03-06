/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_CURSOR_H
#define S3E_EXT_CURSOR_H

/**
 * @addtogroup s3egroup
 * @{
 */

/**
 * @defgroup edkCursorapigroup Cursor Extension API Reference
 *
 * This extension allows an application to display a native message box.
 *
 * This is an example extension supplied with the EDK. It is included to
 * demonstrate the implementation of a basic cross-platform extension and
 * is not intended for use in commercial applications.
 *
 * @{
 */

#include <s3eTypes.h>
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the Cursor extension is available.
 */
s3eBool CursorAvailable();

/**
 * Displays a modal message box with specified title and text.
 *
 * @par Required Header Files
 * Cursor.h
 */
bool Show_Cursor(bool bShow);

int32 Get_Cursor();

void Set_Cursor(int32 cursor);

S3E_END_C_DECL

/** @} */
/** @} */

#endif /* !S3E_EXT_CURSOR_H */
