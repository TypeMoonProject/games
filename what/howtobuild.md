## 操作环境  
Windows 11操作系统  
## 配置库文件  
### 1.在github上下载SDL2库  
下载SDL2-main :  
https://link.gitcode.com/i/d51860c2e9d2433a6d9d32df1f100a53?isLogin=1  
下载SDL2-image :  
https://link.gitcode.com/i/67e5291930fe029bb86b9da8ea3debe5?isLogin=1  
下载SDL2-mixer :  
https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.8.0  
下载SDL2-ttf :  
https://link.gitcode.com/i/d5dede3941122cfc6d52a7efea902bd0?isLogin=1  
四个库全部下载mingw.zip版本  
### 2.配置SDL2  
将库文件分别解压，放到同一个文件夹中，在项目文件夹中创建src文件夹： 

#### 1.配置SDL_main：   
打开 SDL2-2.32.4 文件夹中的 x86_64-w64-mingw32 文件夹，路径为SDL2\SDL2库解压\SDL2-2.32.4\x86_64-w64-mingw32。将include、lib两个文件夹复制到刚刚创建的项目文件夹src中，将 SDL2-2.32.4\x86_64-w64-mingw32/bin 中的 SDL2.dll 复制到项目文件夹中，和main.c放在一个层级。  
#### 2.配置SDL2-image:  
与main的配置类似。打开SDL2_image-2.8.8文件夹中的x86_64-w64-mingw32文件夹，路径为 SDL2_image-2.8.8\x86_64-w64-mingw32，打开 include 文件夹中的 SDL2 文件夹，将其中的 SDL_image 文件复制到项目的 src 文件夹中的 include 文件夹下的SDL2文件夹中，打开 SDL2_image-2.8.8\x86_64-w64-mingw32\lib 将cmake文件夹中的SDL2_image复制到 src\lib\cmake中，将 SDL2_image-2.8.8\x86_64-w64-mingw32\lib\pkgconfig 中的 SDL2_image.pc 复制到 SDL2-Cprogram\src\lib\pkgconfig，将 SDL2_image-2.8.8\x86_64-w64-mingw32\bin 中的 文件复制到项目文件中。  
#### 3.配置SDL2-mixer：  
打开 SDL2_mixer-2.8.0\x86_64-w64-mingw32 ，将 include\SDL2 中的文件复制到项目文件夹中，将 SDL2_mixer-2.8.0\x86_64-w64-mingw32\lib\cmake 中的文件夹复制到 SDL2-Cprogram\src\lib\cmake中，将 SDL2_mixer-2.8.0\x86_64-w64-mingw32\lib\pkgconfig 中的文件复制到 src\lib\pkgconfig 中，将 \SDL2_mixer-2.8.0\x86_64-w64-mingw32\lib 中的文件复制到 src\lib 中，将 SDL2_mixer-2.8.0\x86_64-w64-mingw32\bin 中的文件复制到 src 中。
#### 4.配置SDL2-ttf：  
打开 SDL2_ttf-2.24.0\x86_64-w64-mingw32 ，将 include\SDL2 中的文件复制到 src\include\SDL2 中，将 SDL2_ttf-2.24.0\x86_64-w64-mingw32\lib\cmake 中的文件复制到 src\lib\cmake 中，将 SDL2_ttf-2.24.0\x86_64-w64-mingw32\lib\pkgconfig 中的文件复制到 src\lib\pkgconfig 中，将 SDL2_ttf-2.24.0\x86_64-w64-mingw32\lib 中的文件复制到 src\lib 中，将 SDL2_ttf-2.24.0\x86_64-w64-mingw32\bin 中的文件复制到项目文件中和main.c同级
### 构建项目
#### 使用IDE：
vscode
#### 编写task.json
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc.exe 生成活动文件",
            "command": "D:\\vscode\\msys\\mingw64\\bin\\gcc.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",  //生成和调试有关的信息
                "${workspaceFolder}\\project\\*.c",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I","${workspaceFolder}\\project\\src\\include",      // 参数-I 和工程路径 指明了项目中要引用的非标准头文件的位置。 include对应工程目录下的include文件夹名字，可自行修改                   
                "-L", "${workspaceFolder}\\project\\src\\lib",  // 库文件路径
                "-lmingw32",   // MinGW 必需
                "-lSDL2main",  // SDL2 主库（顺序不可变）
                "-lSDL2",      // SDL2 核心库
                "-lSDL2_image", 
                "-lSDL2_ttf", 
                "-lSDL2_mixer"   
                //"-mwindows"    // 隐藏控制台窗口（GUI应用）     
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```