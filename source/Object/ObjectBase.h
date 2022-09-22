/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  �I�u�W�F�N�g�̊��N���X
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
   * @brief  �A�v���P�[�V����
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  �I�u�W�F�N�g
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ObjectBase
     * @brief �I�u�W�F�N�g�̊��N���X
     */
    class ObjectBase {
    public:
      /**
       * @brief  �I�u�W�F�N�g�̎��ʂ̗񋓌^�N���X
       */
      enum class ObjectId {
        Object,  //!< �I�u�W�F�N�g
        Player,  //!< �v���C���[
        Enemy,   //!< �G
        Sea      //!< �C
      };
      /**
       * @brief  �I�u�W�F�N�g�̏�Ԃ̗񋓌^�N���X
       */
      enum class ObjectState {
        Active,  //!< �������
        Pause,   //!< �ꎞ��~���
        Dead     //!< ���S���
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ObjectBase(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      virtual ~ObjectBase();
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
      /**
       * @brief  ���S
       */
      virtual void Dead();
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S���
       *         false:����ł��Ȃ�
       */
      virtual bool IsDead() const;
      /**
       * @brief  ���ʂ̎擾
       * @return ����
       */
      ObjectId GetId() const {
        return _objectId;
      }
      /**
       * @brief  ��Ԃ̎擾
       * @return ���
       */
      ObjectState GetState() const {
        return _objectState;
      }
      /**
       * @brief  ���[���h���W�s��̎擾
       * @return ���[���h���W�s��
       */
      AppMath::Matrix44 GetMatrix() const {
        return _world;
      }
      /**
       * @brief  ���[�J�����W�̎擾
       * @return ���[�J�����W
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  �����̎擾
       * @return ����
       */
      AppMath::Vector4 GetRotation() const {
        return _rotation;
      }

    protected:
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      virtual void SetParameters();
      /**
       * @brief  ���[���h���W�̍X�V
       */
      void WorldMatrix();

      int _modelHandle{ 0 };  //!< ���f���n���h��
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �I�u�W�F�N�g�̎���
      ObjectId _objectId{ ObjectId::Object };
      //!< �I�u�W�F�N�g�̏��
      ObjectState _objectState{ ObjectState::Active };
      //!< ���[���h���W
      AppMath::Matrix44 _world;
      //!< ���[�J�����W
      AppMath::Vector4 _position;
      //!< ����
      AppMath::Vector4 _rotation;
      //!< �g�嗦
      AppMath::Vector4 _scale;
    };
  } // namespace Object
} // namespace Game