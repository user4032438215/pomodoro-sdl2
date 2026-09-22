# Specification (MVP)

## 基本タイマー仕様
- 作業 25分
- 休憩 5分
- 長休憩 15分
- 長休憩タイミング 3回ごと

## UI
- ダークテーマ
- 円形プログレスバー
- MM:SS 表示
- セッション名表示

## 操作
- 手動切り替え
- later 機能（将来追加）

## 保存
- settings.json に保存

# Settings UI Specification

## Controls

- 作業時間: 5〜60分、5分刻み
- 短い休憩時間: 1〜15分、1分刻み
- 長い休憩時間: 5〜60分、5分刻み
- 長休憩間隔: 1〜12回、1回刻み

## Buttons

- "-" button decreases by step
- "+" button increases by step
- Values do not exceed min/max
- "デフォルトに戻す" sets the draft to 25/5/15/4
- "キャンセル" discards the draft
- "保存" validates and persists the draft

## Persistence

- Save to settings.json
- Existing settings remain unchanged if validation fails
- Existing settings remain unchanged if file writing fails