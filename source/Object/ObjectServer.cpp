/*****************************************************************//**
 * @file   ObjectServer.cpp
 * @brief  オブジェクトを管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"

namespace Game {
  namespace Object {
    ObjectServer::ObjectServer() {
      // レジストリの初期化
      _objectRegistry.clear();
      _addObjectRegistry.clear();
    }

    ObjectServer::~ObjectServer() {

    }

    void ObjectServer::Release() {
      // レジストリの解放
      DeleteObjects(_objectRegistry);
      DeleteObjects(_addObjectRegistry);
    }

    void ObjectServer::Process() {
      // 追加予約されているオブジェクトがある場合
      if (!_addObjectRegistry.empty()) {
        // レジストリにオブジェクトを追加
        AddObjects();
      }
      // レジストリ内のオブジェクトの更新
      for (auto object : _objectRegistry) {
        // オブジェクトが死亡状態でない場合更新
        if (!object->IsDead()) {
          object->Process();
        }
      }
      // 不要になったオブジェクトを削除
      std::erase_if(_objectRegistry, [](auto&& obj) {return obj->IsDead(); });
    }

    void ObjectServer::Draw() const {
      // レジストリ内のオブジェクトの描画
      for (auto&& objct : _objectRegistry) {
        objct->Draw();
      }
    }

    void ObjectServer::RegisterObject(std::shared_ptr<ObjectBase> object) {
      // オブジェクトの取得に失敗した場合エラー
      if (object == nullptr) {
#ifdef _DEBUG
        throw ("オブジェクトはnullptrです");
#endif
        return; // キーが不正
        // 追加予約
        _addObjectRegistry.emplace_back(std::move(object));
      }
    }

    void ObjectServer::AddObjects() {
      // オブジェクトをレジストリの末尾に追加
      for (auto&& obj : _addObjectRegistry) {
        _objectRegistry.emplace_back(std::move(obj));
      }
      // 追加予約レジストリの解放
      _addObjectRegistry.clear();
    }

    void ObjectServer::DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& registry) {
      // レジストリが空の場合中断
      if (registry.empty()) {
        return;
      }
      // 登録オブジェクトの全解放
      for (auto&& obj : registry) {
        // 解放処理
        obj.reset();
      }
      // レジストリの解放
      registry.clear();
    }
  } // namespace Object
} // namespace Game