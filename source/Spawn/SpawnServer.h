/*****************************************************************//**
 * @file   SpawnServer.h
 * @brief  �I�u�W�F�N�g�̐������Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game{
  /**
   * @brief  �A�v���P�[�V����
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  �G
   */
  namespace Enemy {
    class EnemyTuna;
    class EnemyJerryFish;
  } // namespace Enemy
  /**
   * @brief  ����
   */
  namespace Spawn {
    namespace AppMath = AppFrame::Math;
    /**
     * @class SpawnServer
     * @brief �I�u�W�F�N�g�̐������Ǘ�����T�[�o�N���X
     */
    class SpawnServer {
    public:
      /**
       * @brief  �G���������i�[���铮�I�z��
       * @param  �G���ʔԍ�
       * @param  �G�����ʒu(�v���C���[���W�Ɖ��Z)
       * @param  �G��������
       */
      using EnemyTable = std::vector<std::tuple<int, AppMath::Vector4, AppMath::Vector4>>;
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      SpawnServer(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~SpawnServer();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  �X�V
       */
      void Process();

    private:
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�ɓo�^
       */
      void Register();

      int _spawnCount{ 0 };  //!< �����J�E���g
    };
  } // namespace Spawn
} // namespace Game