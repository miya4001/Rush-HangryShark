/*****************************************************************//**
 * @file   UIRadar.cpp
 * @brief  UI���[�_�[�N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
 *********************************************************************/
#include "UIRadar.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  constexpr int PositionScale = 12;  //!< ���W�k��
  constexpr int PlayerX = 250;       //!< �v���C���[x���W
  constexpr int PlayerY = 850;       //!< �v���C���[y���W
  constexpr int Radius = 3;          //!< �~���a
}

namespace Game {
  namespace UI {
    UIRadar::UIRadar(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UIRadar::Init() {
      // �摜�n���h���̐ݒ�
      _shark = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Shark);
      // ��������
      ResponseClear();
      return true;
    }

    void UIRadar::Process() {
      // ��������
      ResponseClear();
      // ����
      Input();
      // �`�悵�Ȃ��ꍇ���f
      if (!_draw) {
        return;
      }
      // �v���C���[�̃R�s�[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // �v���C���[�̃��[�J�����W
      auto playerPosition = player->GetPosition();
      // �v���C���[�̌���
      auto playerRotation = player->GetRotation();
      // �p�x(���W�A��)�̐ݒ�
#ifdef _DEBUG
      _angle = static_cast<double>(AppFrame::Math::Utility::DegreeToRadian(playerRotation.GetY()));
#else
      _angle = static_cast<double>(playerRotation.GetY());
#endif
      // �I�u�W�F�N�g�̃R�s�[
      auto objects = _app.GetObjectServer().GetObjects();
      // �G��T��
      for (auto&& object : objects) {
        if (object->GetId() != Object::ObjectBase::ObjectId::Enemy) {
          continue;
        }
        // �G�̃��[�J�����W
        auto enemyPosition = object->GetPosition();
        // �G-�v���C���[�ԋ���
        auto distance = enemyPosition - playerPosition;
        // �^�ϊ�
        auto distanceX = static_cast<int>(distance.GetX());
        auto distanceZ = static_cast<int>(distance.GetZ());
        // �����k��
        distanceX = distanceX / PositionScale;
        distanceZ = distanceZ / PositionScale;
        // �`����W(�`��̓s���Ŕ��])
        int drawX = PlayerX - distanceX;
        int drawY = PlayerY + distanceZ;
        // �`����W�ɓo�^����
        _drawPosition.emplace_back(drawX, drawY);
      }
    }

    void UIRadar::Draw() const {
      // �`�悵�Ȃ��ꍇ���f
      if (!_draw) {
        return;
      }
      // ���u���w�i�~�`��
      DrawCircle(PlayerX, PlayerY, 250, GetColor(0, 0, 0));
      DrawCircle(PlayerX, PlayerY, 100, GetColor(0, 255, 0), false);
      DrawCircle(PlayerX, PlayerY, 200, GetColor(0, 255, 0), false);
      // �T���`��
      DrawRotaGraph(PlayerX, PlayerY, 0.5, _angle, _shark, true);
      // �G�~�`��
      for (auto&& [x, y] : _drawPosition) {
        DrawCircle(x, y, Radius, GetColor(255, 0, 0));
      }
    }

    void UIRadar::ResponseClear() {
      // �`����W���
      _drawPosition.clear();
    }

    void UIRadar::Input() {
      // ���͏�Ԃ̎擾
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // X�{�^��(�g���K)�̓��͏��
      bool buttonX = xJoypad.GetButton(XINPUT_BUTTON_X, AppFrame::Input::InputTrigger);
      // ���͂�����ꍇ
      if (buttonX) {
        // �`��t���O���]
        _draw = !_draw;
      }
    }
  } // namespace UI
} // namespace Game