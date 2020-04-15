// ============================================================================
//
// This file contains routines that are handled during the Edittime.
//
// Including creating, display, and setting up your object.
// 
// ============================================================================

#ifndef RUN_ONLY

// Common
#include	"common.h"

// Prototype of setup procedure
BOOL CALLBACK DLLExport setupProc(HWND hDlg,uint msgType,WPARAM wParam,LPARAM lParam);

// Structure defined to pass edptr and mv into setup box
typedef struct tagSetP
{
	EDITDATA _far *	edpt;
	mv _far	*		kv;
} setupParams;

/*
// -----------------
// BmpToImg
// -----------------
// Converts an image from the resource to an image displayable under CC&C
// Not used in this template, but it is a good example on how to create
// an image.
WORD BmpToImg(int bmID, npAppli idApp)
{
	Img					ifo;
	WORD				img;
	HRSRC				hs;
	HGLOBAL				hgBuf;
	LPBYTE				adBuf;
	LPBITMAPINFOHEADER	adBmi;

	img = 0;
	if ((hs = FindResource(hInstLib, MAKEINTRESOURCE(bmID), RT_BITMAP)) != NULL)
	{
		if ((hgBuf = LoadResource(hInstLib, hs)) != NULL)
		{
			if ((adBuf = (LPBYTE)LockResource(hgBuf)) != NULL)
			{
				adBmi = (LPBITMAPINFOHEADER)adBuf;
				ifo.imgXSpot = ifo.imgYSpot = ifo.imgXAction = ifo.imgYAction = 0;
				if (adBmi->biBitCount > 4)
					RemapDib((LPBITMAPINFO)adBmi, idApp, NULL);
				img = DibToImage(idApp, &ifo, adBmi);
				UnlockResource(hgBuf);
			}
			FreeResource(hgBuf);
		}
	}
	return img;
}
*/

// -----------------
// Initialize
// -----------------
// Where you want to do COLD-START initialization. Only called ONCE per application.
// 
extern "C" int WINAPI DLLExport Initialize(mv _far *knpV, int quiet)
{
	// No errors
	return 0;
}

// -----------------
// Free
// -----------------
// Where you want to kill and initialized data opened in the above routine
// Called ONCE per application, just before freeing the DLL.
// 
extern "C" int WINAPI DLLExport Free(mv _far *knpV)
{
	// No errors
	return 0;
}

// --------------------
// UpdateEditStructure
// --------------------
// For you to update your object structure to newer versions
// 
HGLOBAL WINAPI DLLExport UpdateEditStructure(mv __far *knpV, void __far * OldEdPtr)
{
	// We do nothing here
	return 0;
}

// -----------------
// LoadObject
// -----------------
// Routine called for each object, when the object is dropped in the frame.
// You can load data here, reserve memory etc...
// Called once per different object, just after loading extension data
int	WINAPI DLLExport LoadObject(mv _far *knpV, LPCSTR fileName, LPEDATA edPtr, int reserved)
{
	return 0;
}

// -----------------
// UnloadObject
// -----------------
// The counterpart of the above routine: called just before the object is
// deleted from the frame
void WINAPI DLLExport UnloadObject(mv _far *knpV, LPEDATA edPtr, int reserved)
{
}

// --------------------
// UpdateFileNames
// --------------------
// If you store file names in your datazone, they have to be relocated when the
// application is moved: this routine does it.
// 
void WINAPI DLLExport UpdateFileNames(mv _far *knpV, LPSTR gameName, LPEDATA edPtr, void (WINAPI * lpfnUpdate)(LPSTR, LPSTR))
{
}

// --------------------
// PutObject
// --------------------
// Called when each individual object is dropped in the frame.
//
void WINAPI	DLLExport PutObject(mv _far *knpV, fpLevObj loPtr, LPEDATA edPtr, ushort cpt)
{
}

// --------------------
// RemoveObject
// --------------------
// Called when each individual object is removed in the frame.
//
void WINAPI	DLLExport RemoveObject(mv _far *knpV, fpLevObj loPtr, LPEDATA edPtr, ushort cpt)
{
	// Is the last object removed?
    if (0 == cpt)
	{
		// Do whatever necessary to remove our data

	}

}
/*
// --------------------
// MakeIcon
// --------------------
// Called once object is created or modified, just after setup.
//
int WINAPI DLLExport MakeIcon ( mv _far *knpV, BITMAPINFO FAR *lpBitmap, LPSTR lpName, fpObjInfo oiPtr, LPEDATA edPtr )
{
	int					error = -1;
	ushort				pSize, bSize;
	HRSRC				hs;
	HGLOBAL				hgBuf;
	LPBYTE				adBuf;
	LPBITMAPINFOHEADER	adBmi;

	// Here, we simply load the icon from the resource and convert it into a format understood by CC&C.
	// You could also generate the icon yourself from what the user has entered in the setup.
	if ((hs = FindResource(hInstLib, MAKEINTRESOURCE(EXO_ICON), RT_BITMAP)) != NULL)
	{
		if ((hgBuf = LoadResource(hInstLib, hs)) != NULL)
		{
			if ((adBuf = (LPBYTE)LockResource(hgBuf)) != NULL)
			{
				adBmi = (LPBITMAPINFOHEADER)adBuf;
				pSize = (adBmi->biBitCount > 8) ? 0 : (4 << (BYTE) adBmi->biBitCount);
				bSize = (((WORD)adBmi->biWidth * adBmi->biBitCount + 31) &~ 31) / 8 * (WORD)adBmi->biHeight;
				_fmemcpy(lpBitmap, adBuf, sizeof(BITMAPINFOHEADER) + pSize + bSize);
				error = FALSE;
				UnlockResource (hgBuf);
			}
			FreeResource(hgBuf);
		}
	}
	return error;
}
*/
// --------------------
// AppendPopup
// --------------------
// Called just before opening the popup menu of the object under the editor.
// You can remove or add options to the default menu...
void WINAPI DLLExport AppendPopup(mv _far *knpV, HMENU hPopup, fpLevObj loPtr, LPEDATA edPtr, int nbSel)
{
}

// --------------------
// CreateObject
// --------------------
// Called when you choose "Create new object". It should display the setup box 
// and initialize everything in the datazone.

int WINAPI DLLExport CreateObject(mv _far *knpV, fpLevObj loPtr, LPEDATA edPtr)
{
	
	setupParams		spa;

	// Set default object flags
	edPtr->sx = 0;
	edPtr->sy = 0;
	edPtr->swidth = 32;
	edPtr->sheight = 32;

	// Call setup (remove this and return 0 if your object does not need a setup)
	spa.edpt = edPtr;
	spa.kv = knpV;
	return ((int) DialOpen(hInstLib, MAKEINTRESOURCE(DB_SETUP), knpV->mvHEditWin, setupProc, 0, 0, DL_MODAL|DL_CENTER_WINDOW, (LPARAM)(LPBYTE)&spa));
}

// --------------------
// SelectPopup
// --------------------
// One of the option from the menu has been selected, and not a default menu option
// automatically handled by CC&C: this routine is then called.
//
int WINAPI DLLExport SelectPopup(mv _far *knpV, int modif, fpObjInfo oiPtr, fpLevObj loPtr, LPEDATA edPtr, fpushort lpParams, int maxParams)
{
	setupParams		spa;

	// Remove this if your object does not need a setup
	if (modif == ID_POP_SETUP)
	{

		spa.edpt = edPtr;
		spa.kv = knpV;
		if (0 == DialOpen(hInstLib, MAKEINTRESOURCE(DB_SETUP), knpV->mvHEditWin, setupProc, 0, 0, DL_MODAL | DL_CENTER_WINDOW, (LPARAM)(LPBYTE)&spa))
			return MODIF_HFRAN;
	}

/* if your object can be resized, remove the remark!
	if (MODIF_SIZE == modif)
	{
		edPtr->swidth = lpParams[2];
		edPtr->sheight = lpParams[3];
	}
*/
	return 0;
}

// --------------------
// SetupProc
// --------------------
// This routine is yours. You may even not need a setup dialog box.
// I have put it as an example...
BOOL CALLBACK DLLExport setupProc(HWND hDlg,uint msgType,WPARAM wParam,LPARAM lParam)
{
	setupParams	_far *	spa;
	EDITDATA _far *		edPtr;

	switch (msgType)
	{
	case WM_INITDIALOG: // Init dialog
		SetWindowLong(hDlg, DWL_USER, lParam);
		return TRUE;

	case WM_COMMAND: // Command
		spa = (setupParams far *)GetWindowLong(hDlg, DWL_USER);
		edPtr = spa->edpt;

		switch (wmCommandID)
		{
		case IDOK:
            // End dialog
			EndDialog(hDlg, 0);
			return 0;

		case IDCANCEL:
			EndDialog(hDlg, -1);
			return 0;

		default:
			break;
		}
		break;

	default:
		break;
	}
	return FALSE;
}


// --------------------
// ModifyObject
// --------------------
// Called by CC&C when the object has been modified
//
int WINAPI DLLExport ModifyObject(mv _far *knpV, LPEDATA edPtr, fpObjInfo oiPtr, fpLevObj loPtr, int modif, fpushort lpParams)
{
	
	// Modification in size?
	if (MODIF_SIZE == modif)
	{
		edPtr->swidth = lpParams[2];
		edPtr->sheight = lpParams[3];
	}
	// No errors...
	return 0;
}


// --------------------
// GetObjectRect
// --------------------
// Returns the size of the rectangle of the object in the frame window
//
void WINAPI DLLExport GetObjectRect(mv _far *knpV, RECT FAR *rc, fpLevObj loPtr, LPEDATA edPtr)
{
	//Print("GetObjectRect");
	rc->right = rc->left + edPtr->swidth;
	rc->bottom = rc->top + edPtr->sheight;
	return;
}

/*
// --------------------
// EditorDisplay
// --------------------
// Displays the object under the frame editor
//
void WINAPI DLLExport EditorDisplay(mv _far *knpV, fpObjInfo oiPtr, fpLevObj loPtr, LPEDATA edPtr, RECT FAR *rc)
{
	LPSURFACE ps = WinGetSurface((int)knpV->mvIdEditWin);
	if ( ps != NULL )
	{
		int x = rc->left;
		int y = rc->top;
		int w = rc->right-rc->left;
		int h = rc->bottom-rc->top;

		cSurface is;
		is.Create(4, 4, ps);
		is.LoadImage(hInstLib, EXO_IMAGE, LI_REMAP);
		is.Blit(*ps, x, y, BMODE_TRANSP, BOP_COPY, 0);
	}
}
*/

// --------------------
// IsTransparent
// --------------------
// This routine tells CC&C if the mouse pointer is over a transparent zone of the object.
// 

extern "C" {
	BOOL WINAPI DLLExport IsTransparent(mv _far *knpV, fpLevObj loPtr, LPEDATA edPtr, int dx, int dy)
	{
		return FALSE;
	}
}

// --------------------
// PrepareToWriteObject
// --------------------
// Just before writing the datazone when saving the application, CC&C calls this routine.
// 
void WINAPI	DLLExport PrepareToWriteObject(mv _far *knpV, LPEDATA edPtr, fpObjInfo adoi)
{
}

// --------------------
// UsesFile
// --------------------
// Triggers when a file is dropped onto the frame
BOOL WINAPI	DLLExport UsesFile (LPMV mV, LPSTR fileName)
{
	
	// Return TRUE if you can create an object from the given file
	return FALSE;

	// Example: return TRUE if file extension is ".txt"
/*	BOOL	r = FALSE;
	NPSTR	ext, npath;

	if ( fileName != NULL )
	{
		if ( (ext=(NPSTR)LocalAlloc(LPTR, _MAX_EXT)) != NULL )
		{
			if ( (npath=(NPSTR)LocalAlloc(LPTR, _MAX_PATH)) != NULL )
			{
				_fstrcpy(npath, fileName);
				_splitpath(npath, NULL, NULL, NULL, ext);
				if ( _stricmp(ext, ".txt") == 0 )
					r = TRUE;
				LocalFree((HLOCAL)npath);
			}
			LocalFree((HLOCAL)ext);
		}
	}
	return r; */
}


// --------------------
// CreateFromFile
// --------------------
// Creates a new object from file
void WINAPI	DLLExport CreateFromFile (LPMV mV, LPSTR fileName, LPEDATA edPtr)
{
	// Initialize your extension data from the given file
	edPtr->swidth = 32;
	edPtr->sheight = 32;

	// Example: store the filename
	// _fstrcpy(edPtr->myFileName, fileName);
}

// ---------------------
// EnumElts
// ---------------------
int WINAPI DLLExport EnumElts (mv __far *knpV, LPEDATA edPtr, ENUMELTPROC enumProc, ENUMELTPROC undoProc, LPARAM lp1, LPARAM lp2)
{  
	int error = 0;
/*
	//Uncomment this if you need to store an image in the image bank.
	//Replace imgidx with the variable you create within the edit structure
  
	// Enum images  
	if ( (error = enumProc(&edPtr->imgidx, IMG_TAB, lp1, lp2)) != 0 )
	{
		// Undo enum images      
		undoProc (&edPtr->imgidx, IMG_TAB, lp1, lp2);    
	}  
*/
	return error;
}

#endif //Not RUN_ONLY