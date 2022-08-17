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
   * @brief  アプリケーション
   */
  namespace Application {
    /**
     * @class  ApplicationMain
     * @brief  アプリケーションメインクラス
     */
    class ApplicationMain :public AppFrame::Application::ApplicationBase {
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
       * @brief  オブジェクトサーバの取得
       * @return オブジェクトサーバの参照
       */
      Object::ObjectServer& GetObjectServer();
      /**
       * @brief  カメラの取得
       * @return カメラの参照
       */
      Camera::Camera& GetCamera();

    private:
      //!< オブジェクトサーバ
      std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
      //!< カメラ
      std::unique_ptr<Camera::Camera> _camera{ nullptr };
    };
  } // namespace Application
} // namespace Game