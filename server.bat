@echo off
REM запуск Node.js сервера
start node server.js

REM ждем, чтоб сеервер запустился
timeout /t 3 /nobreak > NUL

REM открываем браузер с начальной страницей
start http://localhost:3000