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
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"
#include "ModeGameOver.h"

namespace {
  namespace AppMath = AppFrame::Math;
  const AppMath::Vector4 CameraPosition{ 0.0f, 100.0f, 250.0f };  //!< 初期カメラ位置
  const AppMath::Vector4 CameraTarget{ 0.0f, 50.0f, 0.0f };       //!< 初期カメラ注視点
}

namespace Game {
  namespace Mode {
    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGame::Init() {
      // 生成コンポーネントの生成
      _spawn = std::make_unique<Spawn::SpawnComponent>(_appMain);
      return true;
    }

    void ModeGame::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // カメラ初期化
      _appMain.GetCamera().FixedPoint(CameraPosition, CameraTarget);
      // 生成情報の設定
      SetSpawn();
    }

    void ModeGame::Exit() {
      // 生成したオブジェクトを削除
      _appMain.GetObjectServer().Release();
      // 複製したモデルの解放
      _appMain.GetModelLoadServer().DeleteDuplicateModels();
      // 生成コンポーネントの解放
      _spawn->Release();
    }

    void ModeGame::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto xJoypad = input.GetXJoypad();
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
      // モード切り替え
      ChangeMode();
    }

    void ModeGame::Draw() const {
      // オブジェクトサーバの描画
      _appMain.GetObjectServer().Draw();
    }

    void ModeGame::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種モデルハンドルの読み込み
      using ModelLoadServer = AppFrame::Model::ModelLoadServer;
      const ModelLoadServer::LoadModelMap loadModelMap {
        {"sea", "resource/Model/Sea/skysphere.mv1"},
        {"shark", "resource/Model/Shark/megalodon.mv1"},
        {"tuna", "resource/Model/Tuna/Tuna.mv1"},
        {"jerryfish", "resource/Model/Jerryfish/jerryfish.mv1"}
      };
      // モデル読み込みサーバに一括読み込み
      _app.GetModelLoadServer().LoadModels(loadModelMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGame::ChangeMode() {
      // ゲームオーバーでない場合中断
      if (!_appMain.GetGameOver()) {
        return;
      }
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

    void ModeGame::SetSpawn() {
      // 海中背景の生成
      auto sea = std::make_shared<Sea::SeaSphere>(_appMain);
      _appMain.GetObjectServer().RegisterObject(sea, true);
      // プレイヤー(サメ)の生成
      auto player = std::make_shared<Player::PlayerShark>(_appMain);
      _appMain.GetObjectServer().RegisterObject(player, true);
      // 生成情報の設定
      _spawn->SetSpawn();
    }
  } // namespace Mode
} // namespace Game