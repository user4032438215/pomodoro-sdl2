# Development Environment Setup

## OS
- Windows 10/11

## 必要なツール
- Visual Studio 2026
- CMake
- vcpkg
- Git

## SDL2 の導入

> vcpkg install sdl2 sdl2-image sdl2-mixer sdl2-ttf
> vcpkg integrate install

## CMakeLists.txt の設定
- find_package(SDL2 CONFIG REQUIRED)
- find_package(SDL2_ttf CONFIG REQUIRED)
- target_link_libraries(... SDL2::SDL2 SDL2_ttf::SDL2_ttf)

## プロジェクト構造
src/
assets/
config/
docs/

## ビルド手順
- CMake configure
- CMake build

## トラブルシュート
- .vs フォルダは Git に入れない
- out/build が壊れたら削除して再構成
