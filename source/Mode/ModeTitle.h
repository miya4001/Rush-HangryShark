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
    constexpr auto Title = "ModeTitle";  //!< ���[�h�^�C�g���o�^�p�L�[
    /**
     * @class  ModeTitle
     * @brief  ���[�h�^�C�g���N���X
     */
    class ModeTitle : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
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
      /**
       * @brief  ���[�h�Q�[���J��
       */
      void ToModeGame();

      int _sea{ -1 };           //!< �C���摜
      int _title{ -1 };         //!< �^�C�g���摜
      int _start{ -1 };         //!< �J�n�摜
      int _explain{ -1 };       //!< �����摜
      int _quit{ -1 };          //!< �I���摜
      int _bubble{ -1 };        //!< �A�摜
      int _cursor{ 0 };         //!< �J�[�\��
      int _switch{ -1 };        //!< �؂�ւ��摜
      int _bubbleY{ 0 };        //!< �Ay���W
      bool _isStick{ false };   //!< ���X�e�B�b�N����
      bool _decision{ false };  //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game