# MVP手動テストチェックリスト

## 起動

- [ ] アプリが起動する
- [ ] Timer画面が表示される
- [ ] TimerはIDLEで止まっている
- [ ] settings.jsonの値が反映されている

## Timer操作

- [ ] STARTでカウントダウンが始まる
- [ ] PAUSEで止まる
- [ ] RESUMEで再開する
- [ ] RESETで現在のセッションが最初へ戻る
- [ ] RESET後はIDLEになる

## セッション遷移

- [ ] WORK終了後、SHORT_BREAKになる
- [ ] SHORT_BREAK終了後、WORKになる
- [ ] 4回WORK後、LONG_BREAKになる
- [ ] LONG_BREAK終了後、WORKになる

## 設定変更

- [ ] Workの+ / -で値が変わる
- [ ] Short Breakの+ / -で値が変わる
- [ ] Long Breakの+ / -で値が変わる
- [ ] Long Break Intervalの+ / -で値が変わる
- [ ] 最小値・最大値を超えない

## INIT

- [ ] INITで全項目がデフォルトへ戻る
- [ ] INIT後もsettings.jsonは変わらない
- [ ] BACK後、もう一度開くと元の設定へ戻る

## SAVE

- [ ] SAVEでsettings.jsonが更新される
- [ ] アプリを再起動しても設定が残る
- [ ] SAVE後、現在のTimerが新しい設定でIDLEへ戻る

## 異常系

- [ ] settings.jsonを壊してもアプリが落ちない
- [ ] 不正な値は保存されない