/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  �G�̊��N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �G
   */
  namespace Enemy {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  EnemyBase
     * @brief  �G�̊��N���X
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @brief  �G�̏�Ԃ̗񋓌^�N���X
       */
      enum class EnemyState {
        Idle,    //!< �ҋ@
        Swim,    //!< �V�j
        Attack,  //!< �U��
        Dead     //!< ���S
      };
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EnemyBase(Application::ApplicationMain& app);
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
      void Draw() const override;
      /**
       * @brief  �������̐ݒ�
       * @param  position �������W
       * @param  rotation ��������
       */
      virtual void Spawn(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  �G�̏�Ԏ��S�ݒ�
       */
      virtual void SetEnemyDead() {
        _enemyState = EnemyState::Dead;
      }
      /**
       * @brief  �H���l�̎擾
       * @return �H���l
       */
      virtual int GetFoodValue() const {
        return _foodValue;
      }
      /**
       * @brief  �G�̏�Ԃ̎擾
       * @return �G�̏��
       */
      virtual EnemyState GetEnemyState() const {
        return _enemyState;
      }
      /**
       * @brief  ���̏Փ˔���̎擾
       * @return ���̏Փ˔���̎Q��
       */
      virtual Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }

    protected:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      virtual void SetParameters();
      /**
       * @brief  �C���͈͓�����
       * @return true:�C���͈͓�
       *         false:�C���͈͊O
       */
      virtual bool InTheSea();
      /**
       * @brief  �ړ�
       */
      virtual void Move();
      /**
       * @brief  �Փ�
       */
      virtual void Hit();
      /**
       * @brief  ���S
       */
      virtual void Dead();

      int _foodValue{ 0 };  //!< �H���l
      //!< �G�̏��
      EnemyState _enemyState{ EnemyState::Idle };
      //!< ���̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
    };
  } // namespace Enemy
} // namespace Game