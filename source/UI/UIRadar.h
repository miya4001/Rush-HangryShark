/*****************************************************************//**
 * @file   UIRadar.h
 * @brief  UIレーダークラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#pragma once
#include "UIBase.h"
#include <vector>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class  UIRadar
     * @brief  UIレーダークラス
     */
    class UIRadar : public UIBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      UIRadar(Application::ApplicationMain& app);
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  更新
       */
      void Process() override;
      /**
       * @brief  描画
       */
      void Draw() const override;

    private:
      /**
       * @brief  反応消去
       */
      void ResponseClear();

      double _angle{ 0.0 };  //!< 角度(ラジアン)
      //!< 描画座標
      std::vector<std::pair<int, int>> _drawPosition;
    };
  } // namespace UI
} // namespace Game