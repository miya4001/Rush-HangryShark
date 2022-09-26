/*****************************************************************//**
 * @file   SpawnEnemy.h
 * @brief  敵の生成情報クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  生成
   */
  namespace Spawn {
    namespace AppMath = AppFrame::Math;
    /**
     * @class SpawnEnemy
     * @brief 敵の生成情報クラス
     */
    class SpawnEnemy {
    public:
      /**
       * @brief  コンストラクタ
       * @param  number 識別番号
       * @param  position 生成座標(プレイヤー座標への加数)
       * @param  rotation 生成向き
       */
      SpawnEnemy(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  識別番号の取得
       * @return 識別番号
       */
      int GetNumber() {
        return _number;
      }
      /**
       * @brief  生成情報の取得
       * @return 生成座標(プレイヤー座標への加数), 生成向き
       */
      std::pair<AppMath::Vector4, AppMath::Vector4> GetTransform() {
        return { _position, _rotation };
      }

    private:
      int _number{ -1 };  //!< 識別番号
      //!< 生成座標(プレイヤー座標への加数)
      AppMath::Vector4 _position;
      //!< 生成向き
      AppMath::Vector4 _rotation;
    };
  } // namespace Spawn
} // namespace Game