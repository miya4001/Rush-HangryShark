/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  ���̏Փ˔���N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �I�u�W�F�N�g
   */
  namespace Object {
    class ObjectBase;
  } // namespace Object
  /**
   * @brief  �Փ˔���
   */
  namespace Collision {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  CollisionSphere
     * @brief  ���̏Փ˔���N���X
     */
    class CollisionSphere {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  owner ���L�҂̎Q��
       * @param  center ���S���W
       * @param  radius ���̔��a
       */
      CollisionSphere(Object::ObjectBase& owner, const AppMath::Vector4 center, const float radius);
      /**
       * @brief  �f�X�g���N�^
       */
      ~CollisionSphere();
      /**
       * @brief  �X�V
       * @param  move �ړ���
       */
      void Process(AppMath::Vector4 move);
#ifdef _DEBUG
      /**
       * @brief  �`��
       */
      void Draw() const;
      /**
       * @brief  �h��Ԃ�����
       */
      void NoFill();
#endif
      /**
       * @brief  ���Ƌ��̏Փ˔���
       * @param  sphere �Ώۂ̋�
       * @return true:�Փ˂���
       *         false:�Փ˂Ȃ�
       */
      bool IntersectSphere(const CollisionSphere& sphere);
      /**
       * @brief  ���[�J�����W�̐ݒ�
       * @param  position ���W
       */
      inline void SetPosition(const AppMath::Vector4 position) {
        _position = position;
      }
      /**
       * @brief  ���[�J�����W�̎擾
       * @return ���[�J�����W
       */
      AppMath::Vector4 GetPosition() {
        return _position;
      }

    private:
      float _radius{ 0.0f };     //!< ���̔��a
      bool _collision{ false };  //!< �Փ˔���
#ifdef _DEBUG
      bool _drawFill{ false };   //!< �h��Ԃ�
#endif
      //!< ���L�҂̎Q��
      Object::ObjectBase& _owner;
      //!< ���[�J�����W
      AppMath::Vector4 _position;
    };
  } // namespace Collision
} // namespace Game