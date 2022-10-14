/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  モードタイトルクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/ApplicationMain.h"
#include "ModeGame.h"

namespace {
  // 画像ハンドルキー
  constexpr auto UnderSea = "underSea";  //!< 海中
  constexpr auto Title = "title";        //!< タイトル
  constexpr auto Start = "start";        //!< 開始
  constexpr auto Quit = "quit";          //!< 終了
  constexpr auto Cursor = "cursor";      //!< カーソル
  // 音源ハンドルキー
  constexpr auto Bubble = "bubble";  //!< 泡
  constexpr auto Hungry = "hungry";  //!< 空腹
  // 各種定数
  constexpr int SwitchX = 1500;      //!< 切り替え画像x座標
  constexpr int SwitchY = 850;       //!< 切り替え画像y座標
  constexpr int BubbleUpX = 1350;    //!< 泡上x座標
  constexpr int BubbleDownX = 1400;  //!< 泡下x座標
  constexpr int BubbleUpY = 800;     //!< 泡上y座標
  constexpr int BubbleDownY = 900;   //!< 泡下y座標
  constexpr int SEVolume = 200;      //!< SE音量
}

namespace Game {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeTitle::Init() {
      return true;
    }

    void ModeTitle::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(UnderSea);
      _title = _app.GetGraphicLoadServer().GetGraphicHandle(Title);
      _start = _app.GetGraphicLoadServer().GetGraphicHandle(Start);
      _quit = _app.GetGraphicLoadServer().GetGraphicHandle(Quit);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(Cursor);
      _switch = _start;
      // 変数初期化
      _bubbleX = BubbleUpX;
      _bubbleY = BubbleUpY;
    }

    void ModeTitle::Exit() {
      // 変数初期化
      _decision = false;
    }

    void ModeTitle::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto&& xJoypad = input.GetXJoypad();
      // 左スティック入力状態
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // カーソル入力
      CursorInput(leftY);
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModeTitle::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeTitle::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _sea, true);
      DrawGraph(0, 0, _title, true);
      DrawRotaGraph(SwitchX, SwitchY, 1.0, 0.0, _switch, true);
      DrawRotaGraph(_bubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeTitle::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {Title, "resource/Graphic/Title/Title.png"},
        {Start, "resource/Graphic/Title/Start.png"},
        {Quit, "resource/Graphic/Title/Quit.png"},
        {Cursor, "resource/Graphic/Cursor/Bubble.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 各種音源ハンドルの読み込み
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {Bubble, "resource/Sound/SE/Bubble.wav"},
        {Hungry, "resource/Sound/SE/Hungry.wav"}
      };
      // 音源読み込みサーバに一括読み込み
      _app.GetSoundLoadServer().LoadSounds(loadSoundMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeTitle::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // カーソルに合わせて切り替え
      switch (_bubbleY) {
      // 選択上
      case BubbleUpY:
        // モードゲーム遷移
        ToModeGame();
        break;
      // 選択下
      case BubbleDownY:
        // アプリケーションの終了要請
        _app.RequestTerminate();
        break;
      default:
        break;
      }
    }

    void ModeTitle::CursorInput(const int leftY) {
      // 入力値なしの場合中断
      if (leftY == 0) {
        // スティック入力なし
        _isStick = false;
        return;
      }
      // 入力され続けている場合中断
      if (_isStick) {
        return;
      }
      // 正負どちらか判定
      bool isPositive = 0 <= leftY;
      // 入力に合わせて変数切り替え
      _switch = isPositive ? _start : _quit;
      _bubbleX = isPositive ? BubbleUpX : BubbleDownX;
      _bubbleY = isPositive ? BubbleUpY : BubbleDownY;
      // スティック入力あり
      _isStick = true;
      // 泡SEの再生
      _app.GetSoundComponent().PlayBackGround(Bubble, SEVolume);
    }

    void ModeTitle::ToModeGame() {
      // キーの登録判定
      bool key = _app.GetModeServer().ContainsMode(Game);
      // キーが未登録の場合
      if (!key) {
        // モードゲームの登録
        _app.GetModeServer().AddMode(Game, std::make_shared<Mode::ModeGame>(_appMain));
      }
      // モードゲーム遷移
      _app.GetModeServer().TransionToMode(Game);
      // 空腹SEの再生
      _app.GetSoundComponent().PlayBackGround(Hungry, SEVolume);
    }
  } // namespace Mode
} // namespace Game