/*****************************************************************//**
 * @file   UIServer.cpp
 * @brief  UI���Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "UIServer.h"
#include "UIBase.h"

namespace Game {
  namespace UI {
    UIServer::UIServer() {
      // ���W�X�g���̏�����
      _uiRegistry.clear();
    }

    UIServer::~UIServer() {

    }

    void UIServer::Release() {
      // ���W�X�g������̏ꍇ���f
      if (_uiRegistry.empty()) {
        return;
      }
      // �o�^UI�̑S���
      for (auto&& ui : _uiRegistry) {
        // �������
        ui.reset();
      }
      // ���W�X�g���̉��
      _uiRegistry.clear();
    }

    void UIServer::Process() {
      // ���W�X�g������UI�̍X�V
      for (auto&& ui : _uiRegistry) {
        ui->Process();
      }
    }

    void UIServer::Draw() const {
      // ���W�X�g������UI�̍X�V
      for (auto&& ui : _uiRegistry) {
        ui->Draw();
      }
    }

    void UIServer::RegisterUI(std::shared_ptr<UIBase> ui) {
      // UI�̎擾�Ɏ��s�����ꍇ�G���[
      if (ui == nullptr) {
#ifdef _DEBUG
        throw ("UIServer:UI��nullptr�ł�");
#endif
        return; // �L�[���s��
      }
      // ���W�X�g���ɓo�^����
      _uiRegistry.emplace_back(std::move(ui));
    }
  } // namespace UI
} // namespace Game