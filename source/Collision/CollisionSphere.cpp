/*****************************************************************//**
 * @file   CollisionSphere.cpp
 * @brief  ‹…‚ÌÕ“Ë”»’èƒNƒ‰ƒX
 * 
 * @author ‹{àV—s¶
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
      // ’†SÀ•W‚ÉˆÚ“®—Ê‚ğ‰ÁZ
      _position.Add(move);
    }

#ifdef _DEBUG
    void CollisionSphere::Draw() const {
      // ‹…‚Ì•`‰æ(Õ“Ë‚ ‚è‚Ìê‡‹…‚Ì“h‚è‚Â‚Ô‚µ)
      DrawSphere3D(AppMath::UtilityDX::ToVECTOR(_position), _radius, 10, GetColor(0, 0, 0), 0, _drawFill);
    }
#endif

    bool CollisionSphere::IntersectSphere(const CollisionSphere& sphere) {
      // ‹…‚Æ‹…‚Ì‹——£‚Ì“ñæ
      float distSquared = AppMath::Vector4::LengthSquared(_position - sphere._position);
      // ‹…‚Æ‹…‚Ì”¼Œa‚Ì‡Œv
      float sumRadius = _radius + sphere._radius;
      // ‹——£‚Ì“ñæ‚ª”¼Œa‚Ì‡Œv‚Ì“ñæˆÈ‰º‚Ìê‡Õ“Ë
      _collision = distSquared <= sumRadius * sumRadius;
#ifdef _DEBUG
      // Õ“Ë”»’è‚É‡‚í‚¹‚Ä“h‚è‚Â‚Ô‚µ
      _drawFill = _collision;
#endif
      return _collision;
    }
  } // namespace Collision
} // namespace Game