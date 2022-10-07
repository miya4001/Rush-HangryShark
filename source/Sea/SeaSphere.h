/*****************************************************************//**
 * @file   SeaSphere.h
 * @brief  �C���w�i�N���X
 * 
 * @author �{�V�s��
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

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
     * @class  SeaSphere
     * @brief  �C���w�i�N���X
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
      /**
       * @brief  ���̏Փ˔���̎擾
       * @return ���̏Փ˔���̎Q��
       */
      Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;

      //!< ���̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
    };
  } // namespace Sea
} // namespace Game