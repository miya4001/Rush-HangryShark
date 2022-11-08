/*****************************************************************//**
 * @file   EnemyShrimp.h
 * @brief  �G(�G�r)�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �G
   */
  namespace Enemy {
    /**
     * @class  EnemyShrimp
     * @brief  �G(�G�r)�N���X
     */
    class EnemyShrimp : public EnemyBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EnemyShrimp(Application::ApplicationMain& app);
      /**
       * @brief  �X�V
       */
      void Process() override;

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;
      /**
       * @brief  �ړ�
       */
      void Move() override;
    };
  } // namespace Enemy
} // namespace Game