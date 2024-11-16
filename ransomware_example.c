#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int lock_file(const wchar_t* filename) {
    wchar_t full_path[MAX_PATH];
    swprintf(full_path, MAX_PATH, L"\\\\?\\%s", filename);

    wchar_t new_name[MAX_PATH];
    swprintf(new_name, MAX_PATH, L"\\\\?\\%s.locked", filename);

    wprintf(L"Attempting to rename: %s\n", full_path);

    if (MoveFileW(full_path, new_name) == 0) {
        DWORD errorCode = GetLastError();
        wprintf(L"Error renaming file %s. Error code: %lu\n", filename, errorCode);

        switch (errorCode) {
        case ERROR_FILE_NOT_FOUND:
            wprintf(L"Debug: File not found. Check the file path.\n");
            break;
        case ERROR_PATH_NOT_FOUND:
            wprintf(L"Debug: Path not found. Check directory structure.\n");
            break;
        default:
            wprintf(L"Debug: Unknown error occurred.\n");
            break;
        }
        return -1;
    }

    wprintf(L"File %s locked successfully.\n", filename);
    return 0;
}




void lock_directory(const wchar_t* dir_name) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    wchar_t dir_path[MAX_PATH];
    swprintf(dir_path, sizeof(dir_path) / sizeof(wchar_t), L"%s\\*", dir_name);  // Add wildcard * to find all files

    // Open the directory
    hFind = FindFirstFileW(dir_path, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"Unable to open the directory %s\n", dir_name);
        return;
    }

    do {
        // Skip the "." and ".." directories
        if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
            wchar_t full_path[MAX_PATH];
            swprintf(full_path, sizeof(full_path) / sizeof(wchar_t), L"%s\\%s", dir_name, findFileData.cFileName);

            // Check if it's a file or directory
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // If it's a directory, recurse into it
                lock_directory(full_path);
            }
            else {
                // If it's a file, try to lock it
                lock_file(full_path);
            }
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main() {
    wchar_t dir_name[MAX_PATH];

    // Ask the user for the directory path
    wprintf(L"Enter the directory path to lock: ");

    fgetws(dir_name, MAX_PATH, stdin);

    // Remove the newline character added by fgetws
    dir_name[wcslen(dir_name) - 1] = L'\0';

    // Lock all files in the directory
    lock_directory(dir_name);

    return 0;
}
