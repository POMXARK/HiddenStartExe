#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <codecvt>
using namespace std;

// C++ обязательно необходимо обьявить функцию перед её использованием
std::wstring stringToWstring(const std::string& t_str);
void procces_run(wstring file_mane);

extern "C" __declspec(dllexport) void HiddenStart(const char* prog) {
    std:wstring file_name = stringToWstring(prog); // Конвертер 
    procces_run(file_name); // запуск exe
} // публичная функция для вызова из вне __declspec(dllexport)

// ЗАПУСК EXE ->


void procces_run(wstring file_mane) // запуск процесса скрытно , без остановки основной программы
{



    // преобразовать в std :: wstring
   // std::wstring file_mane;

    // получить временный LPWSTR (не совсем безопасно)
    //wstring file_mane = file_mane;
    //LPWSTR pwst = &file_mane[0];

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));


       // Запускаем дочерний процесс.
    if (!CreateProcess(NULL,    // No module name (use command line)
        &file_mane[0], // Command line // WSTRING TO LPWSTR Строку в тип
        NULL,    // Process handle not inheritable
        NULL,    // Thread handle not inheritable
        FALSE,   // Set handle inheritance to FALSE
        0,       // No creation flags
        NULL,    // Use parent's environment block
        NULL,    // Use parent's starting directory
        &si,     // Pointer to STARTUPINFO structure
        &pi)     // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Ждем завершения дочернего процесса.
    //WaitForSingleObject(pi.hProcess, INFINITE);

    // Закрываем дескрипторы процесса и потока.
    //CloseHandle(pi.hProcess);
    //CloseHandle(pi.hThread);
}


// ЗАПУСК EXE <-


// КОНВЕРТЕР ->
std::wstring stringToWstring(const std::string& t_str)
{
    // setup converter
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;

    // use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    return converter.from_bytes(t_str);
}

// КОНВЕРТЕР <-


