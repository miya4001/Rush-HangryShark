/*****************************************************************//**
 * @file   ModePause.cpp
 * @brief  モードポーズクラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#include "ModePause.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  constexpr int SwitchX = 1500;       //!< 切り替え画像x座標
  constexpr int SwitchY = 1000;       //!< 切り替え画像y座標
  constexpr int BubbleY = 1000;       //!< 泡y座標
  constexpr int BubbleLeftX = 1150;   //!< 泡左x座標
  constexpr int BubbleRightX = 1600;  //!< 泡右x座標
  constexpr int SEVolume = 200;       //!< SE音量
} // namespace

namespace Game {
  namespace Mode {
    ModePause::ModePause(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModePause::Init() {
      return true;
    }

    void ModePause::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _pause = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Pause);
      _continue = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Continue);
      _retire = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Retire);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      // 変数初期化
      _switch = _continue;
      _bubbleX = BubbleLeftX;
    }

    void ModePause::Exit() {
      // 変数初期化
      _decision = false;
    }

    void ModePause::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto&& xJoypad = input.GetXJoypad();
      // 左スティック入力状態
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // カーソル入力
      CursorInput(leftX);
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModePause::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModePause::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _pause, true);
      DrawRotaGraph(SwitchX, SwitchY, 1.0, 0.0, _switch, true);
      DrawRotaGraph(_bubbleX, BubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModePause::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::Pause, "resource/Graphic/Pause/Pause.png"},
        {GraphicKey::Continue, "resource/Graphic/Pause/Continue.png"},
        {GraphicKey::Retire, "resource/Graphic/Pause/Retire.png"},
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModePause::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // モードポーズ削除
      _app.GetModeServer().PopBuck();
      // リタイア選択の場合
      if (_bubbleX == BubbleRightX) {
        // モードタイトル遷移
        _app.GetModeServer().TransionToMode(Title);
      }
    }

    void ModePause::CursorInput(const int leftX) {
      // 入力値なしの場合中断
      if (leftX == 0) {
        // スティック入力なし
        _isStick = false;
        return;
      }
      // 入力され続けている場合中断
      if (_isStick) {
        return;
      }
      // 正負どちらか判定
      bool isPositive = AppFrame::Math::Utility::IsPositive(leftX);
      // 入力に合わせて変数切り替え
      _switch = isPositive ? _retire : _continue;
      _bubbleX = isPositive ? BubbleRightX : BubbleLeftX;
      // スティック入力あり
      _isStick = true;
      // 泡SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble, SEVolume);
    }
  } // namespace Mode
} // namespace Game