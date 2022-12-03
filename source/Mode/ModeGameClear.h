/*****************************************************************//**
 * @file   ModeGameClear.h
 * @brief  ���[�h�Q�[���N���A�N���X
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
    constexpr auto GameClear = "ModeGameClear";  //!< ���[�h�Q�[���N���A�o�^�p�L�[
    /**
     * @class  ModeGameClear
     * @brief  ���[�h�Q�[���N���A�N���X
     */
    class ModeGameClear : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeGameClear(Application::ApplicationMain& app);
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

      int _gameClear{ -1 };     //!< �Q�[���N���A�摜
      int _back{ -1 };          //!< �o�b�N�摜
      int _bubble{ -1 };        //!< �A�摜
      bool _decision{ false };  //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game