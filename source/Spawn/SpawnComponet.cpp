/*****************************************************************//**
 * @file   SpawnComponet.cpp
 * @brief  生成コンポーネントクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "SpawnComponent.h"
#include "../Application/ApplicationMain.h"
#include "SpawnServer.h"
#include "SpawnEnemy.h"

namespace {
  // 生成各種定数
  constexpr int Timing = 180;  //!< 生成タイミング
  // 生成キー
  constexpr auto EnemyA = "enemyA";
  constexpr auto EnemyB = "enemyB";
}

namespace Game{
  namespace Spawn {
    SpawnComponent::SpawnComponent(Application::ApplicationMain& app) : _app(app) {

    }

    SpawnComponent::~SpawnComponent() {

    }

    void SpawnComponent::Release() {
      // 生成カウント初期化
      _spawnCount = 0;
    }

    void SpawnComponent::Process() {
      // 生成タイミングの管理
      if (!SpawnTiming()) {
        return;
      }
      // 敵の生成
      SpawnEnemy();
    }

    void SpawnComponent::SetSpawnTable() {
      // 敵生成情報
      const SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Tuna, {-500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}}
      };
      const SpawnServer::EnemyTable enemyB{
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // 生成情報の登録
      _app.GetSpawnServer().RegisterSpawnTable(EnemyA, enemyA);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyB, enemyB);
    }

    bool SpawnComponent::SpawnTiming() {
      // 生成カウントが生成タイミング以下の場合
      if (_spawnCount <= Timing) {
        // 生成カウントを増やす
        ++_spawnCount;
        // 生成を行わない
        return false;
      }
      // 生成カウント初期化
      _spawnCount = 0;
      // 生成を行う
      return true;
    }

    void SpawnComponent::SpawnEnemy() {
      // 生成
      _app.GetSpawnServer().Spawn(EnemyA);
    }
  } // namespace Spawn
} // namespace Game