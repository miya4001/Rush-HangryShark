/*****************************************************************//**
 * @file   UITimer.cpp
 * @brief  UI�^�C�}�[�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "UITimer.h"
#include "../Application/ApplicationMain.h"

namespace {
  // �^�C�}�[�e��萔
  constexpr int TimerSecondsInit = 180;  //!< �����^�C�}�[�b
  constexpr int FrameCountMax = 60;      //!< �t���[���J�E���g���
  constexpr int SecondsMax = 60;         //!< �b���
  constexpr int TenPlace = 10;           //!< �\�̈�
}

namespace Game {
  namespace UI {
    UITimer::UITimer(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UITimer::Init() {
      // �ϐ�������
      _timerSeconds = TimerSecondsInit;
      // �^�C�}�[�b�ϊ�
      TimerConversion();
      return true;
    }

    void UITimer::Process() {
      // �t���[���J�E���g������̏ꍇ
      if (FrameCountMax <= _frameCount) {
        // �t���[���J�E���g������
        _frameCount = 0;
        // ��b�o��
        OneSecondPass();
        // �^�C�}�[�b�ϊ�
        TimerConversion();
        return;
      }
      // �t���[���J�E���g�𑝂₷
      ++_frameCount;
    }

    void UITimer::Draw() const {
      // �f�o�b�O���`��
#ifdef _DEBUG
      // �^�C�}�[
      DrawFormatString(1500, 100, GetColor(255, 255, 255), "%d : %d %d", _onePlaceMinutes, _tenPlaceSeconds, _onePlaceSeconds);
#endif
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