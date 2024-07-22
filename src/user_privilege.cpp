// https://github.com/nodejs/node-addon-examples/tree/main/src
#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#pragma comment(lib, "Netapi32.lib")

// преобразование std::string в std::wstring
// взят по подобию https://stackoverflow.com/questions/6693010/how-do-i-use-multibytetowidechar
// https://stackoverflow.com/a/27296
std::wstring StringToWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], size_needed);
    return wstr;
}

// проверка, является ли пользователь членом группы
// https://learn.microsoft.com/en-us/windows/win32/api/lmaccess/nf-lmaccess-netlocalgroupgetmembers
bool IsUserInGroup(const std::wstring& group, const std::wstring& user) {
    LOCALGROUP_MEMBERS_INFO_3* buffer = nullptr;
    DWORD entriesread;
    DWORD totalentries;
    NET_API_STATUS status;

    status = NetLocalGroupGetMembers(NULL, group.c_str(), 3, (LPBYTE*)&buffer, MAX_PREFERRED_LENGTH, &entriesread, &totalentries, NULL);
    if (status == NERR_Success) {
        for (DWORD i = 0; i < entriesread; ++i) {
            std::wstring member(buffer[i].lgrmi3_domainandname);
            if (member.find(user) != std::wstring::npos) {
                NetApiBufferFree(buffer);
                return true;
            }
        }
        NetApiBufferFree(buffer);
    } else {
        std::wcerr << L"NetLocalGroupGetMembers ERROR: " << status << std::endl;
    }
    return false;
}

//  получение привилегий пользователя

std::string GetUserPrivilege(const std::string& username) {
    std::wstring wusername = StringToWString(username);

    if (IsUserInGroup(L"Users", wusername)) {
        return "User";
    }
    if (IsUserInGroup(L"docker-users", wusername)) {
        return "docker-users";
    }
    
    if (IsUserInGroup(L"Administrators", wusername)) {
        return "Admin";
    }

    return "";
}

// проверка привилегий из JS
// https://github.com/nodejs/node-addon-examples/blob/master/3_callbacks/napi/napi.cc

Napi::String CheckUserPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Ошибка: Ожидалась строка");
    }

    std::string username = info[0].As<Napi::String>().Utf8Value();
    std::string privilege = GetUserPrivilege(username);
    return Napi::String::New(env, privilege);
}

// и инициализация модуля
// https://github.com/nodejs/node-addon-examples/blob/master/3_callbacks/napi/napi.cc

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getUserPrivilege"), Napi::Function::New(env, CheckUserPrivilege));
    return exports;
}

NODE_API_MODULE(user_privilege, Init)
