/*****************************************************************//**
 * @file   SpawnComponent.h
 * @brief  �����R���|�[�l���g�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once

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
   * @brief  ����
   */
  namespace Spawn {
    /**
     * @class  SpawnComponent
     * @brief  �����R���|�[�l���g�N���X
     */
    class SpawnComponent {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      SpawnComponent(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~SpawnComponent();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  �������̐ݒ�
       */
      void SetSpawn();

    private:
      /**
       * @brief  �����^�C�~���O�̊Ǘ�
       * @return true:�������s��
       *         false:�������s��Ȃ�
       */
      bool SpawnTiming();
      /**
       * @brief  �G�̐���
       */
      void SpawnEnemy();
      /**
       * @brief  �G�������̓o�^
       */
      void RegisterEnemyTable();

      int _spawnCount{ 0 };       //!< �����J�E���g
      bool _isRegister{ false };  //!< �o�^�t���O
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
    };
  } // namespace Spawn
} // namespace Game