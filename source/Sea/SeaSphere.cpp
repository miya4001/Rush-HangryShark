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
#include "../Player/PlayerShark.h"

namespace {
  // �C���w�i�e��萔
  constexpr auto Modelhandle = "sea";  //!< ���f���n���h���L�[
  constexpr float Scale = 0.5f;        //!< �g�嗦
  constexpr float Radius = 2500.0f;    //!< �����a
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
      // �v���C���[�̃R�s�[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // �v���C���[�̃��[�J�����W�ɍX�V
      _position = player->GetPosition();
      // ���̃��[�J�����W�̐ݒ�
      _sphere->SetPosition(_position);
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���f���̃��[���h���W�̐ݒ�
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void SeaSphere::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetModelHandle(Modelhandle);
      // �e��p�����[�^�̐ݒ�
      _objectId = ObjectId::Sea;
      _scale.Fill(Scale);
      // ���̏Փ˔���̐ݒ�
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, _position, Radius);
    }
  } // namespace Sea
} // namespace Game