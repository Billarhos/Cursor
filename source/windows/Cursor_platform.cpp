
/*
 * windows-specific implementation of the Cursor extension.
 * Add any platform-specific functionality here.
 *
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#include "Cursor_internal.h"
#include <stdio.h>

#define OEMRESOURCE
#include <windows.h>

HCURSOR hAlphaCursor(NULL);
HCURSOR hAlphaCursorCopy(NULL);

HCURSOR hcArrow(NULL);
HCURSOR hcArrowCopy(NULL);

bool visible(true);

s3eResult CursorInit_platform()
{
	//HDC hMemDC;
	DWORD dwWidth, dwHeight;
	BITMAPV5HEADER bi;
	HBITMAP hBitmap;//, hOldBitmap;
	void *lpBits;
	DWORD x,y;


	dwWidth  = 32;  // width of cursor
	dwHeight = 32;  // height of cursor

	ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
	bi.bV5Size           = sizeof(BITMAPV5HEADER);
	bi.bV5Width           = dwWidth;
	bi.bV5Height          = dwHeight;
	bi.bV5Planes = 1;
	bi.bV5BitCount = 32;
	bi.bV5Compression = BI_BITFIELDS;
	// The following mask specification specifies a supported 32 BPP
	// alpha format for Windows XP.
	bi.bV5RedMask   =  0x00FF0000;
	bi.bV5GreenMask =  0x0000FF00;
	bi.bV5BlueMask  =  0x000000FF;
	bi.bV5AlphaMask =  0xFF000000; 

	HDC hdc;
	hdc = GetDC(NULL);

	// Create the DIB section with an alpha channel.
	hBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, 
		(void **)&lpBits, NULL, (DWORD)0);

	//hMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(NULL,hdc);

	// Draw something on the DIB section.
	/*hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
	SetTextColor(hMemDC,RGB(0,0,0));
	SetBkMode(hMemDC,TRANSPARENT);
	TextOut(hMemDC,0,9,"rgba",4);
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);*/

	// Create an empty mask bitmap.
	HBITMAP hMonoBitmap = CreateBitmap(dwWidth, dwHeight, 1, 1, NULL);

	// Set the alpha values for each pixel in the cursor so that
	// the complete cursor is semi-transparent.
	DWORD *lpdwPixel;
	lpdwPixel = (DWORD *)lpBits;
	for (x=0;x<dwWidth;x++)
	{
		for (y=0;y<dwHeight;y++)
		{
			// Clear the alpha bits
			*lpdwPixel &= 0x00FFFFFF;
			// Set the alpha bits to 0x9F (semi-transparent)
			*lpdwPixel|= 0x01000000; //0x9F000000;
			lpdwPixel++;
		}
	}

	ICONINFO ii;
	ii.fIcon = FALSE;  // Change fIcon to TRUE to create an alpha icon
	ii.xHotspot = 0;
	ii.yHotspot = 0;
	ii.hbmMask =  hMonoBitmap;
	ii.hbmColor = hBitmap;

	// Create the alpha cursor with the alpha DIB section.
	hAlphaCursor = CreateIconIndirect(&ii);
	hAlphaCursorCopy = CopyCursor(hAlphaCursor);

	DeleteObject(hBitmap);          
	DeleteObject(hMonoBitmap); 

    hcArrow = LoadCursor(0, IDC_ARROW);
    hcArrowCopy = CopyCursor(hcArrow);    
    
	//http://cboard.cprogramming.com/windows-programming/66327-restoring-cursor.html


	return S3E_RESULT_SUCCESS;
}

void CursorTerminate_platform()
{
	if (hcArrowCopy)
		SetSystemCursor(hcArrowCopy, OCR_NORMAL);
	//Add any platform-specific termination code here
}

bool Show_Cursor(bool bShow)
{
	if (!hcArrowCopy || !hAlphaCursorCopy)
		return false;

	if (visible && bShow)
		return false;

	if (!visible && !bShow)
		return false;

	if (bShow)
	{
		SetSystemCursor(hcArrowCopy, OCR_NORMAL);
		hcArrowCopy = CopyCursor(hcArrow); 
		visible = true;
		return true;
	}
	else
	{
		SetSystemCursor(hAlphaCursorCopy, OCR_NORMAL);
		hAlphaCursorCopy = CopyCursor(hAlphaCursor);
		visible = false;
		return true;
	}
	return false;
}

int32 Get_Cursor()
{
	return (int32)GetCursor();
}

void Set_Cursor(int32 cursor)
{
	SetCursor((HCURSOR)cursor);
}


