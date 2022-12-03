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
    constexpr auto GameOver = "ModeGameOver";  //!< ���[�h�Q�[���I�[�o�[�o�^�p�L�[
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
      /**
       * @brief  �J�[�\������
       * @param  leftY ���X�e�B�b�N�㉺���͒l
       */
      void CursorInput(const int leftY);

      int _gameOver{ -1 };      //!< �Q�[���I�[�o�[�摜
      int _retry{ -1 };         //!< ���g���C�摜
      int _backTitle{ -1 };     //!< �^�C�g���o�b�N�摜
      int _bubble{ -1 };        //!< �A�摜
      int _switch{ -1 };        //!< �؂�ւ��摜
      int _bubbleY{ 0 };        //!< �Ay���W
      bool _isStick{ false };   //!< ���X�e�B�b�N����
      bool _decision{ false };  //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game