/*****************************************************************//**
 * @file   ModeAMG.cpp
 * @brief  モードAMGクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "ModeAMG.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"

namespace {
  // 画像ハンドルキー
  constexpr auto UnderSea = "underSea";  //!< 海中
  constexpr auto AMGLogo = "amg";        //!< AMG
  // 各種定数
  constexpr int MaxCount = 30;  //!< カウント上限
}

namespace Game {
  namespace Mode {
    ModeAMG::ModeAMG(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeAMG::Init() {
      return true;
    }

    void ModeAMG::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(UnderSea);
      _amg = _app.GetGraphicLoadServer().GetGraphicHandle(AMGLogo);
    }

    void ModeAMG::Exit() {

    }

    void ModeAMG::Process() {
      // カウントを増やす
      ++_modeCount;
      // モード切り替え
      ChangeMode();
    }

    void ModeAMG::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _sea, true);
      DrawGraph(0, 0, _amg, true);
    }

    void ModeAMG::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap {
        {UnderSea, "resource/Graphic/BackGround/UnderSea.png"},
        {AMGLogo, "resource/Graphic/BackGround/AMG.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeAMG::ChangeMode() {
      // カウントが上限未満の場合中断
      if (_modeCount <= MaxCount) {
        return;
      }
      // モードタイトルの登録
      _app.GetModeServer().AddMode(Title, std::make_shared<Mode::ModeTitle>(_appMain));
      // モードタイトル遷移
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespace Mode
} // Game