/*****************************************************************//**
 * @file   UIServer.cpp
 * @brief  UIを管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "UIServer.h"
#include "UIBase.h"

namespace Game {
  namespace UI {
    UIServer::UIServer() {
      // レジストリの初期化
      _uiRegistry.clear();
    }

    UIServer::~UIServer() {

    }

    void UIServer::Release() {
      // レジストリが空の場合中断
      if (_uiRegistry.empty()) {
        return;
      }
      // 登録UIの全解放
      for (auto&& ui : _uiRegistry) {
        // 解放処理
        ui.reset();
      }
      // レジストリの解放
      _uiRegistry.clear();
    }

    void UIServer::Process() {
      // レジストリ内のUIの更新
      for (auto&& ui : _uiRegistry) {
        ui->Process();
      }
    }

    void UIServer::Draw() const {
      // レジストリ内のUIの更新
      for (auto&& ui : _uiRegistry) {
        ui->Draw();
      }
    }

    void UIServer::RegisterUI(std::shared_ptr<UIBase> ui) {
      // UIの取得に失敗した場合エラー
      if (ui == nullptr) {
#ifdef _DEBUG
        throw ("UIServer:UIはnullptrです");
#endif
        return; // キーが不正
      }
      // レジストリに登録する
      _uiRegistry.emplace_back(std::move(ui));
    }
  } // namespace UI
} // namespace Game