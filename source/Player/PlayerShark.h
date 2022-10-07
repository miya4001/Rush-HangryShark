/*****************************************************************//**
 * @file   PlayerShark.h
 * @brief  �v���C���[(�T��)�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �v���C���[
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
    /**
     * @class PlayerShark
     * @brief �v���C���[(�T��)�N���X
     */
    class PlayerShark : public Object::ObjectBase {
    public:
      /**
       * @brief  �v���C���[�̏�Ԃ̗񋓌^�N���X
       */
      enum class PlayerState {
        Idle,    //!< �ҋ@
        Swim,    //!< �ړ�
        Rush,    //!< �ˌ�
        Attack,  //!< �U��
        Eat      //!< �ߐH
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      PlayerShark(Application::ApplicationMain& app);
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
      /**
       * @brief  �v���C���[��Ԃ̎擾
       * @return �v���C���[���
       */
      PlayerState GetPlayerState() {
        return _playerState;
      }
      /**
       * @brief  �{�̋��̏Փ˔���̎擾
       * @return �{�̋��̏Փ˔���̎Q��
       */
      Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }
      /**
       * @brief  �U�����̏Փ˔���̎擾
       * @return �U�����̏Փ˔���̎Q��
       */
      Collision::CollisionSphere& GetAttack() {
        return *_attack;
      }
      /**
       * @brief  �󕠒l�̎擾
       * @return �󕠒l
       */
      int GetHungry() {
        return _hungry;
      }

    private:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      void SetParameters() override;
      /**
       * @brief  ��
       */
      void Hungry();
      /**
       * @brief  ��]
       */
      void Rotate();
      /**
       * @brief  �ړ�
       */
      void Move();
      /**
       * @brief  �U��
       */
      void Attack();
      /**
      /**
       * @brief  �ߐH
       */
      void Eat();

      int _hungry{ 0 };         //!< �󕠒l
      int _hungryCount{ 0 };    //!< �󕠃J�E���g
      int _eatTime{ 0 };        //!< �ߐH����
      float _speed{ 0.0f };     //!< �ړ����x
      //!< �v���C���[�̏��
      PlayerState _playerState{ PlayerState::Idle };
      //!< �O������
      AppMath::Vector4 _forward{ 0.0f, 0.0f, -1.0f };
      //!< �{�̋��̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
      //!< �U�����̏Փ˔���
      std::unique_ptr<Collision::CollisionSphere> _attack{ nullptr };
    };
  } // namespace Player
} // namespace Game