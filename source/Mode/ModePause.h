/*****************************************************************//**
 * @file   ModePause.h
 * @brief  ���[�h�|�[�Y�N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
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
    constexpr auto Pause = "ModePause";  //!< ���[�h�|�[�Y�o�^�p�L�[
    /**
     * @class  ModePause
     * @brief  ���[�h�|�[�Y�N���X
     */
    class ModePause : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModePause(Application::ApplicationMain& app);
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
       * @param  leftX ���X�e�B�b�N���E���͒l
       */
      void CursorInput(const int leftX);

      int _pause{ -1 };         //!< �|�[�Y�摜
      int _continue{ -1 };      //!< ���s�摜
      int _retire{ -1 };        //!< ���^�C�A�摜
      int _bubble{ -1 };        //!< �A�摜
      int _switch{ -1 };        //!< �؂�ւ��摜
      int _bubbleX{ 0 };        //!< �Ax���W
      bool _isStick{ false };   //!< ���X�e�B�b�N����
      bool _decision{ false };  //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game