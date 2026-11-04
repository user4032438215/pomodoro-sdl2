# Pomodoro

シンプルなポモドーロタイマーアプリです。  
作業と休憩を管理し、進捗を視覚的に確認できます。

## 現在の状態

このアプリはMVP段階です。  
基本的なタイマー操作と、設定の保存に対応しています。

## 主な機能

- タイマーの開始・一時停止・リセット
- 作業セッションと休憩セッションの進行
- 残り時間の表示
- 進捗バーの表示
- `settings.json`による設定の読み込み・保存
- SDL2によるウィンドウ表示

## まだ含まれない機能

- 円形プログレスサークル
- 詳細な設定画面
- 作業履歴・統計
- 通知機能
- テーマ切り替え

## 必要な環境

- Windows
- CMake 3.22以上
- C++20対応コンパイラ
- vcpkg
- SDL2
- SDL2_ttf
- nlohmann/json

## ビルド方法

リポジトリ直下で、次を実行します。

```powershell
cmake -S . -B out/build/x64-debug -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build out/build/x64-debug
```

Releaseビルド:

```powershell
cmake -S . -B out/build/x64-release -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build out/build/x64-release
```

## アプリの起動

Debugビルドの場合:

```powershell
cd out/build/x64-debug
.\pomodoro.exe
```

Releaseビルドの場合:

```powershell
cd out/build/x64-release
.\pomodoro.exe
```

`pomodoro.exe`と同じフォルダに、`settings.json`とフォントファイルが必要です。

## テストの実行

すべてのテスト:

```powershell
ctest --test-dir out/build/x64-debug --output-on-failure
```

特定のテストだけ実行:

```powershell
ctest --test-dir out/build/x64-debug -R button_tests --output-on-failure
ctest --test-dir out/build/x64-debug -R timer_tests --output-on-failure
ctest --test-dir out/build/x64-debug -R session_tests --output-on-failure
ctest --test-dir out/build/x64-debug -R settings_tests --output-on-failure
```

## 設定ファイル

`settings.json`は、実行ファイルと同じフォルダに置きます。

例:

```json
{
  "work_minutes": 25,
  "break_minutes": 5
}
```

設定ファイルが無い場合や、値が不正な場合は、アプリ側のデフォルト値で動作します。

## プロジェクト構成

```text
pomodoro/
├─ CMakeLists.txt
├─ README.md
├─ settings.json
├─ src/
│  ├─ main.cpp
│  ├─ app.cpp
│  ├─ app.hpp
│  ├─ pomodoro_renderer.cpp
│  ├─ pomodoro_renderer.hpp
│  ├─ pomodoro_timer.cpp
│  ├─ pomodoro_timer.hpp
│  ├─ pomodoro_session.cpp
│  ├─ pomodoro_session.hpp
│  ├─ settings.cpp
│  ├─ settings.hpp
│  ├─ button.cpp
│  └─ button.hpp
├─ tests/
│  ├─ timer_tests.cpp
│  ├─ session_tests.cpp
│  ├─ settings_tests.cpp
│  └─ button_tests.cpp
└─ docs/
   ├─ architecture.puml
   └─ ui.puml
```

## 設計

システム構成は `docs/architecture.puml` を参照してください。

UI構成は `docs/ui.puml` を参照してください。

## MVPの方針

現在のMVPでは、次を優先しています。

- タイマーとして確実に動くこと
- 操作方法が分かること
- 設定が保存されること

円形プログレスサークルは、MVPの必須要件から外しています。  
まずは現在のUIでフィードバックを集め、必要かどうかを判断します。