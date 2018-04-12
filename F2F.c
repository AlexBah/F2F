/* 	C; send and launch file in all folder*/
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

void LaunchFile(TCHAR szPath[MAX_PATH + 1])
{
  STARTUPINFO si;
  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi;
  memset(&pi, 0, sizeof(pi));
  if ( CreateProcess(NULL, szPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) ) {
    DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
	}
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  }
	
int main(int argc, char* argv[])
{
	// verify argv[1]
	if (argc < 1) {
		printf( "Wait name of file\n" );
		return EXIT_FAILURE;
		}
	// verify exist of file
	FILE *pTextFile = fopen(argv[1], "r");
    if(pTextFile == NULL) {
		printf( "Can't find file %s\n", argv[1]);
		return EXIT_FAILURE;
		}
	fclose(pTextFile);

	WIN32_FIND_DATA ffd;
    HANDLE hFind;
    TCHAR szFind[MAX_PATH + 1] = "";
    lstrcat(szFind, "*.*");
    hFind = FindFirstFile(szFind, &ffd);
    do
    {
	// verify object is folder
		if(ffd.dwFileAttributes & 0x00000010)
            {
            if(lstrcmp(ffd.cFileName, ".") == 0 ||
                lstrcmp(ffd.cFileName, "..") == 0) continue;
				// if object is folder, send file where
				lstrcpy(szFind, ffd.cFileName);
				lstrcat(szFind, "\\");
				lstrcat(szFind, argv[1]);
				CopyFile(argv[1], szFind, TRUE);
				printf( "Copied file to %s\n", szFind);
				SetCurrentDirectory(ffd.cFileName);
				LaunchFile(szFind);
				SetCurrentDirectory("..");
				printf( "launched file to %s\n", szFind);
            }
    }
    while(FindNextFile(hFind, &ffd));
    FindClose(hFind);
	return EXIT_SUCCESS;
}
