# Проверка привилегий пользователя

Этот проект предоставляет возможность проверки привилегий пользователей в системе Windows. использует C++ для определения привилегий и Node.js с N-API для создания интерфейса для веб-приложения.

## Содержание

- [Пример](#описание)
- [Установка](#установка)
- [Использование](#использование)
- [Технические детали](#технические-детали)
- [Ссылки](#ссылки)

## Пример <a name="описание"></a>

![image](https://github.com/user-attachments/assets/c571e547-fb80-465e-bcbd-562a5b5c317a)
![image](https://github.com/user-attachments/assets/04ae171b-ea47-42ee-9e19-76c477a86065)
![image](https://github.com/user-attachments/assets/0e003f2b-2b02-492d-8f8b-ee4e0f488c06)


## Установка <a name="установка"></a>

1. **Клонируйте репозиторий:**
    ```sh
    git clone ...
    ```

2. **Установите зависимости:**
    Убедитесь, что у вас установлен [Node.js](https://nodejs.org/) и [npm](https://www.npmjs.com/). Затем:
    ```sh
    npm install
    ```

3. **Соберите проект:**
    Убедитесь, что у вас установлен [node-gyp](https://github.com/nodejs/node-gyp). Затем:
    ```sh
    npm run build
    ```

## Использование <a name="использование"></a>

1. **Запустите сервер:**
    ```sh
    npm start
    ```

2. **Откройте веб-браузер и перейдите по адресу:**
    ```
    http://localhost:7777
    ```
...

## Технические детали <a name="технические-детали"></a>

- **C++** - Используется для определения привилегий пользователя в системе Windows через `NetLocalGroupGetMembers`.
- **Node.js** - Создает сервер и предоставляет API для взаимодействия с C++ кодом.
- **N-API** - Используется для создания интерфейса между Node.js и C++.

## Ссылки <a name="ссылки"></a>

- [Node.js Documentation](https://nodejs.org/en/docs/)
- [N-API Documentation](https://nodejs.org/api/n-api.html)
- [GitHub Documentation](https://docs.github.com/en/github)
- [Microsoft Documentation for `NetLocalGroupGetMembers`](https://learn.microsoft.com/en-us/windows/win32/api/lmaccess/nf-lmaccess-netlocalgroupgetmembers)

---

© 2024 Григорьев Владислав
