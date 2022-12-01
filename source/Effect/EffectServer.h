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
   * @brief  �A�v���P�[�V����
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  �G�t�F�N�g
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    class EffectBase;
    class EffectBlood;
    class EffectParalysis;
    /**
     * @class  EffectServer
     * @brief  �G�t�F�N�g�̊��N���X
     */
    class EffectServer {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectServer(Application::ApplicationMain& app);
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
      /**
       * @brief  ���̐���
       * @param  position �G�t�F�N�g�Đ��ʒu
       * @param  rotation �G�t�F�N�g�Đ�����
       * @return ���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectBlood> Blood(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  ��Ⴢ̐���
       * @param  position �G�t�F�N�g�Đ��ʒu
       * @param  rotation �G�t�F�N�g�Đ�����
       * @return ��Ⴢ̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<EffectParalysis> Paralysis(const AppMath::Vector4 position, const AppMath::Vector4 rotation);

      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �G�t�F�N�g���W�X�g��
      std::vector<std::shared_ptr<EffectBase>> _effectRegistry;
    };
  } // namespace Effect
  /**
   * @brief  �G�t�F�N�g�ԍ�
   */
  namespace EffectNumber {
    constexpr int Blood = 1;      //!< ��
    constexpr int Paralysis = 2;  //!< ���
  } // namespace EffectNumber
} // namespace Game