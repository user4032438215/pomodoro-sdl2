| 日付  | 作業                             
| ----- | -------------------------------
| 10/15 | settings.jsonの値をSettings画面へ表示
| 10/16 | 作業時間の+ボタンだけを作る 次の日へ
| 10/17 | 作業時間の+ボタンだけを作る & ④ 作業時間の-ボタンだけを作る   一応済（見た目と配置だけ。クリック処理は明日以降）
| 10/18 | Buttonクラスの設計とPUML更新 +button/-button が押されたら コンソールに押されたことを表示まで jsonの値を変更するのはあと + puml update + seeeion の値の取得方法をリファクタ
| 10/19 | Work min の +button/-button が押されたら 範囲外にいかず draft に 値が反映される。だけ 保存やアップデート は 次回以降~~
| 10/20 | その他3項目分のstepper button の実装、一項目ずつ確認してコミット
| 10/21 | ハリボテのSAVE/INIT button の 実装
| 10/22 | Settings機能の現状をDOCSへ書く
| 10/23 | 風邪で休み
| 10/24 | init 初期値の呼び出しのみ
| 10/25 | save button  apply save の 実装
| 10/26 | 手動総合テストチェックリスト作成と実行
| 10/27 | 1.リファクタの優先順位を決める 2.Buttonクラスの設計をDOCSへ書く 3.命名変更の候補をDOCSへ書く 4.PUMLを更新する 5.コミットしてpushする
| 10/28 | button class declared (button.hpp, button.cpp)
| 10/29 | app START button のみクラスに置き換える ビルド失敗
| 10/30 | app START button のみクラスに置き換える ヘッダでインクルードしたら成功した。一旦PUSH。RESET, SETTINGS replaced and checked
| 10/31 |BACK button replaced, setepper buttons replaced to button class
| 11/1  |SAVE button replaced, DEFAULTS(init) button replaced
| 11/2  |timer_session_tests.cppをtimer_tests.cppとsession_tests.cppへ分ける ビルドしてテストパス timer_session_tests.cppは削除
| 11/3  |button_tests.cpp AIに丸投げ めっちゃ苦労した CMale に
		 ```txt
		 target_compile_definitions(button_tests PRIVATE
		 SDL_MAIN_HANDLED
		 )
		 ```
		 追記 
| 11/4  |

# Settings機能の現状

## 完了
- settings.jsonの読み込み
- Timer画面への反映
- Settings画面への表示
- Work、Short Break、Long Break、Long Break Intervalの+ / -
- settings_draft_による編集
- 範囲制限
- SAVEボタンのハリボテ
- INITボタンのハリボテ

## 未完了

~~- INITでsettings_draft_をデフォルトへ戻す~~
~~- SAVEでsettings_draft_をSettings::config_へ反映する~~
~~- SAVEでsettings.jsonへ保存する~~
~~- 保存後、Timerを新しい設定でIDLEへ戻す~~
~~- Buttonクラスへの置き換え~~

---
# 円形プログレスの実装前にやっておくべきこと
~~1. ステッパーの範囲ルールを直す~~
~~2. 使わなくなったコードを削除する~~
~~3. SettingsとButtonの自動テストを追加する~~
~~4. 手動総合テストをもう一度行う~~
5. その後、円形プログレスへ進む←要件から外す

---
- 円形プログレス


