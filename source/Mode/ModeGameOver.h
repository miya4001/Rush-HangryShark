/*****************************************************************//**
 * @file   ModeGameOver.h
 * @brief  ���[�h�Q�[���I�[�o�[�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
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
   * @brief  ���[�h
   */
  namespace Mode {
    constexpr auto GameOver = "ModeGameOver";  //!< ���[�h�^�C�g���o�^�p�L�[
    /**
     * @class  ModeGameOver
     * @brief  ���[�h�Q�[���I�[�o�[�N���X
     */
    class ModeGameOver : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeGameOver(Application::ApplicationMain& app);
      /**
       * @brief  ������
       * @return true:����������
       *         false:���������s
       */
      bool Init() override;
      /**
       * @brief  ���[�h�J�n
       */
      void Enter() override;
      /**
       * @brief  ���[�h�I��
       */
      void Exit() override;
      /**
       * @brief  ����
       * @param  input �C���v�b�g�}�l�[�W���[�̎Q��
       */
      void Input(AppFrame::Input::InputManager& input) override;
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

      bool _decision{ false };  //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game