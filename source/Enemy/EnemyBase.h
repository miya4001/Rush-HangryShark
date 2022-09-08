/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  敵の基底クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"

/**
 * @brief  ゲーム
 */
namespace Game{
  /**
   * @brief  敵
   */
  namespace Enemy {
    namespace AppMath = AppFrame::Math;
    /**
     * @class EnemyBase
     * @brief 敵の基底クラス
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      EnemyBase(Application::ApplicationMain& app);
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      virtual bool Init();
      /**
       * @brief  更新
       */
      virtual void Process();

    protected:
      /**
       * @brief  パラメータの設定
       */
      virtual void SetParameters();
      /**
       * @brief  海中範囲外判定
       * @return true:海中範囲外
       *         false:海中範囲内
       */
      virtual bool IsOverSea();
      /**
       * @brief  衝突
       */
      virtual void Hit();
    };
  } // namespace Enemy
} // namespace Game