/*****************************************************************//**
 * @file   ModeAMG.h
 * @brief  ���[�hAMG�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �A�v���P�[�V����
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  ���[�h
   */
  namespace Mode {
    constexpr auto AMG = "ModeAMG";  //!<   ���[�hAMG
    /**
     * @class  ModeAMG
     * @brief  ���[�hAMG�N���X
     */
    class ModeAMG : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeAMG(Application::ApplicationMain& app);
      /**
       * @brief  ���[�h�J�n
       */
      void Enter() override;
      /**
       * @brief  ���[�h�I��
       */
      void Exit() override;
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
       * @brief  ���\�[�X�ǂݍ���
       */
      void LoadResource() override;
      /**
       * @brief  ���[�h�؂�ւ�
       */
      void ChangeMode() override;

      int _sea{ -1 };  //!< �C���摜
      int _amg{ -1 };  //!< AMG�摜
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // Game