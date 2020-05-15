#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
LPSTR cmdline;

void GainAdminPrivileges(UINT idd, BOOL bWait){

    //strCmd.Format (_T("/adminoption %d"), idd);
    char strCmd[MAX_PATH];
    char strApp[MAX_PATH*10];
    sprintf(strCmd, "/adminoption %d", idd);
    sprintf(strApp, cmdline, idd);

    SHELLEXECUTEINFO execinfo;
    memset(&execinfo, 0, sizeof(execinfo));
    execinfo.lpFile			= strApp;
    execinfo.cbSize			= sizeof(execinfo);
    execinfo.lpVerb			= TEXT("runas");
    execinfo.fMask			= SEE_MASK_NOCLOSEPROCESS;
    execinfo.nShow			= SW_SHOWDEFAULT;
    execinfo.lpParameters	= strCmd;

    ShellExecuteEx(&execinfo);

    if(bWait)
        WaitForSingleObject(execinfo.hProcess, INFINITE);
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    cmdline = lpCmdLine;
    if (strcmp(lpCmdLine, "-i") == 0 || strcmp(lpCmdLine, "su") == 0 || strcmp(lpCmdLine, "") == 0) {
        strcpy(cmdline, (char*)"cmd.exe");
    }
    GainAdminPrivileges(1, 0);
    return 0;
}