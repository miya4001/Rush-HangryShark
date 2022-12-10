/*****************************************************************//**
 * @file   ResultComponent.h
 * @brief  リザルトコンポーネント
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#pragma once
#include "../Enemy/EnemyBase.h"

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  リザルト
   */
  namespace Result {
    /**
     * @class  ResultComponent
     * @brief  リザルトコンポーネント
     */
    class ResultComponent {
    public:
      /**
       * @brief  コンストラクタ
       */
      ResultComponent();
      /**
       * @brief  デストラクタ
       */
      ~ResultComponent();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  死亡数カウント
       * @param  enemy 敵の識別の列挙型
       */
      void DeadCount(Enemy::EnemyBase::EnemyID enemy);
      /**
       * @brief  エビ数の取得
       * @return エビ数
       */
      int GetShrimp() {
        return _shrimp;
      }
      /**
       * @brief  マグロ数の取得
       * @return マグロ数
       */
      int GetTuna() {
        return _tuna;
      }
      /**
       * @brief  クラゲ数の取得
       * @return クラゲ数
       */
      int GetJerryfish() {
        return _jerryfish;
      }

    private:
      int _shrimp{ 0 };     //!< エビ数
      int _tuna{ 0 };       //!< マグロ数
      int _jerryfish{ 0 };  //!< クラゲ数
    };
  } // namespace Result
} // namespace Game