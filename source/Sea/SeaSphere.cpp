/*****************************************************************//**
 * @file   SeaSphere.cpp
 * @brief  �C���w�i�N���X
 * 
 * @author �{�V�s��
 * @date   August 2022
 *********************************************************************/
#include "SeaSphere.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"

namespace {
  // �C���w�i�e��萔
  constexpr auto Modelhandle = "sea";  //!< ���f���n���h���L�[
}

namespace Game {
  namespace Sea {
    SeaSphere::SeaSphere(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool SeaSphere::Init() {
      // �p�����[�^�̐ݒ�
      SetParameters();
      return true;
    }

    void SeaSphere::Process() {
      // �I�u�W�F�N�g�̃R�s�[
      auto objects = _app.GetObjectServer().GetObjects();
      // �v���C���[��T��
      for (auto obj : objects) {
        if (obj->GetId() == ObjectId::Player) {
          // �v���C���[�̃��[�J�����W�ɍX�V
          _position = obj->GetPosition();
          break;
        }
      }
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���f���̃��[���h���W�̐ݒ�
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void SeaSphere::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetModelHandle(Modelhandle);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(1.0f);
    }
  } // namespace Sea
} // namespace Game