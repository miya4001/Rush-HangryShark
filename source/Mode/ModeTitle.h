/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  ���[�h�^�C�g���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
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
    constexpr auto MTitle = "ModeTitle";  //!< ���[�h�^�C�g���o�^�p�L�[
    /**
     * @class  ModeTitle
     * @brief  ���[�h�^�C�g���N���X
     */
    class ModeTitle : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ModeTitle(Application::ApplicationMain& app);
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
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game