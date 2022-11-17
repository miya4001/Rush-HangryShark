/*****************************************************************//**
 * @file   SpawnComponet.cpp
 * @brief  生成コンポーネントクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "SpawnComponent.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"
#include "SpawnServer.h"
#include "SpawnEnemy.h"

namespace {
  // 生成各種定数
  constexpr int SpawnCountMax = 180;  //!< 生成カウント上限
  constexpr int RandSpawnkeyMax = 6;  //!< ランダム生成キー上限
  // 特殊生成キー
  constexpr auto Start = "start";    //!< 開始テーブル
  constexpr auto Error = "error";    //!< エラー
  // ランダム生成キー
  constexpr auto EnemyA = "enemyA";  //!< テーブルA
  constexpr auto EnemyB = "enemyB";  //!< テーブルB
  constexpr auto EnemyC = "enemyC";  //!< テーブルC
  constexpr auto EnemyD = "enemyD";  //!< テーブルD
  constexpr auto EnemyE = "enemyE";  //!< テーブルE
  constexpr auto EnemyF = "enemyF";  //!< テーブルF
} // namespace

namespace Game{
  namespace Spawn {
    SpawnComponent::SpawnComponent(Application::ApplicationMain& app) : _app(app) {

    }

    SpawnComponent::~SpawnComponent() {
      // 生成サーバの解放
      _app.GetSpawnServer().Release();
    }

    void SpawnComponent::Release() {
      // 変数初期化
      _spawnCount = 0;
      _spawnEnemy = 0;
    }

    void SpawnComponent::Process() {
      // 生成タイミングの管理
      if (SpawnTiming()) {
        // 敵の生成
        SpawnEnemy();
      }
    }

    void SpawnComponent::SetSpawn() {
      // 海中背景の生成
      auto sea = std::make_shared<Sea::SeaSphere>(_app);
      _app.GetObjectServer().RegisterObject(sea, true);
      // プレイヤー(サメ)の生成
      auto player = std::make_shared<Player::PlayerShark>(_app);
      _app.GetObjectServer().RegisterObject(player, true);
      // 敵生成情報の登録
      RegisterEnemyTable();
      // 開始テーブル生成
      _app.GetSpawnServer().Spawn(Start);
    }

    bool SpawnComponent::SpawnTiming() {
      // カウント増加
      _spawnCount = AppMath::Utility::IncrementCount(_spawnCount, SpawnCountMax);
      // 生成カウントが上限の場合
      if (_spawnCount == 0) {
        // 生成を行う
        return true;
      }
      // 生成を行わない
      return false;
    }

    void SpawnComponent::SpawnEnemy() {
      // 生成キーの選択
      auto key = ChooseSpawnKey();
      // 生成
      _app.GetSpawnServer().Spawn(key);
      // 敵生成数を増やす
      ++_spawnEnemy;
    }

    std::string_view SpawnComponent::ChooseSpawnKey() {
      // 空生成キー
      std::string_view key = "";
      // 乱数
      int rand = std::rand();
      // 剰余計算
      int remainder = rand % RandSpawnkeyMax;
      // 剰余に合わせて生成キーの選択
      switch (remainder) {
      case 0:
        key = EnemyA;
        break;
      case 1:
        key = EnemyB;
        break;
      case 2:
        key = EnemyC;
        break;
      case 3:
        key = EnemyD;
        break;
      case 4:
        key = EnemyE;
        break;
      case 5:
        key = EnemyF;
        break;
      default:
        break;
      }
      return key;
    }

    void SpawnComponent::RegisterEnemyTable() {
      // 登録済みの場合中断
      if (_isRegister) {
        return;
      }
      // 開始テーブル
      const SpawnServer::EnemyTable start{
        {SpawnNumber::Shrimp, {500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {0.0f, 0.0f, 1500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {0.0f, 0.0f, -1500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {1500.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-1500.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルA
      const SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Shrimp, {750.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {750.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-750.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-750.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
      };
      // テーブルB
      const SpawnServer::EnemyTable enemyB{
        {SpawnNumber::Tuna, {1000.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {1000.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルC
      const SpawnServer::EnemyTable enemyC{
        {SpawnNumber::Jerryfish, {0.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルD
      const SpawnServer::EnemyTable enemyD{
        {SpawnNumber::Shrimp, {0.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {500.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-500.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルE
      const SpawnServer::EnemyTable enemyE{
        {SpawnNumber::Tuna, {0.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルF
      const SpawnServer::EnemyTable enemyF{
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // 生成情報の登録
      _app.GetSpawnServer().RegisterSpawnTable(Start, start);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyA, enemyA);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyB, enemyB);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyC, enemyC);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyD, enemyD);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyE, enemyE);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyF, enemyF);
      // 登録完了
      _isRegister = true;
    }
  } // namespace Spawn
} // namespace Game