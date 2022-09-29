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
   * @brief  �I�u�W�F�N�g
   */
  namespace Object {
    class ObjectBase;
  } // namespace Object
  /**
   * @brief  �G
   */
  namespace Enemy {
    class EnemyTuna;
    class EnemyJerryfish;
  } // namespace Enemy
  /**
   * @brief  ����
   */
  namespace Spawn {
    class SpawnEnemy;
    /**
     * @class SpawnServer
     * @brief �I�u�W�F�N�g�̐������Ǘ�����T�[�o�N���X
     */
    class SpawnServer {
    public:
      /**
       * @brief  �G���������i�[���铮�I�z��
       */
      using EnemyTable = std::vector<SpawnEnemy>;
      /**
       * @brief  �������̃V�F�A�[�h�|�C���^���i�[���铮�I�z��
       */
      using SpawnMap = std::vector<std::shared_ptr<SpawnEnemy>>;
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
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
       * @brief  �������̓o�^
       * @param  key �������ɕR�Â��镶����
       * @param  enemy ������񂪊i�[���ꂽ�A�z�z��
       */
      void RegisterSpawnTable(const std::string_view key, const EnemyTable enemy);
      /**
       * @brief  �I�u�W�F�N�g�̐���
       * @param  key �����L�[ 
       */
      void Spawn(const std::string_view key);

    private:
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�ɓo�^
       */
      void RegisterObjctServer(std::shared_ptr<Object::ObjectBase> object);
      /**
       * @brief  �������̍폜
       * @param  key �����L�[
       */
      void DeleteSpawnTable(const std::string_view key);
      /**
       * @brief  �}�O���̐���
       * @param  spawn �������
       * @return �}�O���̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<Enemy::EnemyTuna> EnemyTuna(SpawnEnemy& spawn) const;
      /**
       * @brief  �N���Q�̐���
       * @param  spawn �������
       * @return �N���Q�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<Enemy::EnemyJerryfish> EnemyJerryfish(SpawnEnemy& spawn) const;

      int _spawnCount{ 0 };  //!< �����J�E���g
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �������W�X�g��
      std::unordered_map<std::string, SpawnMap> _spawnRegistry;
    };
  } // namespace Spawn
  /**
   * @brief  �����ԍ�
   */
  namespace SpawnNumber {
    constexpr int Tuna = 1;       //!< �}�O��
    constexpr int Jerryfish = 2;  //!< �N���Q
  }
} // namespace Game