const express = require('express');
const path = require('path');
const addon = require('./build/Release/user_privilege');

const app = express();
const port = 7777;

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.post('/check', (req, res) => {
    const username = req.body.username;
    const privilege = addon.getUserPrivilege(username);

    res.send(`
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <title>Проверка привилегий</title>
            <link rel="stylesheet" href="/css/styles.css">
        </head>
        <body>
            <div class="container">
                <h1>Результат проверки привилегий пользователя</h1>
                ${privilege
            ? `<p>Пользователь <strong>${username}</strong> имеет привилегию <strong>${privilege}</strong>.</p>`
            : `<p>Пользователя <strong>${username}</strong> нет :()</p>`}
                <a href="/" class="button">Назад</a>
            </div>
        </body>
        </html>
    `);
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
