/*****************************************************************//**
 * @file   SpawnComponent.h
 * @brief  生成コンポーネントクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  アプリケーション
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  生成
   */
  namespace Spawn {
    /**
     * @class  SpawnComponent
     * @brief  生成コンポーネントクラス
     */
    class SpawnComponent {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      SpawnComponent(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~SpawnComponent();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  生成情報の設定
       */
      void SetSpawn();

    private:
      /**
       * @brief  生成タイミングの管理
       * @return true:生成を行う
       *         false:生成を行わない
       */
      bool SpawnTiming();
      /**
       * @brief  敵の生成
       */
      void SpawnEnemy();
      /**
       * @brief  敵生成情報の登録
       */
      void RegisterEnemyTable();

      int _spawnCount{ 0 };       //!< 生成カウント
      bool _isRegister{ false };  //!< 登録フラグ
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
    };
  } // namespace Spawn
} // namespace Game