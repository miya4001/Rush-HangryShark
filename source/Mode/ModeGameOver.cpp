/*****************************************************************//**
 * @file   ModeGameOver.cpp
 * @brief  モードゲームオーバークラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "ModeGameOver.h"
#include "../Application/ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  constexpr int SwitchX = 960;       //!< 切り替え画像x座標
  constexpr int SwitchY = 750;       //!< 切り替え画像y座標
  constexpr int BubbleUpX = 785;     //!< 泡上x座標
  constexpr int BubbleDownX = 860;   //!< 泡下x座標
  constexpr int BubbleUpY = 700;     //!< 泡上y座標
  constexpr int BubbleDownY = 800;   //!< 泡下y座標
  constexpr int SEVolume = 200;      //!< SE音量
}

namespace Game {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGameOver::Init() {
      return true;
    }

    void ModeGameOver::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _gameOver = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameOver);
      _retry = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Retry);
      _backTitle = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::BackTitle);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      _switch = _retry;
      // 変数初期化
      _bubbleX = BubbleUpX;
      _bubbleY = BubbleUpY;
    }

    void ModeGameOver::Exit() {
      // 変数初期化
      _decision = false;
      // ゲームオーバーフラグ初期化
      _appMain.SetGameOver(false);
    }

    void ModeGameOver::Input(AppFrame::Input::InputManager& input) {
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

    void ModeGameOver::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeGameOver::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _gameOver, true);
      DrawRotaGraph(SwitchX, SwitchY, 1.0, 0.0, _switch, true);
      DrawRotaGraph(_bubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeGameOver::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::GameOver, "resource/Graphic/GameOver/GameOver.png"},
        {GraphicKey::Retry, "resource/Graphic/GameOver/Retry.png"},
        {GraphicKey::BackTitle, "resource/Graphic/GameOver/BackTitle.png"},
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGameOver::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // カーソルに合わせて切り替え
      switch (_bubbleY) {
        // 選択上
      case BubbleUpY:
        // モードゲーム遷移
        _app.GetModeServer().TransionToMode(Game);
        // 空腹SEの再生
        _app.GetSoundComponent().PlayBackGround(SoundKey::Hungry, SEVolume);
        break;
        // 選択下
      case BubbleDownY:
        // モードゲーム遷移
        _app.GetModeServer().TransionToMode(Title);
        break;
      default:
        break;
      }
    }

    void ModeGameOver::CursorInput(const int leftY) {
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
      _switch = isPositive ? _retry : _backTitle;
      _bubbleX = isPositive ? BubbleUpX : BubbleDownX;
      _bubbleY = isPositive ? BubbleUpY : BubbleDownY;
      // スティック入力あり
      _isStick = true;
      // 泡SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble, SEVolume);
    }
  } // namespae Mode
} // namespace Game