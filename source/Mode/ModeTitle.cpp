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
#include "ModeExplanation.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  constexpr int SwitchX = 1500;       //!< 切り替え画像x座標
  constexpr int SwitchY = 850;        //!< 切り替え画像y座標
  constexpr int CursorStart = 1;      //!< カーソル開始
  constexpr int CursorExplain = 2;    //!< カーソル説明
  constexpr int CursorQuit = 3;       //!< カーソル終了
  constexpr int BubbleX = 1350;       //!< 泡x座標
  constexpr int BubbleStart = 750;    //!< 泡開始y座標
  constexpr int BubbleExplain = 850;  //!< 泡説明y座標
  constexpr int BubbleQuit = 950;     //!< 泡終了y座標
  constexpr int SEVolume = 200;       //!< SE音量
} // namespace

namespace Game {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeTitle::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::UnderSea);
      _title = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Title);
      _start = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Start);
      _explain = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Explain);
      _quit = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Quit);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      // 変数初期化
      _switch = _start;
      _cursor = CursorStart;
      _bubbleY = BubbleStart;
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
      DrawRotaGraph(BubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeTitle::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::Title, "resource/Graphic/Title/Title.png"},
        {GraphicKey::Start, "resource/Graphic/Title/Start.png"},
        {GraphicKey::Explain, "resource/Graphic/Title/Explain.png"},
        {GraphicKey::Quit, "resource/Graphic/Title/Quit.png"},
        {GraphicKey::Back, "resource/Graphic/Explanation/Back.png"},
        {GraphicKey::Bubble, "resource/Graphic/Cursor/Bubble.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 各種音源ハンドルの読み込み
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {SoundKey::Bubble1, "resource/Sound/SE/Bubble1.wav"},
        {SoundKey::Bubble2, "resource/Sound/SE/Bubble2.wav"},
        {SoundKey::Hungry, "resource/Sound/SE/Hungry.wav"}
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
      // 泡2SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble2, SEVolume);
      // カーソルに合わせて切り替え
      switch (_cursor) {
      // 開始選択
      case CursorStart:
        // モードゲーム遷移
        ToModeGame();
        break;
      // 説明選択
      case CursorExplain:
        // モード説明遷移
        ToModeExplanation();
        break;
      // 終了選択
      case CursorQuit:
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
      bool isPositive = AppFrame::Math::Utility::IsPositive(leftY);
      // 入力に合わせてカーソル上下
      if (isPositive) {
        // 開始より下の場合
        if (CursorStart < _cursor) {
          // カーソルを上げる
          --_cursor;
        }
      } else {
        // 終了より上の場合
        if (_cursor < CursorQuit) {
          // カーソルを下げる
          ++_cursor;
        }
      }
      // カーソルに合わせて変数切り替え
      switch (_cursor) {
      // 開始
      case CursorStart:
        _switch = _start;
        _bubbleY = BubbleStart;
        break;
      // 説明
      case CursorExplain:
        _switch = _explain;
        _bubbleY = BubbleExplain;
        break;
      // 終了
      case CursorQuit:
        _switch = _quit;
        _bubbleY = BubbleQuit;
        break;
      default:
        break;
      }
      // スティック入力あり
      _isStick = true;
      // 泡1SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble1, SEVolume);
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
      _app.GetSoundComponent().PlayBackGround(SoundKey::Hungry, SEVolume);
    }

    void ModeTitle::ToModeExplanation() {
      // キーの登録判定
      bool key = _app.GetModeServer().ContainsMode(Explanation);
      // キーが未登録の場合
      if (!key) {
        // モード説明の登録
        _app.GetModeServer().AddMode(Explanation, std::make_shared<Mode::ModeExplanation>(_appMain));
      }
      // モード説明遷移
      _app.GetModeServer().TransionToMode(Explanation);
    }
  } // namespace Mode
} // namespace Game