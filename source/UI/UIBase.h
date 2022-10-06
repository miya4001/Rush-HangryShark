/*****************************************************************//**
 * @file   UIBase.h
 * @brief  UI�̊��N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �A�v���P�[�V����
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class UIBase
     * @brief UI�̊��N���X
     */
    class UIBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      UIBase(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      virtual ~UIBase();
      /**
       * @brief  ������
       * @return true:����������
       *         false:���������s
       */
      virtual bool Init();
      /**
       * @brief  �X�V
       */
      virtual void Process();
      /**
       * @brief  �`��
       */
      virtual void Draw() const;

    protected:
      int _graphicHandle{ -1 };  //!< �摜�n���h��
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;

    };
  } // namespace UI
} // namespace Game