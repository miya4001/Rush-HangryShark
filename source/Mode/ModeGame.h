/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  ���[�h�Q�[���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "../Spawn/SpawnComponent.h"
#include "../UI/UIServer.h"

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
    constexpr auto Game = "ModeGame";  //!< ���[�h�Q�[���o�^�p�L�[
    /**
     * @class  ModeGame
     * @brief  ���[�h�Q�[���N���X
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeGame(Application::ApplicationMain& app);
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
       * @brief  UI�̐ݒ�
       */
      void SetUI();
      /**
       * @brief  ���[�h�|�[�Y�J��
       */
      void ToModePause();
      /**
       * @brief  ���[�h�Q�[���I�[�o�[�J��
       */
      void ToModeGameOver();
      /**
       * @brief  ���[�h�Q�[���N���A�J��
       */
      void ToModeGameClear();

      bool _isPause{ false };  //!< �|�[�Y�t���O
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
      //!< �����R���|�[�l���g
      std::unique_ptr<Spawn::SpawnComponent> _spawn{ nullptr };
      //!< UI�T�[�o
      std::unique_ptr<UI::UIServer> _uiServer{ nullptr };
    };
  } // namespace Mode
} // namespace Game