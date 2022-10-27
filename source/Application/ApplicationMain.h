/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  アプリケーションメインクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  オブジェクト
   */
  namespace Object {
    class ObjectServer;
  } // namespace Object
  /**
   * @brief  カメラ
   */
  namespace Camera {
    class Camera;
  } // namespace Camera
  /**
   * @brief  生成
   */
  namespace Spawn {
    class SpawnServer;
  } // namespace Spawn
  /**
   * @brief  アプリケーション
   */
  namespace Application {
    /**
     * @class  ApplicationMain
     * @brief  アプリケーションメインクラス
     */
    class ApplicationMain : public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  コンストラクタ
       */
      ApplicationMain();
      /**
       * @brief  アプリケーションの初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  ゲームオーバーフラグの設定
       * @param  flag フラグ
       */
      inline void SetGameOver(const bool flag) {
        _isGameOver = flag;
      }
      /**
       * @brief  ゲームクリアフラグの設定
       * @param  flag フラグ
       */
      inline void SetGameClear(const bool flag) {
        _isGameClear = flag;
      }
      /**
       * @brief  ゲームオーバーフラグの取得
       * @return ゲームオーバーフラグ
       */
      inline bool GetGameOver() const {
        return _isGameOver;
      }
      /**
       * @brief  ゲームクリアフラグの取得
       * @return ゲームクリアフラグ
       */
      inline bool GetGameClear() const {
        return _isGameClear;
      }
      /**
       * @brief  オブジェクトサーバの取得
       * @return オブジェクトサーバの参照
       */
      Object::ObjectServer& GetObjectServer();
      /**
       * @brief  カメラの取得
       * @return カメラの参照
       */
      Camera::Camera& GetCamera();
      /**
       * @brief  生成サーバの取得
       * @return 生成サーバの参照
       */
      Spawn::SpawnServer& GetSpawnServer();

    private:
      bool _isGameOver{ false };   //!< ゲームオーバーフラグ
      bool _isGameClear{ false };  //!< ゲームクリアフラグ
      //!< オブジェクトサーバ
      std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
      //!< カメラ
      std::unique_ptr<Camera::Camera> _camera{ nullptr };
      //!< 生成サーバ
      std::unique_ptr<Spawn::SpawnServer> _spawnServer{ nullptr };
    };
  } // namespace Application
} // namespace Game