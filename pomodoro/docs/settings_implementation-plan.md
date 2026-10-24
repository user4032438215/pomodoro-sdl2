# Settings保存機能 実装計画

## 目的

Settings画面で変更した値を、
SAVEボタンで保存できるようにする。

また、INITボタンで編集中の値を
デフォルトへ戻せるようにする。

## 現状

- settings.jsonは起動時に読み込める
- Settings::config_が現在の設定を持つ
- App::settings_draft_が編集中の設定を持つ
- 4項目の+ / -でsettings_draft_を変更できる
- SAVEとINITはクリックログを出すだけ

## ゴール

- INITでsettings_draft_をデフォルトへ戻す
- SAVEでsettings_draft_を検証する
- 検証成功ならconfig_へ反映する
- config_をsettings.jsonへ保存する
- 保存後、Timerを新しい設定でIDLEへ戻す

# day1 INIT を動かす
- src/app.cpp
- 変更内容
- App::handle_events()のINITボタン処理を変更します。