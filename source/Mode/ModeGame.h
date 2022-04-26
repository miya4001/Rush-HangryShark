/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  ���[�h�Q�[���N���X
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
    /**
     * @class  ModeGame
     * @brief  ���[�h�Q�[���N���X
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ModeGame(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModeGame() override;
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