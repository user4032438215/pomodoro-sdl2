Phase 1: 現在のMVPを保護
現在すでに動作している状態をGitへ保存します。


feat: implement initial pomodoro MVP
このコミットを基準にすれば、以降の変更で問題が起きても戻れます。

Phase 2: Timer画面をWeb版へ近づける
順番は次です。


1. 起動直後をIDLEにする
2. マウスの開始・一時停止・再開ボタン
3. リセットボタン
4. MM:SS表示
5. 完了ポモドーロ数
6. 一時停止状態表示
7. 円形プログレス
1機能ごとにビルド・実行・コミットします。

Phase 3: 設定画面
設定画面は一度に完成させず、段階的に作ります。


1. 設定画面へ移動するボタン
2. 設定画面のレイアウト
3. + / −ボタン
4. 編集用draft
5. デフォルトに戻す
6. キャンセル
7. 保存とJSON検証
8. 設定反映


実装の段階では、次の順番がおすすめです。

最初のボタン実装
まずはApp内でSDL_Rectを直接持っても構いません。

cpp
SDL_Rect start_button_;
SDL_Rect pause_button_;
SDL_Rect reset_button_;
クリック判定が増えてきたら、

cpp
struct Button
{
    SDL_Rect bounds;
    std::string label;
};
へ切り出します。

さらに、ボタンの描画・hover・enabled状態が複雑になった時点で、Buttonクラスにします。

つまり、PUML上では拡張予定として表現していますが、実装は段階的に行ってください。

1作業単位の進め方
作業単位1: ドキュメント保存
作成ファイル:

text
docs/specification.md
docs/behavior.md
docs/ui-specification.md
docs/settings-format.md
docs/architecture.md
docs/testing.md
docs/roadmap.md
docs/diagrams/class-diagram.puml
確認:

text
内容を読み返す
コミット:

text
docs: define MVP requirements and architecture
作業単位2: 起動直後をIDLEにする
変更:

cpp
App::run()
から、

cpp
timer_.start();
を削除します。

確認:

text
起動直後に25:00
開始ボタンなしなら時間が減らない
コミット:

text
fix: keep timer idle on startup
作業単位3: Timer画面の開始ボタン
変更:

text
SDL_MOUSEBUTTONDOWN
開始ボタンの矩形判定
確認:

text
開始ボタンでIDLE→RUNNING
作業単位4: 一時停止・再開
確認:

text
RUNNING→PAUSED
PAUSED→RUNNING
作業単位5: リセット
仕様:

text
現在のSessionTypeを維持
完了数を維持
TimerをIDLEへ戻す
自動開始しない
作業単位6: MM:SS
Rendererだけを変更します。

text
1500 sec → 25:00
作業単位7: 完了数と状態表示
text
現在 0 ポモドーロ完了
PAUSED
作業単位8: 円形プログレス
Timerのget_progress()は変更せず、Renderer側で描画します。

SDL2には円弧専用APIがないため、円周上の点を計算し、SDL_RenderDrawLines()で線分を結ぶ方式が現実的です。

作業単位9: 設定画面の表示
まずは操作なしで、設定画面を表示するだけにします。

text
作業時間 25分
短い休憩 5分
長い休憩 15分
長休憩間隔 4回
作業単位10: ステッパー
設定値の仕様:

text
作業時間: 5〜60、5刻み
短い休憩: 1〜15、1刻み
長い休憩: 5〜60、5刻み
長休憩間隔: 1〜12、1刻み
作業単位11: 設定保存
text
デフォルトに戻す
キャンセル
保存
の順に実装します。

設定画面の仕様
今回の合意に基づく設定画面は次です。

text
設定

作業時間       [ − ] 25 分 [ ＋ ]
短い休憩       [ − ]  5 分 [ ＋ ]
長い休憩       [ − ] 15 分 [ ＋ ]
長休憩間隔     [ − ]  4 回 [ ＋ ]

              [デフォルトに戻す]

              [キャンセル] [保存]
値の刻みは、

text
作業時間: 5分
短い休憩: 1分
長い休憩: 5分
間隔: 1回
です。

設定画面で編集するのは、

cpp
settings_draft_
です。

保存するまでは、

cpp
settings_.current()
を変更しません。

次に行うこと
次の作業は、コード変更ではなく、まずPUMLと仕様ドキュメントを保存することです。

その後、最初の実装単位として、

text
起動直後をIDLEにする
を実施します。

これは変更が小さく、確認も簡単です。

text
起動する
→ 25:00が表示される
→ 数秒待っても25:00のまま
次に開始ボタンを追加します。

この順番なら、1回の作業で扱う内容を小さく保ちながら、Web版の完成形へ少しずつ近づけられます。

まず完成条件を固定する
現在のMVP完成条件は、次のユーザーフローで定義できます。

text
アプリを起動する
↓
WORK・25:00・0%・完了数0が表示される
↓
開始ボタンをクリックする
↓
タイマーが進む
↓
一時停止・再開できる
↓
リセットすると現在セッションの最初に戻る
↓
時間切れで次のセッションが表示される
↓
4回目のWORK終了後にLONG_BREAKになる
↓
設定画面で値をボタン操作だけで変更できる
↓
設定を保存できる
↓
再起動後も設定が維持される
この一連の流れをユーザーが問題なく完了できれば、MVP完成と判断できます。

P0: 完成に必須
text
- 起動直後をIDLEにする
- Timer画面の開始ボタン
- 一時停止・再開ボタン
- リセットボタン
- MM:SS表示
- セッション名表示
- 経過プログレス0〜100%
- 円形プログレス
- WORK/SHORT_BREAK/LONG_BREAKの自動遷移
- 4回ごとの長休憩
- 設定画面
- + / −ステッパー
- デフォルトに戻す
- キャンセル
- settings.json保存
- 再起動後の設定読み込み

P1: できればMVPに含める
text
- 完了ポモドーロ数表示
- 一時停止中の状態表示
- ボタンのhover表示
- 設定保存失敗時のエラー表示
- 設定値の範囲外防止

P2: MVP後
text
- キーボードショートカット
- セッションスキップ
- Windows通知
- 通知音
- タスク履歴
- 統計
- フォント設定
- テーマ設定