# リファクタ計画

## 目的

MVP完成前に、
重複を減らし、
責務をはっきりさせ、
今後の拡張をしやすくする。

## Refactoring Priorities
1. button class  	          -ボタン処理の重複が多く、効果が大きい
2. 設定値の範囲・刻みの整理   -設定値の範囲・刻みの整理
3. 命名の改善                 -config_、INITなどが分かりにくい
4. Rendererのテキスト描画     -文字位置計算が重複している
5. App.cppの分割              -500行超えているが、今はまだ保留
# 4と5は、MVP完成後でも可

---
- button class
```C++
//button class
class Button
{
public:
    Button(
        SDL_Rect bounds,
        std::string label
    );

    bool contains(
        int x,
        int y
    ) const;

    void render(
        PomodoroRenderer& renderer
    ) const;

    const std::string& label() const;

    void set_label(const std::string& label);

private:
    SDL_Rect bounds_{};
    std::string label_;
};
```
移行手順
1. button.hppとbutton.cppを追加する
2. Timer画面のSTARTボタンだけButtonへ置き換える
3. ビルドして動作確認する
4. RESET、SETTINGSも置き換える
5. Settings画面の+と-も置き換える
6. SAVE、DEFAULTS、BACKも置き換える
7. PUMLを更新する

---
設定値の範囲をまとめる
現状の問題 数値がapp.cppに散らばっています。

```C++
//PomodoroLisits
struct PomodoroLimits
{
    static constexpr int work_min{5};
    static constexpr int work_max{60};
    static constexpr int work_step{5};

    static constexpr int short_break_min{1};
    static constexpr int short_break_max{15};
    static constexpr int short_break_step{1};

    static constexpr int long_break_min{5};
    static constexpr int long_break_max{60};
    static constexpr int long_break_step{5};

    static constexpr int interval_min{1};
    static constexpr int interval_max{12};
    static constexpr int interval_step{1};
};
```
---
命名の改善
| 現在            | 気になる点                     | 候補                 
| --------------- | ------------------------------ | -------------------- 
| config_         | 何の設定か少し抽象的           | current_config_      
| INIT            | 初期化？リセット？分かりにくい | DEFAULTS             
| settings_draft_ | 悪くないが長い                 | そのままでOK           
| button_label()  | Timer画面専用っぽい            | timer_button_label() 

---
Rendererのテキスト描画
# 現状の問題
render_button()の中で、文字位置を固定オフセットにしています。
```C++
render_text(
    label,
    bounds.x + 20,
    bounds.y + 10
);
```
# 改善案
文字の幅を取得して、ボタンの中央へ置きます。
```C++
void PomodoroRenderer::render_button(
    const SDL_Rect& bounds,
    const std::string& label
)
{
    // 背景と枠を描く

    int text_width = 0;
    int text_height = 0;

    // TTF_SizeUTF8で文字サイズを取得する
    TTF_SizeUTF8(
        font_,
        label.c_str(),
        &text_width,
        &text_height
    );

    const int text_x =
        bounds.x +
        (bounds.w - text_width) / 2;

    const int text_y =
        bounds.y +
        (bounds.h - text_height) / 2;

    render_text(
        label,
        text_x,
        text_y
    );
}
```

---
App.cppの分割
今すぐじゃなくてもよい
→まだButtonクラスやSettings保存の最終形が固まっていない
  分割すると、変更箇所が増える
  MVP完成が遅れる

今後の分割タイミング
- Buttonクラスが完成している
- Settings保存が完成している
- 円形プログレスも入っている
- App.cppが800行以上になる
- 同じ種類の処理が明確に固まっている

その後

app.cpp
├─ timer_screen.cpp
├─ settings_screen.cpp
└─ input_handler.cpp

のように分割