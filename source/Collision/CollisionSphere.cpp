/*****************************************************************//**
 * @file   CollisionSphere.cpp
 * @brief  球の衝突判定クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "CollisionSphere.h"

namespace Game {
  namespace Collision {
    CollisionSphere::CollisionSphere(Object::ObjectBase& owner, const AppMath::Vector4 center, const float radius) : _owner(owner) {
      _position = center;
      _radius = radius;
    }

    CollisionSphere::~CollisionSphere() {

    }

    void CollisionSphere::Process(AppMath::Vector4 move) {
      // 中心座標に移動量を加算
      _position.Add(move);
    }

#ifdef _DEBUG
    void CollisionSphere::Draw() const {
      // 球の描画(衝突ありの場合球の塗りつぶし)
      DrawSphere3D(AppMath::UtilityDX::ToVECTOR(_position), _radius, 10, GetColor(0, 0, 0), 0, _drawFill);
    }
#endif

    bool CollisionSphere::IntersectSphere(const CollisionSphere& sphere) {
      // 球と球の距離の二乗
      float distSquared = AppMath::Vector4::LengthSquared(_position - sphere._position);
      // 球と球の半径の合計
      float sumRadius = _radius + sphere._radius;
      // 距離の二乗が半径の合計の二乗以下の場合衝突
      _collision = distSquared <= sumRadius * sumRadius;
#ifdef _DEBUG
      // 衝突判定に合わせて塗りつぶし
      _drawFill = _collision;
#endif
      return _collision;
    }
  } // namespace Collision
} // namespace Game