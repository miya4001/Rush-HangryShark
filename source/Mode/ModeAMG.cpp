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
#include "../ConstLoadResourceKey.h"

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
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::UnderSea);
      _amg = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::AMG);
    }

    void ModeAMG::Exit() {

    }

    void ModeAMG::Process() {
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
        {GraphicKey::UnderSea, "resource/Graphic/BackGround/UnderSea.png"},
        {GraphicKey::AMG, "resource/Graphic/BackGround/AMG.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeAMG::ChangeMode() {
      // モードタイトルの登録
      _app.GetModeServer().AddMode(Title, std::make_shared<Mode::ModeTitle>(_appMain));
      // モードタイトル遷移
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespace Mode
} // Game