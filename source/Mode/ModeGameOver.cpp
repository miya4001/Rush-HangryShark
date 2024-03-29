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
  constexpr int SwitchX = 960;      //!< 切り替え画像x座標
  constexpr int SwitchY = 750;      //!< 切り替え画像y座標
  constexpr int BubbleX = 785;      //!< 泡x座標
  constexpr int BubbleUpY = 700;    //!< 泡上y座標
  constexpr int BubbleDownY = 800;  //!< 泡下y座標
  constexpr int SEVolume = 200;     //!< SE音量
} // namespace

namespace Game {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeGameOver::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _gameOver = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameOver);
      _retry = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Retry);
      _backTitle = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::BackTitle);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      // 変数初期化
      _switch = _retry;
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
      DrawRotaGraph(BubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
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
      // 泡2SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble2, SEVolume);
      // カーソルに合わせて切り替え
      switch (_bubbleY) {
      // リトライ選択
      case BubbleUpY:
        // モードゲーム遷移
        _app.GetModeServer().TransionToMode(Game);
        // 空腹SEの再生
        _app.GetSoundComponent().PlayBackGround(SoundKey::Hungry, SEVolume);
        break;
      // タイトルバック選択
      case BubbleDownY:
        // モードタイトル遷移
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
      bool isPositive = AppFrame::Math::Utility::IsPositive(leftY);
      // 入力に合わせて変数切り替え
      _switch = isPositive ? _retry : _backTitle;
      _bubbleY = isPositive ? BubbleUpY : BubbleDownY;
      // スティック入力あり
      _isStick = true;
      // 泡1SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble1, SEVolume);
    }
  } // namespae Mode
} // namespace Game