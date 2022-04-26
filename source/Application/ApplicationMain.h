/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  �A�v���P�[�V�������C���N���X
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
    /**
     * @class  ApplicationMain
     * @brief  �A�v���P�[�V�������C���N���X
     */
    class ApplicationMain :public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      ApplicationMain();
      /**
       * @brief  �A�v���P�[�V�����̏�����
       * @return true:����������
       *         false:���������s
       */
      bool Init() override;

    private:

    };
  } // namespace Application
} // namespace Game