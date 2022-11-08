/*****************************************************************//**
 * @file   EnemyJerryfish.h
 * @brief  �G(�N���Q)�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �G
   */
  namespace Enemy {
    /**
     * @class  EnemyJerryfish
     * @brief  �G(�N���Q)�N���X
     */
    class EnemyJerryfish : public EnemyBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EnemyJerryfish(Application::ApplicationMain& app);
      /**
       * @brief  �X�V
       */
      void Process() override;
      /**
       * @brief  �`��
       */
      void Draw() const override;

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;
      /**
       * @brief  �Փ˔���̐ݒ�
       */
      void SetCollision() override;
      /**
       * @brief  �ړ�
       */
      void Move() override;
      /**
       * @brief  �[�d
       */
      void Charge();
      /**
       * @brief  �U��
       */
      void Attack();

      int _chargeCount{ 0 };  //!< �[�d�J�E���g
      int _attackCount{ 0 };  //!< �U���J�E���g
      //!< �U�����̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _attack{ nullptr };
    };
  } // namespace Enemy
} // namespace Game