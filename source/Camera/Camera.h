/*****************************************************************//**
 * @file   Camera.h
 * @brief  �J�����N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �J����
   */
  namespace Camera {
    namespace AppMath = AppFrame::Math;
    /**
     * @class Camera
     * @brief �J�����N���X
     */
    class Camera {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      Camera();
      /**
       * @brief  �f�X�g���N�^
       */
      ~Camera();
      /**
       * @brief  ������
       * @return true:����������
       *         false:���������s
       */
      bool Init();
      /**
       * @brief  �Ǐ]�J����
       * @param  target �����_
       * @param  forward �O������
       */
      void Tracking(const AppMath::Vector4 target, const AppMath::Vector4 forward);
      /**
       * @brief  ��_�J����
       * @param  position �ʒu
       * @param  target �����_
       */
      void FixedPoint(const AppMath::Vector4 position, const AppMath::Vector4 target);

    private:
      //!< �J�����ʒu
      AppMath::Vector4 _position;
      //!< �J���������_
      AppMath::Vector4 _target;
    };
  } // namespace Camera
} // namespace Game