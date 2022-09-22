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
   * @brief  敵
   */
  namespace Enemy {
    class EnemyTuna;
    class EnemyJerryFish;
  } // namespace Enemy
  /**
   * @brief  生成
   */
  namespace Spawn {
    namespace AppMath = AppFrame::Math;
    /**
     * @class SpawnServer
     * @brief オブジェクトの生成を管理するサーバクラス
     */
    class SpawnServer {
    public:
      /**
       * @brief  敵生成情報を格納する動的配列
       * @param  敵識別番号
       * @param  敵生成位置(プレイヤー座標と加算)
       * @param  敵生成向き
       */
      using EnemyTable = std::vector<std::tuple<int, AppMath::Vector4, AppMath::Vector4>>;
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
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
       * @brief  更新
       */
      void Process();

    private:
      /**
       * @brief  オブジェクトサーバに登録
       */
      void Register();

      int _spawnCount{ 0 };  //!< 生成カウント
    };
  } // namespace Spawn
} // namespace Game