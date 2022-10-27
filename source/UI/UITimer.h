/*****************************************************************//**
 * @file   UITimer.h
 * @brief  UI�^�C�}�[�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once
#include "UIBase.h"
#include <vector>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class  UITimer
     * @brief  UI�^�C�}�[�N���X
     */
    class UITimer : public UIBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      UITimer(Application::ApplicationMain& app);
      /**
       * @brief  ������
       * @return true:����������
       *         false:���������s
       */
      bool Init() override;
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
       * @brief  ��b�o��
       */
      void OneSecondPass();
      /**
       * @brief  �^�C�}�[�b�ϊ�
       */
      void TimerConversion();

      int _colon{ -1 };           //!< �R�����摜
      int _frameCount{ 0 };       //!< �t���[���J�E���g
      int _timerSeconds{ 0 };     //!< �^�C�}�[�b
      int _onePlaceSeconds{ 0 };  //!< �b(��̈�)
      int _tenPlaceSeconds{ 0 };  //!< �b(�\�̈�)
      int _onePlaceMinutes{ 0 };  //!< ��(��̈�)
      // �^�C�}�[�����摜
      std::vector<int> _timerNumber;
    };
  } // namespace UI
} // namespace Game