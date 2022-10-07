/*****************************************************************//**
 * @file   SpawnServer.cpp
 * @brief  オブジェクトの生成を管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "SpawnServer.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "SpawnEnemy.h"
#include "../Enemy/EnemyTuna.h"
#include "../Enemy/EnemyJerryfish.h"

namespace Game {
  namespace Spawn {
    SpawnServer::SpawnServer(Application::ApplicationMain& app) : _app(app) {
      // レジストリの初期化
      _spawnRegistry.clear();
    }

    SpawnServer::~SpawnServer() {

    }

    void SpawnServer::Release() {
      // レジストリが空の場合中断
      if (_spawnRegistry.empty()) {
        return;
      }
      // 生成情報の全解放
      for (auto&& [key, map] : _spawnRegistry) {
        map.clear();
      }
      // レジストリの解放
      _spawnRegistry.clear();
    }

    void SpawnServer::RegisterSpawnTable(const std::string_view key, const EnemyTable enemy) {
      // 生成情報の確認
      if (enemy.empty()) {
#ifdef _DEBUG
        throw ("SpawnServer:生成情報が空です\n");
#endif
        return;  // 生成情報が空
      }
      // キーが登録済みの場合
      if (_spawnRegistry.contains(key.data())) {
        // 重複している生成情報の削除
        DeleteSpawnTable(key);
      }
      // 生成情報のシェアードポインタの動的配列
      SpawnMap spawnMap;
      // 敵の生成情報のシェアードポインタを格納
      for (auto&& value : enemy) {
        spawnMap.emplace_back(std::make_shared<SpawnEnemy>(value));
      }
      // レジストリに登録する
      _spawnRegistry.emplace(key.data(), spawnMap);
    }

    void SpawnServer::Spawn(const std::string_view key) {
      // 生成情報を基にオブジェクトを生成し登録
      for (auto&& spawn : _spawnRegistry.at(key.data()))
        // 識別番号から判別
        switch (spawn->GetNumber()) {
        // マグロ
        case SpawnNumber::Tuna:
          RegisterObjctServer(EnemyTuna(*spawn.get()));
          break;
        // クラゲ
        case SpawnNumber::Jerryfish:
          RegisterObjctServer(EnemyJerryfish(*spawn.get()));
          break;
        // 該当なし
        default:
#ifdef _DEBUG
          throw ("SpawnServer:識別番号が不正です\n");
#endif
          break;
        }
    }

    void SpawnServer::RegisterObjctServer(std::shared_ptr<Object::ObjectBase> object) {
      // オブジェクトサーバへの登録を行う
      _app.GetObjectServer().RegisterObject(std::move(object));
    }

    void SpawnServer::DeleteSpawnTable(const std::string_view key) {
      // 生成情報の取り出し
      auto&& map = _spawnRegistry.at(key.data());
      // 生成情報の削除
      map.clear();
      // レジストリから削除する
      _spawnRegistry.erase(key.data());
    }

    std::shared_ptr<Enemy::EnemyTuna> SpawnServer::EnemyTuna(SpawnEnemy& spawn) const {
      // マグロの生成
      auto tuna = std::make_shared<Enemy::EnemyTuna>(_app);
      // スポーン情報の設定
      auto [position, rotation] = spawn.GetTransform();
      tuna->Spawn(position, rotation);
      // 生成したシェアードポインタを返す
      return std::move(tuna);
    }

    std::shared_ptr<Enemy::EnemyJerryfish> SpawnServer::EnemyJerryfish(SpawnEnemy& spawn) const {
      // クラゲの生成
      auto jerryfish = std::make_shared<Enemy::EnemyJerryfish>(_app);
      // スポーン情報の設定
      auto [position, rotation] = spawn.GetTransform();
      jerryfish->Spawn(position, rotation);
      // 生成したシェアードポインタを返す
      return std::move(jerryfish);
    }
  } // namespace Spawn
} // namespace Game