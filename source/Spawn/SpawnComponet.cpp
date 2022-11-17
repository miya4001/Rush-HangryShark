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
  constexpr int SpawnCountMax = 180;  //!< �����J�E���g���
  constexpr int RandSpawnkeyMax = 6;  //!< �����_�������L�[���
  // ���ꐶ���L�[
  constexpr auto Start = "start";    //!< �J�n�e�[�u��
  constexpr auto Error = "error";    //!< �G���[
  // �����_�������L�[
  constexpr auto EnemyA = "enemyA";  //!< �e�[�u��A
  constexpr auto EnemyB = "enemyB";  //!< �e�[�u��B
  constexpr auto EnemyC = "enemyC";  //!< �e�[�u��C
  constexpr auto EnemyD = "enemyD";  //!< �e�[�u��D
  constexpr auto EnemyE = "enemyE";  //!< �e�[�u��E
  constexpr auto EnemyF = "enemyF";  //!< �e�[�u��F
} // namespace

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
      _spawnEnemy = 0;
    }

    void SpawnComponent::Process() {
      // �����^�C�~���O�̊Ǘ�
      if (SpawnTiming()) {
        // �G�̐���
        SpawnEnemy();
      }
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
      // �J�E���g����
      _spawnCount = AppMath::Utility::IncrementCount(_spawnCount, SpawnCountMax);
      // �����J�E���g������̏ꍇ
      if (_spawnCount == 0) {
        // �������s��
        return true;
      }
      // �������s��Ȃ�
      return false;
    }

    void SpawnComponent::SpawnEnemy() {
      // �����L�[�̑I��
      auto key = ChooseSpawnKey();
      // ����
      _app.GetSpawnServer().Spawn(key);
      // �G�������𑝂₷
      ++_spawnEnemy;
    }

    std::string_view SpawnComponent::ChooseSpawnKey() {
      // �󐶐��L�[
      std::string_view key = "";
      // ����
      int rand = std::rand();
      // ��]�v�Z
      int remainder = rand % RandSpawnkeyMax;
      // ��]�ɍ��킹�Đ����L�[�̑I��
      switch (remainder) {
      case 0:
        key = EnemyA;
        break;
      case 1:
        key = EnemyB;
        break;
      case 2:
        key = EnemyC;
        break;
      case 3:
        key = EnemyD;
        break;
      case 4:
        key = EnemyE;
        break;
      case 5:
        key = EnemyF;
        break;
      default:
        break;
      }
      return key;
    }

    void SpawnComponent::RegisterEnemyTable() {
      // �o�^�ς݂̏ꍇ���f
      if (_isRegister) {
        return;
      }
      // �J�n�e�[�u��
      const SpawnServer::EnemyTable start{
        {SpawnNumber::Shrimp, {500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-500.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {0.0f, 0.0f, 1500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {0.0f, 0.0f, -1500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {1500.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-1500.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��A
      const SpawnServer::EnemyTable enemyA{
        {SpawnNumber::Shrimp, {750.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {750.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-750.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-750.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
      };
      // �e�[�u��B
      const SpawnServer::EnemyTable enemyB{
        {SpawnNumber::Tuna, {1000.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {1000.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-1000.0f, 0.0f, -500.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��C
      const SpawnServer::EnemyTable enemyC{
        {SpawnNumber::Jerryfish, {0.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��D
      const SpawnServer::EnemyTable enemyD{
        {SpawnNumber::Shrimp, {0.0f, 0.0f, -1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {500.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Shrimp, {-500.0f, 0.0f, 1000.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��E
      const SpawnServer::EnemyTable enemyE{
        {SpawnNumber::Tuna, {0.0f, 0.0f, -750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Tuna, {-500.0f, 0.0f, 500.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �e�[�u��F
      const SpawnServer::EnemyTable enemyF{
        {SpawnNumber::Jerryfish, {250.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}},
        {SpawnNumber::Jerryfish, {-250.0f, 0.0f, 750.0f}, {0.0f, 0.0f, 0.0f}}
      };
      // �������̓o�^
      _app.GetSpawnServer().RegisterSpawnTable(Start, start);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyA, enemyA);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyB, enemyB);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyC, enemyC);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyD, enemyD);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyE, enemyE);
      _app.GetSpawnServer().RegisterSpawnTable(EnemyF, enemyF);
      // �o�^����
      _isRegister = true;
    }
  } // namespace Spawn
} // namespace Game