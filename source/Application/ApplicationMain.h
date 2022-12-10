/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  �A�v���P�[�V�������C���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �I�u�W�F�N�g
   */
  namespace Object {
    class ObjectServer;
  } // namespace Object
  /**
   * @brief  �J����
   */
  namespace Camera {
    class Camera;
  } // namespace Camera
  /**
   * @brief  ����
   */
  namespace Spawn {
    class SpawnServer;
  } // namespace Spawn
  /**
   * @brief  �G�t�F�N�g
   */
  namespace Effect {
    class EffectServer;
  } // namespace Effect
  /**
   * @brief  ���U���g
   */
  namespace Result {
    class ResultComponent;
  } // namespace Result
  /**
   * @brief  �A�v���P�[�V����
   */
  namespace Application {
    /**
     * @class  ApplicationMain
     * @brief  �A�v���P�[�V�������C���N���X
     */
    class ApplicationMain : public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      ApplicationMain();
      /**
       * @brief  �A�v���P�[�V�����̏�����
       * @return true:����������
       *         false:���������s
       */
      bool Init() override;
      /**
       * @brief  �Q�[���I�[�o�[�t���O�̐ݒ�
       * @param  flag �t���O
       */
      inline void SetGameOver(const bool flag) {
        _isGameOver = flag;
      }
      /**
       * @brief  �Q�[���N���A�t���O�̐ݒ�
       * @param  flag �t���O
       */
      inline void SetGameClear(const bool flag) {
        _isGameClear = flag;
      }
      /**
       * @brief  �Q�[���I�[�o�[�t���O�̎擾
       * @return �Q�[���I�[�o�[�t���O
       */
      inline bool GetGameOver() const {
        return _isGameOver;
      }
      /**
       * @brief  �Q�[���N���A�t���O�̎擾
       * @return �Q�[���N���A�t���O
       */
      inline bool GetGameClear() const {
        return _isGameClear;
      }
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�̎擾
       * @return �I�u�W�F�N�g�T�[�o�̎Q��
       */
      Object::ObjectServer& GetObjectServer();
      /**
       * @brief  �J�����̎擾
       * @return �J�����̎Q��
       */
      Camera::Camera& GetCamera();
      /**
       * @brief  �����T�[�o�̎擾
       * @return �����T�[�o�̎Q��
       */
      Spawn::SpawnServer& GetSpawnServer();
      /**
       * @brief  �G�t�F�N�g�T�[�o�̎擾
       * @return �G�t�F�N�g�T�[�o�̎Q��
       */
      Effect::EffectServer& GetEffectServer();
      /**
       * @brief  ���U���g�R���|�[�l���g�̎擾
       * @return ���U���g�R���|�[�l���g�̎Q��
       */
      Result::ResultComponent& GetResultComponent();

    private:
      bool _isGameOver{ false };   //!< �Q�[���I�[�o�[�t���O
      bool _isGameClear{ false };  //!< �Q�[���N���A�t���O
      //!< �I�u�W�F�N�g�T�[�o
      std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
      //!< �J����
      std::unique_ptr<Camera::Camera> _camera{ nullptr };
      //!< �����T�[�o
      std::unique_ptr<Spawn::SpawnServer> _spawnServer{ nullptr };
      //!< �G�t�F�N�g�T�[�o
      std::unique_ptr<Effect::EffectServer> _effectServer{ nullptr };
      //!< ���U���g�R���|�[�l���g
      std::unique_ptr<Result::ResultComponent> _resultComponent{ nullptr };
    };
  } // namespace Application
} // namespace Game