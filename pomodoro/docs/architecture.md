# Architecture

## クラス構造
- PomodoroTimer
- PomodoroSession
- PomodoroSettings
- PomodoroRenderer
- PomodoroNotification
- App

## 依存関係
App → Timer
App → Session
App → Renderer
App → Settings
App → Notification

## 責務分離
- Timer: 時間管理
- Session: 状態管理
- Renderer: UI
- Settings: 設定保存
- Notification: 通知
