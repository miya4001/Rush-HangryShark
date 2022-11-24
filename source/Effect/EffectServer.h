/*****************************************************************//**
 * @file   EffectServer.h
 * @brief  �G�t�F�N�g���Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   November 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �G�t�F�N�g
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    class EffectBase;
    /**
     * @class  EffectServer
     * @brief  �G�t�F�N�g�̊��N���X
     */
    class EffectServer {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      EffectServer();
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectServer();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  �`��
       */
      void Draw() const;
      /**
       * @brief  �G�t�F�N�g�̐���
       * @param  number �G�t�F�N�g�ԍ�
       * @param  position �G�t�F�N�g�Đ��ʒu
       * @param  rotation �G�t�F�N�g�Đ�����
       */
      void MakeEffect(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation);

    private:
      /**
       * @brief  �G�t�F�N�g�̓o�^
       * @param  effect �G�t�F�N�g�̃V�F�A�[�h�|�C���^
       */
      void RegisterEffect(std::shared_ptr<EffectBase> effect);

      //!< �G�t�F�N�g���W�X�g��
      std::vector<std::shared_ptr<EffectBase>> _effectRegistry;
    };
  } // namespace Effect
  /**
   * @brief  �G�t�F�N�g�ԍ�
   */
  namespace EffectNumber {

  } // namespace EffectNumber
} // namespace Game