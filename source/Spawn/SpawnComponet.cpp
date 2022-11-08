/*****************************************************************//**
 * @file   SpawnComponet.cpp
 * @brief  �����R���|�[�l���g�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "SpawnComponent.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"
#include "SpawnServer.h"
#include "SpawnEnemy.h"

namespace {
  // �����e��萔
  constexpr int Timing = 180;  //!< �����^�C�~���O
  // �����L�[
  constexpr auto Start = "start";    //!< �J�n�e�[�u��
  constexpr auto EnemyA = "enemyA";  //!< �e�[�u��A
  constexpr auto EnemyB = "enemyB";  //!< �e�[�u��B
  constexpr auto EnemyC = "enemyC";  //!< �e�[�u��C
}

namespace Game{
  namespace Spawn {
    SpawnComponent::SpawnComponent(Application::ApplicationMain& app) : _app(app) {

    }

    SpawnComponent::~SpawnComponent() {
      // �����T�[�o�̉��
      _app.GetSpawnServer().Release();
    }

    void SpawnComponent::Release() {
      // �ϐ�������
      _spawnCount = 0;
    }

    void SpawnComponent::Process() {
      // �����^�C�~���O�̊Ǘ�
      if (!SpawnTiming()) {
        return;
      }
      // �G�̐���
      SpawnEnemy();
    }

    void SpawnComponent::SetSpawn() {
      // �C���w�i�̐���
      auto sea = std::make_shared<Sea::SeaSphere>(_app);
      _app.GetObjectServer().RegisterObject(sea, true);
      // �v���C���[(�T��)�̐���
      auto player = std::make_shared<Player::PlayerShark>(_app);
      _app.GetObjectServer().RegisterObject(player, true);
      // �G�������̓o�^
      RegisterEnemyTable();
      // �J�n�e�[�u������
      _app.GetSpawnServer().Spawn(Start);
    }

    bool SpawnComponent::SpawnTiming() {
      // �����J�E���g�������^�C�~���O�ȉ��̏ꍇ
      if (_spawnCount <= Timing) {
        // �����J�E���g�𑝂₷
        ++_spawnCount;
        // �������s��Ȃ�
        return false;
      }
      // �����J�E���g������
      _spawnCount = 0;
      // �������s��
      return true;
    }

    void SpawnComponent::SpawnEnemy() {
      // ����
      _app.GetSpawnServer().Spawn(EnemyA);
    }

    void SpawnComponent::RegisterEnemyTable() {
      // �o�^�ς݂̏ꍇ���f
      if (_isRegister) {
        return;
      }
      // �J�n�e�[�u��
      const SpawnServer::EnemyTable start{
        {SpawnNumber::Tuna, {0.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {0.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {1000.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��A
      const SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Tuna, {1000.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��B
      const SpawnServer::EnemyTable enemyB{
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��C
      const SpawnServer::EnemyTable enemyC{
        {SpawnNumber::Shrimp, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �������̓o�^
      _app.GetSpawnServer().RegisterSpawnTable(Start, start);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyA, enemyA);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyB, enemyB);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyC, enemyC);
      // �o�^����
      _isRegister = true;
    }
  } // namespace Spawn
} // namespace Game