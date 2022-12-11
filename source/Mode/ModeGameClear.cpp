/*****************************************************************//**
 * @file   ModeGameClear.cpp
 * @brief  モードゲームクリアクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "ModeGameClear.h"
#include "../Application/ApplicationMain.h"
#include "../Result/ResultComponent.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  constexpr int TenPlace = 10;      //!< 十の位
  constexpr int BackX = 960;        //!< バックx座標
  constexpr int BackY = 900;        //!< バックy座標
  constexpr int BubbleX = 860;      //!< 泡x座標
  constexpr int BubbleY = 900;      //!< 泡y座標
  constexpr int ResultX = 960;      //!< リザルトx座標
  constexpr int NumberTenX = 1000;  //!< 数(十の位)x座標
  constexpr int NumberOneX = 1080;  //!< 数(一の位)x座標
  constexpr int ShrimpY = 550;      //!< エビy座標
  constexpr int TunaY = 650;        //!< マグロy座標
  constexpr int JerryfishY = 750;   //!< クラゲy座標
  constexpr int SEVolume = 200;     //!< SE音量
} // namespace

namespace Game {
  namespace Mode {
    ModeGameClear::ModeGameClear(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeGameClear::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _gameClear = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameClear);
      _shrimp = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Shrimp);
      _tuna = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Tuna);
      _jerryfish = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Jerryfish);
      _back = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Back);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      _number = _app.GetGraphicLoadServer().GetDivGraphicHandles(GraphicKey::Number);
      // 敵数の設定
      SetEnemyNumbers();
    }

    void ModeGameClear::Exit() {
      // 変数初期化
      _decision = false;
      // ゲームクリアフラグ初期化
      _appMain.SetGameClear(false);
    }

    void ModeGameClear::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto&& xJoypad = input.GetXJoypad();
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModeGameClear::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeGameClear::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _gameClear, true);
      DrawRotaGraph(BackX, BackY, 1.0, 0.0, _back, true);
      DrawRotaGraph(BubbleX, BubbleY, 1.0, 0.0, _bubble, true);
      // リザルト数の描画
      DrawRotaGraph(ResultX, ShrimpY, 1.0, 0.0, _shrimp, true);
      DrawRotaGraph(ResultX, TunaY, 1.0, 0.0, _tuna, true);
      DrawRotaGraph(ResultX, JerryfishY, 1.0, 0.0, _jerryfish, true);
      DrawRotaGraph(NumberTenX, ShrimpY, 1.0, 0.0, _number.at(_shrimpTen), true);
      DrawRotaGraph(NumberTenX, TunaY, 1.0, 0.0, _number.at(_tunaTen), true);
      DrawRotaGraph(NumberTenX, JerryfishY, 1.0, 0.0, _number.at(_jerryfishTen), true);
      DrawRotaGraph(NumberOneX, ShrimpY, 1.0, 0.0, _number.at(_shrimpOne), true);
      DrawRotaGraph(NumberOneX, TunaY, 1.0, 0.0, _number.at(_tunaOne), true);
      DrawRotaGraph(NumberOneX, JerryfishY, 1.0, 0.0, _number.at(_jerryfishOne), true);
    }

    void ModeGameClear::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::GameClear, "resource/Graphic/GameClear/GameClear.png"},
        {GraphicKey::Shrimp, "resource/Graphic/GameClear/Shrimp.png"},
        {GraphicKey::Tuna, "resource/Graphic/GameClear/Tuna.png"},
        {GraphicKey::Jerryfish, "resource/Graphic/GameClear/Jerryfish.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGameClear::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // 泡2SEの再生
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble2, SEVolume);
      // モードタイトル遷移
      _app.GetModeServer().TransionToMode(Title);
    }

    void ModeGameClear::SetEnemyNumbers() {
      // エビ数の取得
      int shrimp = _appMain.GetResultComponent().GetShrimp();
      // エビ数の設定
      _shrimpTen = shrimp / TenPlace;
      _shrimpOne = shrimp % TenPlace;
      // マグロ数の取得
      int tuna = _appMain.GetResultComponent().GetTuna();
      // マグロ数の設定
      _tunaTen = tuna / TenPlace;
      _tunaOne = tuna % TenPlace;
      // クラゲ数の取得
      int jerryfish = _appMain.GetResultComponent().GetJerryfish();
      // クラゲ数の設定
      _jerryfishTen = jerryfish / TenPlace;
      _jerryfishOne = jerryfish % TenPlace;
    }
  } // namespae Mode
} // namespace Game