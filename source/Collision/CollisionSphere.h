/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  球の衝突判定クラス
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
   * @brief  オブジェクト
   */
  namespace Object {
    class ObjectBase;
  } // namespace Object
  /**
   * @brief  衝突判定
   */
  namespace Collision {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  CollisionSphere
     * @brief  球の衝突判定クラス
     */
    class CollisionSphere {
    public:
      /**
       * @brief  コンストラクタ
       * @param  owner 所有者の参照
       * @param  center 中心座標
       * @param  radius 球の半径
       */
      CollisionSphere(Object::ObjectBase& owner, const AppMath::Vector4 center, const float radius);
      /**
       * @brief  デストラクタ
       */
      ~CollisionSphere();
      /**
       * @brief  更新
       * @param  move 移動量
       */
      void Process(AppMath::Vector4 move);
#ifdef _DEBUG
      /**
       * @brief  描画
       */
      void Draw() const;
      /**
       * @brief  塗りつぶし解除
       */
      void NoFill();
#endif
      /**
       * @brief  球と球の衝突判定
       * @param  sphere 対象の球
       * @return true:衝突あり
       *         false:衝突なし
       */
      bool IntersectSphere(const CollisionSphere& sphere);
      /**
       * @brief  ローカル座標の設定
       * @param  position 座標
       */
      inline void SetPosition(const AppMath::Vector4 position) {
        _position = position;
      }
      /**
       * @brief  ローカル座標の取得
       * @return ローカル座標
       */
      AppMath::Vector4 GetPosition() {
        return _position;
      }

    private:
      float _radius{ 0.0f };     //!< 球の半径
      bool _collision{ false };  //!< 衝突判定
#ifdef _DEBUG
      bool _drawFill{ false };   //!< 塗りつぶし
#endif
      //!< 所有者の参照
      Object::ObjectBase& _owner;
      //!< ローカル座標
      AppMath::Vector4 _position;
    };
  } // namespace Collision
} // namespace Game