/*****************************************************************//**
 * @file   SpawnServer.cpp
 * @brief  �I�u�W�F�N�g�̐������Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "SpawnServer.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "SpawnEnemy.h"
#include "../Enemy/EnemyTuna.h"
#include "../Enemy/EnemyJerryfish.h"

namespace Game {
  namespace Spawn {
    SpawnServer::SpawnServer(Application::ApplicationMain& app) : _app(app) {
      // ���W�X�g���̏�����
      _spawnRegistry.clear();
    }

    SpawnServer::~SpawnServer() {

    }

    void SpawnServer::Release() {
      // ���W�X�g������̏ꍇ���f
      if (_spawnRegistry.empty()) {
        return;
      }
      // �������̑S���
      for (auto&& [key, map] : _spawnRegistry) {
        map.clear();
      }
      // ���W�X�g���̉��
      _spawnRegistry.clear();
    }

    void SpawnServer::RegisterSpawnTable(const std::string_view key, const EnemyTable enemy) {
      // �������̊m�F
      if (enemy.empty()) {
#ifdef _DEBUG
        throw ("SpawnServer:������񂪋�ł�\n");
#endif
        return;  // ������񂪋�
      }
      // �L�[���o�^�ς݂̏ꍇ
      if (_spawnRegistry.contains(key.data())) {
        // �d�����Ă��鐶�����̍폜
        DeleteSpawnTable(key);
      }
      // �������̃V�F�A�[�h�|�C���^�̓��I�z��
      SpawnMap spawnMap;
      // �G�̐������̃V�F�A�[�h�|�C���^���i�[
      for (auto&& value : enemy) {
        spawnMap.emplace_back(std::make_shared<SpawnEnemy>(value));
      }
      // ���W�X�g���ɓo�^����
      _spawnRegistry.emplace(key.data(), spawnMap);
    }

    void SpawnServer::Spawn(const std::string_view key) {
      // ����������ɃI�u�W�F�N�g�𐶐����o�^
      for (auto&& spawn : _spawnRegistry.at(key.data()))
        // ���ʔԍ����画��
        switch (spawn->GetNumber()) {
        // �}�O��
        case SpawnNumber::Tuna:
          RegisterObjctServer(EnemyTuna(*spawn.get()));
          break;
        // �N���Q
        case SpawnNumber::Jerryfish:
          RegisterObjctServer(EnemyJerryfish(*spawn.get()));
          break;
        // �Y���Ȃ�
        default:
#ifdef _DEBUG
          throw ("SpawnServer:���ʔԍ����s���ł�\n");
#endif
          break;
        }
    }

    void SpawnServer::RegisterObjctServer(std::shared_ptr<Object::ObjectBase> object) {
      // �I�u�W�F�N�g�T�[�o�ւ̓o�^���s��
      _app.GetObjectServer().RegisterObject(std::move(object));
    }

    void SpawnServer::DeleteSpawnTable(const std::string_view key) {
      // �������̎��o��
      auto&& map = _spawnRegistry.at(key.data());
      // �������̍폜
      map.clear();
      // ���W�X�g������폜����
      _spawnRegistry.erase(key.data());
    }

    std::shared_ptr<Enemy::EnemyTuna> SpawnServer::EnemyTuna(SpawnEnemy& spawn) const {
      // �}�O���̐���
      auto tuna = std::make_shared<Enemy::EnemyTuna>(_app);
      // �X�|�[�����̐ݒ�
      auto [position, rotation] = spawn.GetTransform();
      tuna->Spawn(position, rotation);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(tuna);
    }

    std::shared_ptr<Enemy::EnemyJerryfish> SpawnServer::EnemyJerryfish(SpawnEnemy& spawn) const {
      // �N���Q�̐���
      auto jerryfish = std::make_shared<Enemy::EnemyJerryfish>(_app);
      // �X�|�[�����̐ݒ�
      auto [position, rotation] = spawn.GetTransform();
      jerryfish->Spawn(position, rotation);
      // ���������V�F�A�[�h�|�C���^��Ԃ�
      return std::move(jerryfish);
    }
  } // namespace Spawn
} // namespace Game