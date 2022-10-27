/*****************************************************************//**
 * @file   ConstLoadResourceKey.h
 * @brief  リソース読み込みキー定数
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  画像ハンドルキー
   */
  namespace GraphicKey {
    constexpr auto UnderSea = "underSea";              //!< 海中画像
    constexpr auto AMG = "amg";                        //!< AMG画像
    constexpr auto Title = "title";                    //!< タイトル画像
    constexpr auto Start = "start";                    //!< 開始画像
    constexpr auto Quit = "quit";                      //!< 終了画像
    constexpr auto GameOver = "gameOver";              //!< ゲームオーバー画像
    constexpr auto Retry = "retry";                    //!< リトライ画像
    constexpr auto BackTitle = "backTitle";            //!< タイトルバック画像
    constexpr auto Bubble = "bubble";                  //!< 泡画像
    constexpr auto HungryGauge = "hungryGauge";        //!< 空腹ゲージ画像
    constexpr auto HungryGaugeBar = "hungryGaugeBar";  //!< 空腹ゲージバー画像
    constexpr auto TimerNumber = "timerNumber";        //!< タイマー数字画像
    constexpr auto TimerColon = "timerColon";          //!< タイマーコロン画像
  } // namespace GraphicKey
  /**
   * @brief  モデルハンドルキー
   */
  namespace ModelKey {
    constexpr auto SeaSphere = "seaSphere";  //!< 海中背景モデル
    constexpr auto Shark = "shark";          //!< サメモデル
    constexpr auto Shrimp = "shrimp";        //!< エビモデル
    constexpr auto Tuna = "tuna";            //!< マグロモデル
    constexpr auto Jerryfish = "jerryfish";  //!< クラゲモデル
  } // namespace ModelKey
  /**
   * @brief  音源ハンドルキー
   */
  namespace SoundKey {
    constexpr auto Bubble = "bubble";  //!< 泡SE
    constexpr auto Hungry = "hungry";  //!< 空腹SE
    constexpr auto Bite = "bite";      //!< 噛みつきSE
    constexpr auto Eat = "eat";        //!< 捕食SE
  } // namespace SoundKey
}