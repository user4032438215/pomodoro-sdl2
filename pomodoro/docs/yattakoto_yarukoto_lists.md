- 261011

ビルド成功
アプリ実行成功
STARTボタンが表示される
クリック操作も動く
表示位置にずれがある
→ とりあえず後回し

SDL_MOUSEBUTTONDOWNを受け取れる
event.button.xとevent.button.yでクリック位置を取得できる
SDL_Rectでボタン領域を定義できる
is_inside()でクリック判定できる
SDL_RenderFillRect()でボタン背景を描ける
SDL_RenderDrawRect()でボタン枠を描ける
TTFでSTART、PAUSE、RESUMEを表示できる
Timer状態に応じてボタン表示を切り替えられる

対象:

text
src/app.hpp
src/app.cpp
src/pomodoro_renderer.hpp
src/pomodoro_renderer.cpp
変更内容:

text
- Timer画面にSTARTボタンを追加
- Timer状態に応じてSTART、PAUSE、RESUMEを表示
- 左クリックでTimerを開始、一時停止、再開
- SDL_Rectによるクリック判定を追加

次にやること:
目標
RESETボタンをクリックしたら、
現在のセッションを最初からやり直せる

リセットは、次の意味にします。


現在のセッション種別は変えない
完了ポモドーロ数は変えない
TimerをIDLEへ戻す
自動開始しない
例

WORK実行中にRESET
→ Work
→ 25:00
→ IDLE

SHORT_BREAK実行中にRESET
→ Short Break
→ 05:00
→ IDLE
実装手順

1. リセットボタンの位置を追加する
app.hppへ追加します。

cpp
SDL_Rect reset_button_{150, 330, 100, 40};
画面イメージ:

text
[RESET] [START]
2. リセットボタンを描画する
App::render()へ追加します。

cpp
renderer_.render_button(
    reset_button_,
    "RESET"
);

3. クリック判定を追加する
App::handle_events()のマウス処理へ追加します。

cpp
if (is_inside(reset_button_, x, y)) {
    reset_current_timer();
}
4. reset_current_timer()を確認する
すでに次の関数があるはずです。

cpp
void App::reset_current_timer()
{
    const int duration_seconds =
        session_.get_duration_minutes() * 60;

    timer_.reset(duration_seconds);
}
この関数は、

現在のセッション種別の時間を取得
Timerをその時間でリセット
IDLEに戻す
という動作になります。

5. ビルドと確認

6. コミット
feat: add current session reset control