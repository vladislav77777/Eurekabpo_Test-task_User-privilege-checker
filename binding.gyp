{
    "targets": [
        {
            "target_name": "user_privilege",
            "sources": ["src/user_privilege.cpp"],
            "include_dirs": [
                "C:\\Users\\Vladi\\Eurekabpo_Test-task_User-privilege-checker\\node_modules\\node-addon-api"
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"]
        }
    ]
}
