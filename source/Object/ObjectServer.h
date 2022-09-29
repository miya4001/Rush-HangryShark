/*****************************************************************//**
 * @file   ObjectServer.h
 * @brief  オブジェクトを管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  プレイヤー
   */
  namespace Player {
    class PlayerShark;
  }
  /**
   * @brief  オブジェクト
   */
  namespace Object {
    class ObjectBase;
    /**
     * @class ObjectServer
     * @brief オブジェクトを管理するサーバクラス
     */
    class ObjectServer {
    public:
      /**
       * @brief コンストラクタ
       */
      ObjectServer();
      /**
       * @brief デストラクタ
       */
      ~ObjectServer();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  描画
       */
      void Draw() const;
      /**
       * @brief  オブジェクトを登録
       * @param  object オブジェクトのスマートポインタ
       * @param  add 直接追加(デフォルトでfalse)
       */
      void RegisterObject(std::shared_ptr<ObjectBase> object, const bool add = false);
      /**
       * @brief  オブジェクトレジストリの取得
       * @return オブジェクトのシェアードポインタが格納された動的配列
       */
      std::vector<std::shared_ptr<ObjectBase>> GetObjects() {
        return _objectRegistry;
      }
      /**
       * @brief  プレイヤーの取得
       * @return プレイヤーの参照
       */
      std::shared_ptr<Player::PlayerShark> GetPlayerShark();

    private:
      /**
       * @brief  オブジェクトの追加
       */
      void AddObjects();
      /**
       * @brief  オブジェクトが登録されているレジストリの解放
       * @param  registry オブジェクトのシェアードポインタが格納されたコンテナの参照
       */
      void DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& registry);

      //!< オブジェクトレジストリ
      std::vector<std::shared_ptr<ObjectBase>> _objectRegistry;
      //!< オブジェクト追加予約レジストリ
      std::vector<std::shared_ptr<ObjectBase>> _addObjectRegistry;
    };
  } // namespace Object
} // namespace Game