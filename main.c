#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <sec_api/tchar_s.h>

void connectRussian() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru-RU.UTF8");
}

void task1() {
    DWORD drivers = GetLogicalDrives();
    printf("Список доступных дисков: \n");
    for (char i = 0; i < 32; i++) {
        if (drivers & (1 << i)) {
            char driveLetter = (char)('A' + i);
            printf("%c:\\\n", driveLetter);
        }
    }
}

void task2() {
    char nameBuffer[MAX_PATH + 1];
    char systemNameBuffer[MAX_PATH + 1];
    DWORD serialNumber;
    DWORD maxComponentLength;
    DWORD fileSystemFlags;
    if (GetVolumeInformationA(
            "C:\\",
            nameBuffer,
            sizeof (nameBuffer),
            &serialNumber,
            &maxComponentLength,
            &fileSystemFlags,
            systemNameBuffer,
            sizeof (systemNameBuffer)
    )) {
        printf("Имя тома: %s\n", nameBuffer);
        printf("Имя файловой системы: %s\n", systemNameBuffer);
        printf("Серийный номер: %lu\n", serialNumber);
        printf("Максимальный размер компонента: %lu\\n", maxComponentLength);
        printf("Флаги файловой системы: 0x%lX\\n", fileSystemFlags);
    } else {
        printf("В ходе выполнения GetVolumeInformation была получена ошибка %lu", GetLastError());
    }
}

void task3() {
    TCHAR relativePath[MAX_PATH];
    TCHAR fullPath[MAX_PATH];
    _tcscpy_s(relativePath, MAX_PATH, _T("test.txt"));
    DWORD length = GetFullPathName(relativePath, MAX_PATH, fullPath, NULL);
    if (length == 0) {
        DWORD error = GetLastError();
    } else if (length > MAX_PATH) {
        printf("Путь слишком длинный для буфера\n");
    } else {
        _tprintf(_T("Полный путь: %s\n"), fullPath);
    }
}

void task4() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(_T("C:\\*"), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Ошибка при вызове FindFirstFile: %lu\n", GetLastError());
        return;
    }
    do {
        _tprintf(_T("Имя файла: %s\n"), findFileData.cFileName);
        _tprintf(_T("Тип файла: %s\n"), (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? _T("Папка") : _T("Файл"));
        _tprintf(_T("Размер файла: %lu bytes\n"), findFileData.nFileSizeLow);

        FILETIME ft = findFileData.ftLastWriteTime;
        SYSTEMTIME st;
        FileTimeToSystemTime(&ft, &st);

        _tprintf(_T("Дата последнего изменения: %02d/%02d/%d %02d:%02d\n\n"), st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute);
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void task5() {
    TCHAR buffer[MAX_PATH];
    if (GetWindowsDirectory(buffer, MAX_PATH) == 0) {
        printf("Ошибка при вызове GetWindowsDirectory: %lu\n", GetLastError());
        return;
    }

    _tprintf(_T("Путь к каталогу Windows: %s\n"), buffer);
}

void task6() {
    TCHAR buffer[MAX_PATH];
    DWORD length = GetTempPath(MAX_PATH, buffer);
    if (length == 0 || length > MAX_PATH) {
        printf("Ошибка при вызове GetTempPath: %lu\n", GetLastError());
        return;
    }

    _tprintf(_T("Путь к временному каталогу: %s\n"), buffer);
}

void task7() {
    if (!SetVolumeLabel(_T("C:\\"), _T("Мой_Диск"))) {
        printf("Ошибка при вызове SetVolumeLabel: %lu\n", GetLastError());
        return;
    }

    _tprintf(_T("Метка тома успешно изменена\n"));
}

void task8() {
    if (!RemoveDirectory(_T("C:\\example_directory"))) {
        printf("Ошибка при вызове RemoveDirectory: %lu\n", GetLastError());
        return;
    }

    _tprintf(_T("Каталог успешно удален\n"));
}

void task9() {
    HANDLE hFile = CreateFile(_T("C:\\example.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Ошибка при вызове CreateFile: %lu\n", GetLastError());
        return;
    }

    CloseHandle(hFile);
    _tprintf(_T("Файл успешно создан\n"));
}

void task10() {
    HANDLE hFile = CreateFile(_T("C:\\example.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Ошибка при вызове CreateFile: %lu\n", GetLastError());
        return;
    }

    TCHAR data[] = _T("Пример текста для записи в файл.");
    DWORD bytesWritten;
    if (!WriteFile(hFile, data, sizeof(data), &bytesWritten, NULL)) {
        printf("Ошибка при вызове WriteFile: %lu\n", GetLastError());
        CloseHandle(hFile);
        return;
    }

    CloseHandle(hFile);
    _tprintf(_T("Данные успешно записаны в файл\n"));
}

void task11() {
    if (!CopyFile(_T("C:\\source_file.txt"), _T("C:\\destination_file.txt"), FALSE)) {
        printf("Ошибка при вызове CopyFile: %lu\n", GetLastError());
        return;
    }
    _tprintf(_T("Файл успешно скопирован\n"));
}


int main() {
    connectRussian();
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    task10();
    task11();
    return 0;
}