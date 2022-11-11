/*****************************************************************//**
 * @file   UITimer.cpp
 * @brief  UI�^�C�}�[�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "UITimer.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �^�C�}�[�e��萔
  constexpr int TimerSecondsInit = 180;   //!< �����^�C�}�[�b
  constexpr int FrameCountMax = 60;       //!< �t���[���J�E���g���
  constexpr int SecondsMax = 60;          //!< �b���
  constexpr int TenPlace = 10;            //!< �\�̈�
  constexpr int ColonX = 1700;            //!< �R����x���W
  constexpr int OnePlaceMinutesX = 1630;  //!< ��(��̈�)x���W
  constexpr int TenPlaceSecondsX = 1730;  //!< �b(�\�̈�)x���W
  constexpr int OnePlaceSecondsX = 1800;  //!< �b(��̈�)x���W
  constexpr int DrawY = 25;               //!< �`��y���W
}

namespace Game {
  namespace UI {
    UITimer::UITimer(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UITimer::Init() {
      // �摜�n���h���̐ݒ�
      _timerNumber = _app.GetGraphicLoadServer().GetDivGraphicHandles(GraphicKey::TimerNumber);
      _colon = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::TimerColon);
      // �ϐ�������
      _timerSeconds = TimerSecondsInit;
      // �^�C�}�[�b�ϊ�
      TimerConversion();
      return true;
    }

    void UITimer::Process() {
      // �^�C�}�[�b���s�����ꍇ
      if (_timerSeconds <= 0) {
        // �Q�[���N���A
        _app.SetGameClear(true);
        // �z�C�b�X��SE�̍Đ�
        _app.GetSoundComponent().PlayBackGround(SoundKey::Whistle);
        return;
      }
      // �t���[���J�E���g����
      _frameCount = AppFrame::Math::Utility::IncrementCount(_frameCount, FrameCountMax);
      // �t���[���J�E���g������̏ꍇ
      if (_frameCount == 0) {
        // ��b�o��
        OneSecondPass();
        // �^�C�}�[�b�ϊ�
        TimerConversion();
      }
    }

    void UITimer::Draw() const {
      // �R�����`��
      DrawGraph(ColonX, DrawY, _colon, true);
      // �^�C�}�[�����`��
      DrawGraph(OnePlaceMinutesX, DrawY, _timerNumber.at(_onePlaceMinutes), true);
      DrawGraph(TenPlaceSecondsX, DrawY, _timerNumber.at(_tenPlaceSeconds), true);
      DrawGraph(OnePlaceSecondsX, DrawY, _timerNumber.at(_onePlaceSeconds), true);
    }

    void UITimer::OneSecondPass() {
      // �^�C�}�[�b�����炷
      --_timerSeconds;
    }

    void UITimer::TimerConversion() {
      // ��(��̈�)�����߂�
      _onePlaceMinutes = _timerSeconds / SecondsMax;
      // �b
      int seconds = _timerSeconds % SecondsMax;
      // �b(�\�̈�)�����߂�
      _tenPlaceSeconds = seconds / TenPlace;
      // �b(��̈�)�����߂�
      _onePlaceSeconds = seconds % TenPlace;
    }
  } // namespace UI
} // namespace Game