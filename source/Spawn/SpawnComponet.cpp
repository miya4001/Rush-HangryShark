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
  constexpr auto Start = "start";    //!< 開始テーブル
  constexpr auto EnemyA = "enemyA";  //!< テーブルA
  constexpr auto EnemyB = "enemyB";  //!< テーブルB
}

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
    }

    void SpawnComponent::Process() {
      // 生成タイミングの管理
      if (!SpawnTiming()) {
        return;
      }
      // 敵の生成
      SpawnEnemy();
    }

    void SpawnComponent::SetSpawn() {
      // 敵生成情報の登録
      RegisterEnemyTable();
      // 開始テーブル生成
      _app.GetSpawnServer().Spawn(Start);
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

    void SpawnComponent::RegisterEnemyTable() {
      // 登録済みの場合中断
      if (_isRegister) {
        return;
      }
      // 開始テーブル
      const SpawnServer::EnemyTable start{
        {SpawnNumber::Tuna, {0.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {0.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {1000.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルA
      const SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Tuna, {1000.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {1000.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // テーブルB
      const SpawnServer::EnemyTable enemyB{
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // 生成情報の登録
      _app.GetSpawnServer().RegisterSpawnTable(Start, start);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyA, enemyA);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyB, enemyB);
      // 登録完了
      _isRegister = true;
    }
  } // namespace Spawn
} // namespace Game