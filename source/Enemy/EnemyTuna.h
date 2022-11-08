/*****************************************************************//**
 * @file   EnemyTuna.h
 * @brief  �G(�}�O��)�N���X
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
     * @class  EnemyTuna
     * @brief  �G(�}�O��)�N���X
     */
    class EnemyTuna : public EnemyBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EnemyTuna(Application::ApplicationMain& app);
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
       * @brief  �T��
       */
      void Search();
      /**
       * @brief  ����
       */
      void Escape();

      //!< �T�����̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _search{ nullptr };
    };
  } // namespace Enemy
} // namespace Game