/*****************************************************************//**
 * @file   EffectDiscover.h
 * @brief  �G�t�F�N�g(����)�N���X
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
     * @class  EffectDiscover
     * @brief  �G�t�F�N�g(����)�N���X
     */
    class EffectDiscover : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectDiscover(Application::ApplicationMain& app);

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;
    };
  } // namespace Effect
} // namespace Game