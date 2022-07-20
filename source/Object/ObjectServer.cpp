/*****************************************************************//**
 * @file   ObjectServer.cpp
 * @brief  �I�u�W�F�N�g���Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"

namespace Game {
  namespace Object {
    ObjectServer::ObjectServer() {
      // ���W�X�g���̏�����
      _objectRegistry.clear();
      _addObjectRegistry.clear();
    }

    ObjectServer::~ObjectServer() {

    }

    void ObjectServer::Release() {
      // ���W�X�g���̉��
      DeleteObjects(_objectRegistry);
      DeleteObjects(_addObjectRegistry);
    }

    void ObjectServer::Process() {
      // �ǉ��\�񂳂�Ă���I�u�W�F�N�g������ꍇ
      if (!_addObjectRegistry.empty()) {
        // ���W�X�g���ɃI�u�W�F�N�g��ǉ�
        AddObjects();
      }
      // ���W�X�g�����̃I�u�W�F�N�g�̍X�V
      for (auto object : _objectRegistry) {
        // �I�u�W�F�N�g�����S��ԂłȂ��ꍇ�X�V
        if (!object->IsDead()) {
          object->Process();
        }
      }
      // �s�v�ɂȂ����I�u�W�F�N�g���폜
      std::erase_if(_objectRegistry, [](auto&& obj) {return obj->IsDead(); });
    }

    void ObjectServer::Draw() const {
      // ���W�X�g�����̃I�u�W�F�N�g�̕`��
      for (auto&& objct : _objectRegistry) {
        objct->Draw();
      }
    }

    void ObjectServer::RegisterObject(std::shared_ptr<ObjectBase> object) {
      // �I�u�W�F�N�g�̎擾�Ɏ��s�����ꍇ�G���[
      if (object == nullptr) {
#ifdef _DEBUG
        throw ("�I�u�W�F�N�g��nullptr�ł�");
#endif
        return; // �L�[���s��
        // �ǉ��\��
        _addObjectRegistry.emplace_back(std::move(object));
      }
    }

    void ObjectServer::AddObjects() {
      // �I�u�W�F�N�g�����W�X�g���̖����ɒǉ�
      for (auto&& obj : _addObjectRegistry) {
        _objectRegistry.emplace_back(std::move(obj));
      }
      // �ǉ��\�񃌃W�X�g���̉��
      _addObjectRegistry.clear();
    }

    void ObjectServer::DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& registry) {
      // ���W�X�g������̏ꍇ���f
      if (registry.empty()) {
        return;
      }
      // �o�^�I�u�W�F�N�g�̑S���
      for (auto&& obj : registry) {
        // �������
        obj.reset();
      }
      // ���W�X�g���̉��
      registry.clear();
    }
  } // namespace Object
} // namespace Game