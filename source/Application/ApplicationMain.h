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
   * @brief  �I�u�W�F�N�g
   */
  namespace Object {
    class ObjectServer;
  } // namespace Object
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
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�̎擾
       * @return �I�u�W�F�N�g�T�[�o�̎Q��
       */
      Object::ObjectServer& GetObjectServer();

    private:
      //!< �I�u�W�F�N�g�T�[�o
      std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
    };
  } // namespace Application
} // namespace Game