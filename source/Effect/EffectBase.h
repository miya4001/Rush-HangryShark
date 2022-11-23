/*****************************************************************//**
 * @file   EffectBase.h
 * @brief  �G�t�F�N�g�̊��N���X
 * 
 * @author �{�V�s��
 * @date   November 2022
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
   * @brief  �G�t�F�N�g
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  EffectBase
     * @brief  �G�t�F�N�g�̊��N���X
     */
    class EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectBase(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      virtual ~EffectBase();
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
       * @brief  �G�t�F�N�g��~
       */
      virtual void DeadEffect();
      /**
       * @brief  �G�t�F�N�g�Đ����̐ݒ�
       * @param  position �G�t�F�N�g�Đ��ʒu
       * @param  rotation �G�t�F�N�g�Đ�����
       */
      virtual void SetTransform(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S���
       *         false:����ł��Ȃ�
       */
      virtual bool IsDead() {
        return _effectState == EffectState::Dead;
      }

    protected:
      /**
       * @brief  �G�t�F�N�g�̏�Ԃ̗񋓌^�N���X
       */
      enum class EffectState {
        Active,  //!< �������
        Paused,  //!< ��~���
        Dead     //!< ���S���
      };
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      virtual void SetParameters();
      /**
       * @brief  �G�t�F�N�g�Đ�
       */
      virtual void PlayEffect();
      /**
       * @brief  �G�t�F�N�g�ǂݍ��݃n���h���̎擾
       * @param  key �G�t�F�N�g�n���h���L�[
       * @return �G�t�F�N�g�ǂݍ��݃n���h��
       */
      virtual int GetEffectLoadHandle(const std::string_view key);

      int _loadHandle{ -1 };  //!< �G�t�F�N�g�ǂݍ��݃n���h��
      int _playHandle{ -1 };  //!< �G�t�F�N�g�Đ��n���h��
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �G�t�F�N�g�̏��
      EffectState _effectState{ EffectState::Paused };
      //!< �ʒu
      AppMath::Vector4 _position;
      //!< ����
      AppMath::Vector4 _rotation;
    };
  } // namespace Effect
} // namespace Game