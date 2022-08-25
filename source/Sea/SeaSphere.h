/*****************************************************************//**
 * @file   SeaSphere.h
 * @brief  �C���w�i�N���X
 * 
 * @author �{�V�s��
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �C
   */
  namespace Sea {
    namespace AppMath = AppFrame::Math;
    /**
     * @class SeaSphere
     * @brief �C���w�i�N���X
     */
    class SeaSphere : public Object::ObjectBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      SeaSphere(Application::ApplicationMain& app);
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

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;
    };
  } // namespace Sea
} // namespace Game