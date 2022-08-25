/*****************************************************************//**
 * @file   PlayerShark.h
 * @brief  �v���C���[(�T��)�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"

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
        Idle,  //!< �ҋ@
        Swim,  //!< �ړ�
        Rush,  //!< �ˌ�
        Eat,   //!< �ߐH
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

      void Draw() const override;

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
       * @brief  �ړ�
       */
      void Swim();
      /**
       * @brief  �ڐG
       */
      void Hit();
      /**
       * @brief  �ߐH
       */
      void Eat();
      /**
       * @brief  �ړ��ʂ̎Z�o
       * @return �ړ���
       */
      AppMath::Vector4 Move();

      int _hungry{ 0 };         //!< �󕠒l
      int _hungryCount{ 0 };    //!< �󕠃J�E���g
      int _eatTime{ 0 };        //!< �ߐH����
      float _speed{ 0.0f };     //!< �ړ����x
      bool _isEating{ false };  //!< �ߐH��
      //!< �O������
      AppMath::Vector4 _forward{ 0.0f, 0.0f, -1.0f };
      //!< �v���C���[�̏��
      PlayerState _playerState{ PlayerState::Idle };
      //!< �O�t���[���̃v���C���[�̏��
      PlayerState _oldPlayerState{ PlayerState::Idle };
    };
  } // namespace Player
} // namespace Game