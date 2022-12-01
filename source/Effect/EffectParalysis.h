/*****************************************************************//**
 * @file   EffectParalysis.h
 * @brief  �G�t�F�N�g(���)�N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
 *********************************************************************/
#pragma once
#include "EffectBase.h"

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �G�t�F�N�g
   */
  namespace Effect {
    /**
     * @class  EffectParalysis
     * @brief  �G�t�F�N�g(���)�N���X
     */
    class EffectParalysis : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectParalysis(Application::ApplicationMain& app);

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;
    };
  } // namespace Effect
} // namespace Game