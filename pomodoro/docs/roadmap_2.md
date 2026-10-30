| 日付  | 作業                             
| ----- | -------------------------------
| 10/15 | ~~settings.jsonの値をSettings画面へ表示~~ 
| 10/16 | ~~作業時間の+ボタンだけを作る~~  次の日へ
| 10/17 | ~~作業時間の+ボタンだけを作る & ④ 作業時間の-ボタンだけを作る   一応済（見た目と配置だけ。クリック処理は明日以降）~~
| 10/18 | ~~Buttonクラスの設計とPUML更新 +button/-button が押されたら コンソールに押されたことを表示まで jsonの値を変更するのはあと + puml update + seeeion の値の取得方法をリファクタ~~
| 10/19 | ~~Work min の +button/-button が押されたら 範囲外にいかず draft に 値が反映される。だけ 保存やアップデート は 次回以降~~
| 10/20 | ~~その他3項目分のstepper button の実装、一項目ずつ確認してコミット~~
| 10/21 | ~~ハリボテのSAVE/INIT button の 実装~~
| 10/22 | Settings機能の現状をDOCSへ書く
| 10/23 | 風邪で休み
| 10/24 | init 初期値の呼び出しのみ
| 10/25 | save button  apply save の 実装
| 10/26 | 手動総合テストチェックリスト作成と実行
| 10/27 | 1.リファクタの優先順位を決める 2.Buttonクラスの設計をDOCSへ書く 3.命名変更の候補をDOCSへ書く 4.PUMLを更新する 5.コミットしてpushする
| 10/28 | button class declared (button.hpp, button.cpp)
| 10/29 | app START button のみクラスに置き換える ビルド失敗
| 10/30 | 
| 10/31 |
| 11/1  |
| 11/2  |
| 11/3  |



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

- INITでsettings_draft_をデフォルトへ戻す
- SAVEでsettings_draft_をSettings::config_へ反映する
- SAVEでsettings.jsonへ保存する
- 保存後、Timerを新しい設定でIDLEへ戻す
- Buttonクラスへの置き換え
- 円形プログレス


INIT の命名 どうする問題

SAVE / INITを3〜4日に分解する
Day 1:
    INITを動かす
    settings_draft_をデフォルトへ戻す
    表示が変わることを確認する
    settings.jsonは保存しない

Day 2:
    Settings::apply()を追加する
    draftの検証を行う
    検証成功ならconfig_へ反映する
    まだ保存しない

Day 3:
    Settings::save()を追加する
    SAVEでconfig_をsettings.jsonへ保存する
    再起動して値が残ることを確認する

Day 4:
    保存後、Timerを新しい設定でIDLEへ戻す
    テストを追加する

