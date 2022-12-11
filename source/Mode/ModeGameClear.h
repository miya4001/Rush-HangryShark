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
      /**
       * @brief  �G���̐ݒ�
       */
      void SetEnemyNumbers();

      int _gameClear{ -1 };     //!< �Q�[���N���A�摜
      int _shrimp{ -1 };        //!< �G�r���摜
      int _tuna{ -1 };          //!< �}�O�����摜
      int _jerryfish{ -1 };     //!< �N���Q���摜
      int _back{ -1 };          //!< �o�b�N�摜
      int _bubble{ -1 };        //!< �A�摜
      int _shrimpTen{ 0 };      //!< �G�r��(�\�̈�)
      int _shrimpOne{ 0 };      //!< �G�r��(��̈�)
      int _tunaTen{ 0 };        //!< �}�O����(�\�̈�)
      int _tunaOne{ 0 };        //!< �}�O����(��̈�)
      int _jerryfishTen{ 0 };   //!< �N���Q��(�\�̈�)
      int _jerryfishOne{ 0 };   //!< �N���Q��(��̈�)
      bool _decision{ false };  //!< �I������
      // �����摜
      std::vector<int> _number;
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game