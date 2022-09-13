/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  �G�̊��N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �G
   */
  namespace Enemy {
    namespace AppMath = AppFrame::Math;
    /**
     * @class EnemyBase
     * @brief �G�̊��N���X
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      EnemyBase(Application::ApplicationMain& app);
      /**
       * @brief  ������
       * @return true:����������
       *         false:���������s
       */
      virtual bool Init();
      /**
       * @brief  �X�V
       */
      virtual void Process();
      /**
       * @brief  �`��
       */
      void Draw() const override;

    protected:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      virtual void SetParameters();
      /**
       * @brief  �C���͈͊O����
       * @return true:�C���͈͊O
       *         false:�C���͈͓�
       */
      virtual bool IsOverSea();
      /**
       * @brief  �ړ�
       */
      virtual void Move();
      /**
       * @brief  �Փ�
       */
      virtual void Hit();

      //!< ���̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _sphere;
    };
  } // namespace Enemy
} // namespace Game