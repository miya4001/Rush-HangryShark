/*****************************************************************//**
 * @file   SpawnComponet.cpp
 * @brief  �����R���|�[�l���g�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "SpawnComponent.h"
#include "../Application/ApplicationMain.h"
#include "SpawnServer.h"
#include "SpawnEnemy.h"

namespace {
  // �����e��萔
  constexpr int Timing = 180;  //!< �����^�C�~���O
  // �����L�[
  constexpr auto EnemyA = "enemyA";
  constexpr auto EnemyB = "enemyB";
}

namespace Game{
  namespace Spawn {
    SpawnComponent::SpawnComponent(Application::ApplicationMain& app) : _app(app) {

    }

    SpawnComponent::~SpawnComponent() {

    }

    void SpawnComponent::Release() {
      // �����J�E���g������
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

    void SpawnComponent::SetSpawnTable() {
      // �G�������
      const SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Tuna, {-500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}}
      };
      const SpawnServer::EnemyTable enemyB{
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �������̓o�^
      _app.GetSpawnServer().RegisterSpawnTable(EnemyA, enemyA);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyB, enemyB);
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
  } // namespace Spawn
} // namespace Game