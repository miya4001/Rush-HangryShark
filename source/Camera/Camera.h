/*****************************************************************//**
 * @file   Camera.h
 * @brief  カメラクラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  カメラ
   */
  namespace Camera {
    namespace AppMath = AppFrame::Math;
    /**
     * @class Camera
     * @brief カメラクラス
     */
    class Camera {
    public:
      /**
       * @brief  コンストラクタ
       */
      Camera();
      /**
       * @brief  デストラクタ
       */
      ~Camera();
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init();
      /**
       * @brief  追従カメラ
       * @param  target 注視点
       * @param  forward 前方向き
       */
      void Tracking(const AppMath::Vector4 target, const AppMath::Vector4 forward);
      /**
       * @brief  定点カメラ
       * @param  position 位置
       * @param  target 注視点
       */
      void FixedPoint(const AppMath::Vector4 position, const AppMath::Vector4 target);

    private:
      //!< カメラ位置
      AppMath::Vector4 _position;
      //!< カメラ注視点
      AppMath::Vector4 _target;
    };
  } // namespace Camera
} // namespace Game