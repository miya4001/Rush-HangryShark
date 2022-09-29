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
#include "../Spawn/SpawnServer.h"
#include "../Spawn/SpawnEnemy.h"
#include "../Player/PlayerShark.h"
#include "../Sea/SeaSphere.h"

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
      // 生成サーバの解放
      _appMain.GetSpawnServer().Release();
      // 複製したモデルの解放
      _appMain.GetModelLoadServer().DeleteDuplicateModels();
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
        {"shark", "resource/Model/Shark/megalodon.mv1"},
        {"sea", "resource/Model/Sea/skysphere.mv1"},
        {"tuna", "resource/Model/Tuna/Tuna.mv1"},
        {"jerryfish", "resource/Model/Jerryfish/jerryfish.mv1"}
      };
      // モデル読み込みサーバに一括読み込み
      _app.GetModelLoadServer().LoadModels(loadModelMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGame::SetSpawn() {
      // プレイヤー(サメ)の生成
      auto player = std::make_shared<Player::PlayerShark>(_appMain);
      _appMain.GetObjectServer().RegisterObject(player, true);
      // 海中背景の生成
      auto sea = std::make_shared<Sea::SeaSphere>(_appMain);
      _appMain.GetObjectServer().RegisterObject(sea, true);
      // 敵生成情報
      const Spawn::SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Tuna, {-500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // 生成情報の登録
      _appMain.GetSpawnServer().RegisterSpawnTable("enemyA", enemyA);
      _appMain.GetSpawnServer().Spawn("enemyA");
    }
  } // namespace Mode
} // namespace Game