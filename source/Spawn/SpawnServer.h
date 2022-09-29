/*****************************************************************//**
 * @file   SpawnServer.h
 * @brief  オブジェクトの生成を管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game{
  /**
   * @brief  アプリケーション
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  オブジェクト
   */
  namespace Object {
    class ObjectBase;
  } // namespace Object
  /**
   * @brief  敵
   */
  namespace Enemy {
    class EnemyTuna;
    class EnemyJerryfish;
  } // namespace Enemy
  /**
   * @brief  生成
   */
  namespace Spawn {
    class SpawnEnemy;
    /**
     * @class SpawnServer
     * @brief オブジェクトの生成を管理するサーバクラス
     */
    class SpawnServer {
    public:
      /**
       * @brief  敵生成情報を格納する動的配列
       */
      using EnemyTable = std::vector<SpawnEnemy>;
      /**
       * @brief  生成情報のシェアードポインタを格納する動的配列
       */
      using SpawnMap = std::vector<std::shared_ptr<SpawnEnemy>>;
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      SpawnServer(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~SpawnServer();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  生成情報の登録
       * @param  key 生成情報に紐づける文字列
       * @param  enemy 生成情報が格納された連想配列
       */
      void RegisterSpawnTable(const std::string_view key, const EnemyTable enemy);
      /**
       * @brief  オブジェクトの生成
       * @param  key 生成キー 
       */
      void Spawn(const std::string_view key);

    private:
      /**
       * @brief  オブジェクトサーバに登録
       */
      void RegisterObjctServer(std::shared_ptr<Object::ObjectBase> object);
      /**
       * @brief  生成情報の削除
       * @param  key 生成キー
       */
      void DeleteSpawnTable(const std::string_view key);
      /**
       * @brief  マグロの生成
       * @param  spawn 生成情報
       * @return マグロのシェアードポインタ
       */
      std::shared_ptr<Enemy::EnemyTuna> EnemyTuna(SpawnEnemy& spawn) const;
      /**
       * @brief  クラゲの生成
       * @param  spawn 生成情報
       * @return クラゲのシェアードポインタ
       */
      std::shared_ptr<Enemy::EnemyJerryfish> EnemyJerryfish(SpawnEnemy& spawn) const;

      int _spawnCount{ 0 };  //!< 生成カウント
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< 生成レジストリ
      std::unordered_map<std::string, SpawnMap> _spawnRegistry;
    };
  } // namespace Spawn
  /**
   * @brief  生成番号
   */
  namespace SpawnNumber {
    constexpr int Tuna = 1;       //!< マグロ
    constexpr int Jerryfish = 2;  //!< クラゲ
  }
} // namespace Game