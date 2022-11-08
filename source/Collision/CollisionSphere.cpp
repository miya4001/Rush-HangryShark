/*****************************************************************//**
 * @file   CollisionSphere.cpp
 * @brief  ���̏Փ˔���N���X
 * 
 * @author �{�V�s��
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
      // ���S���W�Ɉړ��ʂ����Z
      _position.Add(move);
    }

#ifdef _DEBUG
    void CollisionSphere::Draw() const {
      // ���̕`��(�Փ˂���̏ꍇ���̓h��Ԃ�)
      DrawSphere3D(AppMath::UtilityDX::ToVECTOR(_position), _radius, 10, GetColor(0, 0, 0), 0, _drawFill);
    }
#endif

    bool CollisionSphere::IntersectSphere(const CollisionSphere& sphere) {
      // ���Ƌ��̋����̓��
      float distSquared = AppMath::Vector4::LengthSquared(_position - sphere._position);
      // ���Ƌ��̔��a�̍��v
      float sumRadius = _radius + sphere._radius;
      // �����̓�悪���a�̍��v�̓��ȉ��̏ꍇ�Փ�
      _collision = distSquared <= sumRadius * sumRadius;
#ifdef _DEBUG
      // �Փ˔���ɍ��킹�ēh��Ԃ�
      _drawFill = _collision;
#endif
      return _collision;
    }
  } // namespace Collision
} // namespace Game