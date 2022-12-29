/*****************************************************************//**
 * @file   UIRadar.h
 * @brief  UI���[�_�[�N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
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
     * @class  UIRadar
     * @brief  UI���[�_�[�N���X
     */
    class UIRadar : public UIBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      UIRadar(Application::ApplicationMain& app);
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
       * @brief  ��������
       */
      void ResponseClear();

      double _angle{ 0.0 };  //!< �p�x(���W�A��)
      //!< �`����W
      std::vector<std::pair<int, int>> _drawPosition;
    };
  } // namespace UI
} // namespace Game