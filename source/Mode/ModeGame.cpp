/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  モードゲームクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Effect/EffectServer.h"
#include "../UI/UIHungryGauge.h"
#include "../UI/UITimer.h"
#include "ModeGameOver.h"
#include "ModeGameClear.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  namespace AppMath = AppFrame::Math;
  const AppMath::Vector4 CameraPosition{ 0.0f, 100.0f, 250.0f };  //!< 初期カメラ位置
  const AppMath::Vector4 CameraTarget{ 0.0f, 50.0f, 0.0f };       //!< 初期カメラ注視点
  const AppMath::Vector4 DirLight{ 0.0f, -1.0f, 0.0f };           //!< ディレクショナルライト
} // namespace

namespace Game {
  namespace Mode {
    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGame::Init() {
      // 生成コンポーネントの生成
      _spawn = std::make_unique<Spawn::SpawnComponent>(_appMain);
      // UIサーバの生成
      _uiServer = std::make_unique<UI::UIServer>();
      return true;
    }

    void ModeGame::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // ディレクショナルライトの変更
      ChangeLightTypeDir(AppMath::UtilityDX::ToVECTOR(DirLight));
      // ライトを青色に変更
      SetLightDifColor(GetColorF(0.5f, 0.5f, 1.0f, 0.0f));
      // カメラ初期化
      _appMain.GetCamera().FixedPoint(CameraPosition, CameraTarget);
      // 生成情報の設定
      _spawn->SetSpawn();
      // UIの設定
      SetUI();
    }

    void ModeGame::Exit() {
      // 生成したオブジェクトを削除
      _appMain.GetObjectServer().Release();
      // 生成コンポーネントの解放
      _spawn->Release();
      // 生成したエフェクトを削除
      _appMain.GetEffectServer().Release();
      // UIサーバの解放
      _uiServer->Release();
      // 複製したモデルの解放
      _appMain.GetModelLoadServer().DeleteDuplicateModels();
    }

    void ModeGame::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto&& xJoypad = input.GetXJoypad();
      // STARTボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_START, AppFrame::Input::InputTrigger)) {
        // アプリケーションの終了要請
        _app.RequestTerminate();
      }
    }

    void ModeGame::Process() {
      // 入力
      Input(_app.GetInputManager());
      // オブジェクトサーバの更新
      _appMain.GetObjectServer().Process();
      // 生成コンポーネントの更新
      _spawn->Process();
      // エフェクトサーバの更新
      _appMain.GetEffectServer().Process();
      // UIサーバの更新
      _uiServer->Process();
      // モード切り替え
      ChangeMode();
    }

    void ModeGame::Draw() const {
      // オブジェクトサーバの描画
      _appMain.GetObjectServer().Draw();
      // エフェクトサーバの描画
      _appMain.GetEffectServer().Draw();
      // UIサーバの描画
      _uiServer->Draw();
    }

    void ModeGame::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::HungryGauge, "resource/Graphic/UI/HungryGauge.png"},
        {GraphicKey::HungryGaugeBar, "resource/Graphic/UI/HungryGaugeBar.png"},
        {GraphicKey::TimerColon, "resource/Graphic/UI/Colon.png"}
      };
      // 各種分割画像ハンドルの読み込み
      const GraphicLoadServer::LoadDivGraphicMap loadDivGraphicMap{
        {GraphicKey::Number, {"resource/Graphic/UI/Number_sheet.png", 10, 10, 1, 70, 106}}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      _app.GetGraphicLoadServer().LoadDivGraphics(loadDivGraphicMap);
      // 各種モデルハンドルの読み込み
      using ModelLoadServer = AppFrame::Model::ModelLoadServer;
      const ModelLoadServer::LoadModelMap loadModelMap {
        {ModelKey::SeaSphere, "resource/Model/Sea/skysphere.mv1"},
        {ModelKey::Shark, "resource/Model/Shark/megalodon.mv1"},
        {ModelKey::Shrimp, "resource/Model/Shrimp/Shrimp.mv1"},
        {ModelKey::Tuna, "resource/Model/Tuna/Tuna.mv1"},
        {ModelKey::Jerryfish, "resource/Model/Jerryfish/jerryfish.mv1"}
      };
      // モデル読み込みサーバに一括読み込み
      _app.GetModelLoadServer().LoadModels(loadModelMap);
      // 各種エフェクトハンドルの読み込み
      using EffectLoadServer = AppFrame::Effect::EffectLoadServer;
      const EffectLoadServer::LoadEffectMap loadEffectMap {
        {EffectKey::Blood, "resource/Effect/Blood/Blood.efkefc", EffectMagni::Blood},
        {EffectKey::Discover, "resource/Effect/Discover/Discover.efkefc", EffectMagni::Discover},
        {EffectKey::Paralysis, "resource/Effect/Paralysis/Paralysis.efkefc", EffectMagni::Paralysis}
      };
      // エフェクト読み込みサーバに一括読み込み
      _app.GetEffectLoadServer().LoadEffects(loadEffectMap);
      // 各種音源ハンドルの読み込み
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {SoundKey::Bite, "resource/Sound/SE/Bite.wav"},
        {SoundKey::Eat, "resource/Sound/SE/Eat.wav"},
        {SoundKey::Paralysis, "resource/Sound/SE/Paralysis.wav"},
        {SoundKey::Drawn, "resource/Sound/SE/Drawn.wav"},
        {SoundKey::Whistle, "resource/Sound/SE/Whistle.wav"}
      };
      // 音源読み込みサーバに一括読み込み
      _app.GetSoundLoadServer().LoadSounds(loadSoundMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGame::ChangeMode() {
      // ゲームオーバーの場合
      if (_appMain.GetGameOver()) {
        // モードゲームオーバー遷移
        ToModeGameOver();
        return;
      }
      // ゲームクリアの場合
      if (_appMain.GetGameClear()) {
        // モードゲームクリア遷移
        ToModeGameClear();
        return;
      }
    }

    void ModeGame::SetUI() {
      // 空腹ゲージの生成
      auto hungryGauge = std::make_shared<UI::UIHungryGauge>(_appMain);
      _uiServer->RegisterUI(hungryGauge);
      // タイマーの生成
      auto timer = std::make_shared<UI::UITimer>(_appMain);
      _uiServer->RegisterUI(timer);
    }

    void ModeGame::ToModeGameOver() {
      // キーの登録判定
      bool key = _app.GetModeServer().ContainsMode(GameOver);
      // キーが未登録の場合
      if (!key) {
        // モードゲームオーバーの登録
        _app.GetModeServer().AddMode(GameOver, std::make_shared<Mode::ModeGameOver>(_appMain));
      }
      // モードゲームオーバー遷移
      _app.GetModeServer().TransionToMode(GameOver);
    }

    void ModeGame::ToModeGameClear() {
      // キーの登録判定
      bool key = _app.GetModeServer().ContainsMode(GameClear);
      // キーが未登録の場合
      if (!key) {
        // モードゲームクリアの登録
        _app.GetModeServer().AddMode(GameClear, std::make_shared<Mode::ModeGameClear>(_appMain));
      }
      // モードゲームクリア遷移
      _app.GetModeServer().TransionToMode(GameClear);
    }
  } // namespace Mode
} // namespace Game