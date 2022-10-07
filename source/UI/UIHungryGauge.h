/*****************************************************************//**
 * @file   UIHungryGauge.h
 * @brief  UI�󕠃Q�[�W�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once
#include "UIBase.h"

 /**
  * @brief  �Q�[��
  */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class  UIHungryGauge
     * @brief  UI�󕠃Q�[�W�N���X
     */
    class UIHungryGauge : public UIBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      UIHungryGauge(Application::ApplicationMain& app);
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
      int _gauge{ -1 };          //!< �󕠃Q�[�W�摜
      int _gaugeBar{ -1 };       //!< �󕠃Q�[�W�o�[�摜
      int _gaugeBarRightX{ 0 };  //!< �Q�[�W�o�[�E��x���W
    };
  } // namespace UI
} // namespace Game